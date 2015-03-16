#ifndef __hoodwink_config_h__
#define __hoodwink_config_h__

#ifdef FRONT_ARCH_MIPS32
# define FRONT_ARCH MIPS32
#endif
#ifdef FRONT_ARCH_X86_64
# define FRONT_ARCH X86_64
#endif

#ifdef BACK_ARCH_MIPS32
# define BACK_ARCH MIPS32
#endif
#ifdef BACK_ARCH_X86_64
# define BACK_ARCH X86_64
#endif

#endif /* __hoodwink_config_h__ */
