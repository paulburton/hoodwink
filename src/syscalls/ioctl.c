#include "debug.h"
#include "string.h"
#include "syscall.h"

#define IOC_NRSHIFT	0
#define IOC_TYPESHIFT	8
#define IOC_SIZESHIFT	16
#define IOC_DIRSHIFT	(IOC_SIZESHIFT + IOC_SIZEBITS)

#define IOC(dir,type,nr,size)		\
	(((dir)  << IOC_DIRSHIFT) |	\
	 ((type) << IOC_TYPESHIFT) |	\
	 ((nr)   << IOC_NRSHIFT) |	\
	 ((size) << IOC_SIZESHIFT))

#define IO(type,nr)		IOC(IOC_NONE, (type), (nr), 0)
#define IOR(type,nr,size)	IOC(IOC_READ, (type), (nr), (size))
#define IOW(type,nr,size)	IOC(IOC_WRITE, (type), (nr), (size))
#define IOWR(type,nr,size)	IOC(IOC_READ | IOC_WRITE, (type), (nr), (size))

uint32_t translate_sys_ioctl(struct sys_state *sys, uint32_t *args)
{
	int ret, fd = args[0];
	unsigned int back_cmd, front_cmd = args[1];

	back_cmd = front_cmd & 0xffff;
	back_cmd |= ((front_cmd >> 16) & ((1 << IOC_SIZEBITS) - 1)) << 16;

	switch ((front_cmd >> (16 + FRONT_IOC_SIZEBITS)) & ((1 << FRONT_IOC_DIRBITS) - 1)) {
	case FRONT_IOC_NONE:
		back_cmd |= IOC_NONE << (16 + IOC_SIZEBITS);
		break;

	case FRONT_IOC_READ:
		back_cmd |= IOC_READ << (16 + IOC_SIZEBITS);
		break;

	case FRONT_IOC_WRITE:
		back_cmd |= IOC_WRITE << (16 + IOC_SIZEBITS);
		break;

	default:
		return -FRONT_EINVAL;
	}

	switch (back_cmd) {
	case IO('T', 0x0d): /* TCGETS */
		{
			front_termios_s *f = sys->mem_base + args[2];
			termios_s b;

			ret = sys_ioctl(fd, back_cmd, (unsigned long)&b);

			f->c_iflag = b.c_iflag;
			f->c_oflag = b.c_oflag;
			f->c_cflag = b.c_cflag;
			f->c_lflag = b.c_lflag;
			f->c_line = b.c_line;
			memcpy(f->c_cc, b.c_cc, min(sizeof(f->c_cc), sizeof(b.c_cc)));
		}
		break;

	default:
		debug("Unrecognised IOCTL cmd 0x%x\n", front_cmd);
		ret = -FRONT_EINVAL;
	}

	return ret;
}
