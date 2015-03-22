#include "debug.h"
#include "mips32.h"
#include "syscall.h"

uint32_t frontend_rdhwr(const struct mips32_state *sys, unsigned reg)
{
	switch (reg) {
	case 29:
		return sys->cpu.ulr;

	default:
		debug("rdhwr %u unimplemented\n", reg);
		return 0;
	}
}
