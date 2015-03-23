#ifndef __hoodwink_mips32_h__
#define __hoodwink_mips32_h__

#include "sys.h"
#include "syscall.h"
#include "util.h"

struct mips32_state {
	struct sys_state sys;

	struct {
		uint32_t gpr[32];
		uint64_t fpr[32];
		uint32_t pc;
		uint32_t hi, lo;
		uint32_t ulr;
	} cpu;
};

enum mips32_delta_reg {
	GPR0	= 0,
	GPR31	= 31,

	FPR0	= 32,
	FPR31	= 63,

	HI,
	LO,

	ULR,

	MAX_DELTA_SIZE,
};

struct mips32_delta {
	uint64_t values[MAX_DELTA_SIZE];
	enum mips32_delta_reg regs[MAX_DELTA_SIZE];
	uint8_t count;
	uint32_t next_pc;
};

static inline void mips32_delta_set(struct mips32_delta *d, enum mips32_delta_reg reg, uint64_t val)
{
	unsigned i;

	/* zero never changes */
	if (reg == GPR0)
		return;

#ifdef DEBUG
	if (d->count >= MAX_DELTA_SIZE) {
		debug("Delta too large?!?\n");
		sys_exit(1);
	}
#endif

	i = d->count++;
	d->regs[i] = reg;
	d->values[i] = val;
}

enum mips_op {
	MIPS_OP_SPEC		= 0x00,
	MIPS_OP_REGIMM		= 0x01,
	MIPS_OP_J		= 0x02,
	MIPS_OP_JAL		= 0x03,
	MIPS_OP_BEQ		= 0x04,
	MIPS_OP_BNE		= 0x05,
	MIPS_OP_BLEZ		= 0x06,
	MIPS_OP_BGTZ		= 0x07,
	MIPS_OP_ADDIU		= 0x09,
	MIPS_OP_SLTI		= 0x0a,
	MIPS_OP_SLTIU		= 0x0b,
	MIPS_OP_ANDI		= 0x0c,
	MIPS_OP_ORI		= 0x0d,
	MIPS_OP_XORI		= 0x0e,
	MIPS_OP_LUI		= 0x0f,
	MIPS_OP_BEQL		= 0x14,
	MIPS_OP_BNEL		= 0x15,
	MIPS_OP_SPEC2		= 0x1c,
	MIPS_OP_SPEC3		= 0x1f,
	MIPS_OP_LB		= 0x20,
	MIPS_OP_LH		= 0x21,
	MIPS_OP_LWL		= 0x22,
	MIPS_OP_LW		= 0x23,
	MIPS_OP_LBU		= 0x24,
	MIPS_OP_LHU		= 0x25,
	MIPS_OP_LWR		= 0x26,
	MIPS_OP_SB		= 0x28,
	MIPS_OP_SH		= 0x29,
	MIPS_OP_SWL		= 0x2a,
	MIPS_OP_SW		= 0x2b,
	MIPS_OP_SWR		= 0x2e,
	MIPS_OP_LL		= 0x30,
	MIPS_OP_PREF		= 0x33,
	MIPS_OP_LDC1		= 0x35,
	MIPS_OP_SC		= 0x38,
	MIPS_OP_SDC1		= 0x3d,
};

enum mips_op_regimm {
	MIPS_REGIMM_BLTZ	= 0x00,
	MIPS_REGIMM_BGEZ	= 0x01,
	MIPS_REGIMM_BLTZAL	= 0x10,
	MIPS_REGIMM_BGEZAL	= 0x11,
};

enum mips_op_spec {
	MIPS_SPEC_SLL		= 0x00,
	MIPS_SPEC_SRL		= 0x02,
	MIPS_SPEC_SRA		= 0x03,
	MIPS_SPEC_SLLV		= 0x04,
	MIPS_SPEC_SRLV		= 0x06,
	MIPS_SPEC_SRAV		= 0x07,
	MIPS_SPEC_JR		= 0x08,
	MIPS_SPEC_JALR		= 0x09,
	MIPS_SPEC_MOVZ		= 0x0a,
	MIPS_SPEC_MOVN		= 0x0b,
	MIPS_SPEC_SYSCALL	= 0x0c,
	MIPS_SPEC_BREAK		= 0x0d,
	MIPS_SPEC_SYNC		= 0x0f,
	MIPS_SPEC_MFHI		= 0x10,
	MIPS_SPEC_MFLO		= 0x12,
	MIPS_SPEC_MULT		= 0x18,
	MIPS_SPEC_MULTU		= 0x19,
	MIPS_SPEC_DIV		= 0x1a,
	MIPS_SPEC_DIVU		= 0x1b,
	MIPS_SPEC_ADD		= 0x20,
	MIPS_SPEC_ADDU		= 0x21,
	MIPS_SPEC_SUBU		= 0x23,
	MIPS_SPEC_AND		= 0x24,
	MIPS_SPEC_OR		= 0x25,
	MIPS_SPEC_XOR		= 0x26,
	MIPS_SPEC_NOR		= 0x27,
	MIPS_SPEC_SLT		= 0x2a,
	MIPS_SPEC_SLTU		= 0x2b,
	MIPS_SPEC_TEQ		= 0x34,
};

enum mips_op_spec2 {
	MIPS_SPEC2_MUL		= 0x02,
	MIPS_SPEC2_CLZ		= 0x20,
};

enum mips_op_spec3 {
	MIPS_SPEC3_EXT		= 0x00,
	MIPS_SPEC3_INS		= 0x04,
	MIPS_SPEC3_BSHFL	= 0x20,
	MIPS_SPEC3_RDHWR	= 0x3b,
};

enum mips_op_spec3_bshfl {
	MIPS_BSHFL_SEB		= 0x10,
	MIPS_BSHFL_SEH		= 0x18,
};

enum mips_vdso_entry {
	VDSO_SIGRETURN,
	VDSO_RT_SIGRETURN,
};

extern void frontend_interp_fetchexec(const struct mips32_state *mips, struct mips32_delta *delta, uint32_t pc_off, int *restart_on_signal);
extern void frontend_interp_writeback(struct mips32_state *mips, struct mips32_delta *delta);

extern uint32_t frontend_rdhwr(const struct mips32_state *sys, unsigned reg);

extern void frontend_rt_sigreturn(const struct mips32_state *mips, struct mips32_delta *delta);

extern void frontend_vdso_init(struct sys_state *sys);
extern uint32_t frontend_vdso_entry(struct sys_state *sys, enum mips_vdso_entry entry);

#endif /* __hoodwink_mips32_h__ */
