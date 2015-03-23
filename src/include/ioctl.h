#ifndef __hoodwink_ioctl_h__
#define __hoodwink_ioctl_h__

#include "config.h"
#include "types.h"
#include "util.h"

#if defined(FRONT_ARCH_MIPS32) || defined(BACK_ARCH_MIPS32)
# include "mips32/ioctl.h"
#endif
#if defined(FRONT_ARCH_X86_64) || defined(BACK_ARCH_X86_64)
# include "x86_64/ioctl.h"
#endif

#define IOC_NONE		CAT(BACK_ARCH, _IOC_NONE)
#define IOC_READ		CAT(BACK_ARCH, _IOC_READ)
#define IOC_WRITE		CAT(BACK_ARCH, _IOC_WRITE)
#define IOC_SIZEBITS		CAT(BACK_ARCH, _IOC_SIZEBITS)
#define IOC_DIRBITS		CAT(BACK_ARCH, _IOC_DIRBITS)

#define FRONT_IOC_NONE		CAT(FRONT_ARCH, _IOC_NONE)
#define FRONT_IOC_READ		CAT(FRONT_ARCH, _IOC_READ)
#define FRONT_IOC_WRITE		CAT(FRONT_ARCH, _IOC_WRITE)
#define FRONT_IOC_SIZEBITS	CAT(FRONT_ARCH, _IOC_SIZEBITS)
#define FRONT_IOC_DIRBITS	CAT(FRONT_ARCH, _IOC_DIRBITS)

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

#define TCGETS			CAT(BACK_ARCH, _TCGETS)
#define FRONT_TCGETS		CAT(FRONT_ARCH, _TCGETS)

#endif /* __hoodwink_ioctl_h__ */
