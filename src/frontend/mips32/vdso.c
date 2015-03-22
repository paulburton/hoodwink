#include "debug.h"
#include "mips32.h"
#include "sys.h"
#include "syscall.h"

void frontend_vdso_init(struct sys_state *sys)
{
	uint32_t vdso_addr = 0x7fff0000;
	unsigned vdso_sz = 1 << sys->page_bits;
	uint32_t *code = sys->mem_base + vdso_addr;
	int err;

	err = sys_mprotect(sys->mem_base + vdso_addr, vdso_sz, PROT_READ | PROT_WRITE);
	if (err) {
		debug("Failed to mprotect VDSO\n");
		sys_exit(1);
	}

	code[0] = (MIPS_OP_ADDIU << 26) | (2 << 16) | MIPS32_NR_sigreturn;
	code[1] = (MIPS_OP_SPEC << 26) | MIPS_SPEC_SYSCALL;

	code[2] = (MIPS_OP_ADDIU << 26) | (2 << 16) | MIPS32_NR_rt_sigreturn;
	code[3] = (MIPS_OP_SPEC << 26) | MIPS_SPEC_SYSCALL;

	err = sys_mprotect(sys->mem_base + vdso_addr, vdso_sz, PROT_READ);
	if (err) {
		debug("Failed to mprotect VDSO\n");
		sys_exit(1);
	}
}

uint32_t frontend_vdso_entry(struct sys_state *sys, enum mips_vdso_entry entry)
{
	switch (entry) {
	case VDSO_SIGRETURN:
		return 0x7fff0000;

	case VDSO_RT_SIGRETURN:
		return 0x7fff0008;

	default:
		return 0;
	}
}
