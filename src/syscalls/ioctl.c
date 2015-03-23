#include "debug.h"
#include "ioctl.h"
#include "string.h"
#include "syscall.h"

uint32_t translate_sys_ioctl(const struct sys_state *sys, uint32_t *args)
{
	int ret, fd = args[0];
	unsigned int front_cmd = args[1];

	switch (front_cmd) {
	case FRONT_TCGETS:
		{
			front_termios_s *f = sys->mem_base + args[2];
			termios_s b;

			ret = sys_ioctl(fd, TCGETS, (unsigned long)&b);
			debug("ioctl(%d, 0x%x, ...) = 0x%x\n", fd, TCGETS, ret);

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
