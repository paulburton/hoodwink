/*
 * hoodwink
 * Copyright (C) 2015 Paul Burton <paul@archlinuxmips.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <stdbool.h>

#include "debug.h"
#include "mips32.h"
#include "syscall.h"

static const char *reg_names[32] = {
	"zero", "at", "v0", "v1",
	"a0", "a1", "a2", "a3",
	"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
	"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
	"t8", "t9", "k0", "k1",
	"gp", "sp", "fp", "ra",
};

static uint32_t se8(unsigned imm)
{
	return (uint32_t)(int32_t)(int8_t)imm;
}

static uint32_t se16(unsigned imm)
{
	return (uint32_t)(int32_t)(int16_t)imm;
}

void frontend_interp(struct mips32_state *mips)
{
	uint32_t inst = *(uint32_t *)(mips->sys.mem_base + mips->cpu.pc);
	uint32_t *gpr = &mips->cpu.gpr[0];
	uint64_t *fpr = &mips->cpu.fpr[0];
	uint32_t next_pc = mips->cpu.pc + 4;
	uint32_t tgt;
	uint64_t u64;
	unsigned op = inst >> 26;
	unsigned rs = (inst >> 21) & 0x1f;
	unsigned rt = (inst >> 16) & 0x1f;
	unsigned rd = (inst >> 11) & 0x1f;
	unsigned sa = (inst >> 6) & 0x1f;
	unsigned imm = inst & 0xffff;
	unsigned msb, lsb, sz;
	int simm = se16(imm);
	bool do_ds = false;
	void *ptr;

	debug_in_asm("interp %8x: %08x ", mips->cpu.pc, inst);

	switch (op) {
	case MIPS_OP_SPEC:
		op = inst & 0x3f;
		switch (op) {
		case MIPS_SPEC_SLL:
			if (!inst)
				debug_in_asm("nop\n");
			else
				debug_in_asm("sll\t%s, %s, %u\n", reg_names[rd], reg_names[rt], sa);
			if (rd)
				gpr[rd] = gpr[rt] << sa;
			break;

		case MIPS_SPEC_SRL:
			debug_in_asm("srl\t%s, %s, %u\n", reg_names[rd], reg_names[rt], sa);
			if (rd)
				gpr[rd] = gpr[rt] >> sa;
			break;

		case MIPS_SPEC_SRA:
			debug_in_asm("sra\t%s, %s, %u\n", reg_names[rd], reg_names[rt], sa);
			if (rd)
				gpr[rd] = (int32_t)gpr[rt] >> sa;
			break;

		case MIPS_SPEC_SLLV:
			debug_in_asm("sllv\t%s, %s, %s\n", reg_names[rd], reg_names[rt], reg_names[rs]);
			if (rd)
				gpr[rd] = gpr[rt] << gpr[rs];
			break;

		case MIPS_SPEC_SRLV:
			debug_in_asm("srlv\t%s, %s, %s\n", reg_names[rd], reg_names[rt], reg_names[rs]);
			if (rd)
				gpr[rd] = gpr[rt] >> gpr[rs];
			break;

		case MIPS_SPEC_SRAV:
			debug_in_asm("srav\t%s, %s, %s\n", reg_names[rd], reg_names[rt], reg_names[rs]);
			if (rd)
				gpr[rd] = (int32_t)gpr[rt] >> gpr[rs];
			break;

		case MIPS_SPEC_JR:
			debug_in_asm("jr\t%s\n", reg_names[rs]);
			next_pc = gpr[rs];
			do_ds = true;
			break;

		case MIPS_SPEC_JALR:
			if (rd == 31)
				debug_in_asm("jalr\t%s\n", reg_names[rs]);
			else
				debug_in_asm("jalr\t%s, %s\n", reg_names[rd], reg_names[rs]);
			if (rd)
				gpr[rd] = next_pc + 4;
			next_pc = gpr[rs];
			do_ds = true;
			break;

		case MIPS_SPEC_MOVZ:
			debug_in_asm("movz\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			if (rd && !gpr[rt])
				gpr[rd] = gpr[rs];
			break;

		case MIPS_SPEC_MOVN:
			debug_in_asm("movn\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			if (rd && gpr[rt])
				gpr[rd] = gpr[rs];
			break;

		case MIPS_SPEC_SYSCALL:
			tgt = (inst >> 6) & 0xfffff;

			debug_in_asm("syscall");
			if (tgt)
				debug_in_asm("\t0x%x\n", tgt);
			else
				debug_in_asm("\n");

			frontend_syscall_invoke(&mips->sys, gpr[2]);
			break;

		case MIPS_SPEC_BREAK:
			debug_in_asm("break\n");
			/* TODO: exception */
			sys_exit(1);
			break;

		case MIPS_SPEC_SYNC:
			debug_in_asm("sync\n");
			break;

		case MIPS_SPEC_MFHI:
			debug_in_asm("mfhi\t%s\n", reg_names[rd]);
			if (rd)
				gpr[rd] = mips->cpu.hi;
			break;

		case MIPS_SPEC_MFLO:
			debug_in_asm("mflo\t%s\n", reg_names[rd]);
			if (rd)
				gpr[rd] = mips->cpu.lo;
			break;

		case MIPS_SPEC_MULTU:
			debug_in_asm("multu\t%s, %s\n", reg_names[rs], reg_names[rt]);
			u64 = (uint64_t)gpr[rs] * gpr[rt];
			mips->cpu.lo = u64;
			mips->cpu.hi = u64 >> 32;
			break;

		case MIPS_SPEC_DIVU:
			debug_in_asm("divu\t%s, %s\n", reg_names[rs], reg_names[rt]);
			mips->cpu.lo = gpr[rs] / gpr[rt];
			mips->cpu.hi = gpr[rs] % gpr[rt];
			break;

		case MIPS_SPEC_ADD:
			debug_in_asm("add\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			/* TODO: overflow check */
			if (rd)
				gpr[rd] = gpr[rs] + gpr[rt];
			break;

		case MIPS_SPEC_ADDU:
			if (rt)
				debug_in_asm("addu\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			else
				debug_in_asm("move\t%s, %s\n", reg_names[rd], reg_names[rs]);
			if (rd)
				gpr[rd] = gpr[rs] + gpr[rt];
			break;

		case MIPS_SPEC_SUBU:
			if (rs)
				debug_in_asm("subu\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			else
				debug_in_asm("negu\t%s, %s\n", reg_names[rd], reg_names[rt]);

			if (rd)
				gpr[rd] = gpr[rs] - gpr[rt];
			break;

		case MIPS_SPEC_AND:
			debug_in_asm("and\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			if (rd)
				gpr[rd] = gpr[rs] & gpr[rt];
			break;

		case MIPS_SPEC_OR:
			debug_in_asm("or\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			if (rd)
				gpr[rd] = gpr[rs] | gpr[rt];
			break;

		case MIPS_SPEC_XOR:
			debug_in_asm("xor\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			if (rd)
				gpr[rd] = gpr[rs] ^ gpr[rt];
			break;

		case MIPS_SPEC_NOR:
			debug_in_asm("nor\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			if (rd)
				gpr[rd] = ~(gpr[rs] | gpr[rt]);
			break;

		case MIPS_SPEC_SLT:
			debug_in_asm("slt\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			if (rd)
				gpr[rd] = (int32_t)gpr[rs] < (int32_t)gpr[rt];
			break;

		case MIPS_SPEC_SLTU:
			debug_in_asm("sltu\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			if (rd)
				gpr[rd] = gpr[rs] < gpr[rt];
			break;

		case MIPS_SPEC_TEQ:
			tgt = (inst >> 6) & 0x3ff;
			debug_in_asm("teq\t%s, %s", reg_names[rs], reg_names[rt]);
			if (tgt)
				debug_in_asm(", 0x%x\n", tgt);
			else
				debug_in_asm("\n");

			if (gpr[rs] == gpr[rt]) {
				/* TODO: exception */
				sys_exit(1);
			}
			break;

		default:
			goto ri;
		}
		break;

	case MIPS_OP_REGIMM:
		op = rt;
		switch (op) {
		case MIPS_REGIMM_BLTZ:
			tgt = next_pc + (simm << 2);
			debug_in_asm("bltz\t%s, 0x%x\n", reg_names[rs], tgt);
			if ((int32_t)gpr[rs] < 0) {
				next_pc = tgt;
				do_ds = true;
			}
			break;

		case MIPS_REGIMM_BGEZ:
			tgt = next_pc + (simm << 2);
			debug_in_asm("bgez\t%s, 0x%x\n", reg_names[rs], tgt);
			if ((int32_t)gpr[rs] >= 0) {
				next_pc = tgt;
				do_ds = true;
			}
			break;

		case MIPS_REGIMM_BLTZAL:
			tgt = next_pc + (simm << 2);
			debug_in_asm("bltzal\t%s, 0x%x\n", reg_names[rs], tgt);
			gpr[31] = next_pc + 4;
			if ((int32_t)gpr[rs] < 0) {
				next_pc = tgt;
				do_ds = true;
			}
			break;

		case MIPS_REGIMM_BGEZAL:
			tgt = next_pc + (simm << 2);
			if (rs == 0)
				debug_in_asm("bal\t0x%x\n", tgt);
			else
				debug_in_asm("bgezal\t%s, 0x%x\n", reg_names[rs], tgt);
			gpr[31] = next_pc + 4;
			if ((int32_t)gpr[rs] >= 0) {
				next_pc = tgt;
				do_ds = true;
			}
			break;

		default:
			goto ri;
		}
		break;

	case MIPS_OP_J:
		next_pc &= ~((1 << 28) - 1);
		next_pc |= (inst & 0x3ffffff) << 2;

		debug_in_asm("j\t0x%x\n", next_pc);

		do_ds = true;
		break;

	case MIPS_OP_JAL:
		gpr[31] = next_pc + 4;

		next_pc &= ~((1 << 28) - 1);
		next_pc |= (inst & 0x3ffffff) << 2;

		debug_in_asm("jal\t0x%x\n", next_pc);

		do_ds = true;
		break;

	case MIPS_OP_BEQ:
		tgt = next_pc + (simm << 2);

		if (rt)
			debug_in_asm("beq\t%s, %s", reg_names[rs], reg_names[rt]);
		else
			debug_in_asm("beqz\t%s", reg_names[rs]);
		debug_in_asm(", 0x%x\n", tgt);

		if (gpr[rs] == gpr[rt]) {
			next_pc = tgt;
			do_ds = true;
		}
		break;

	case MIPS_OP_BNE:
		tgt = next_pc + (simm << 2);

		if (rt)
			debug_in_asm("bne\t%s, %s", reg_names[rs], reg_names[rt]);
		else
			debug_in_asm("bnez\t%s", reg_names[rs]);
		debug_in_asm(", 0x%x\n", tgt);

		if (gpr[rs] != gpr[rt]) {
			next_pc = tgt;
			do_ds = true;
		}
		break;

	case MIPS_OP_BLEZ:
		tgt = next_pc + (simm << 2);
		debug_in_asm("blez\t%s, 0x%x\n", reg_names[rs], tgt);

		if ((int32_t)gpr[rs] <= 0) {
			next_pc = tgt;
			do_ds = true;
		}
		break;

	case MIPS_OP_BGTZ:
		tgt = next_pc + (simm << 2);
		debug_in_asm("bgtz\t%s, 0x%x\n", reg_names[rs], tgt);

		if ((int32_t)gpr[rs] > 0) {
			next_pc = tgt;
			do_ds = true;
		}
		break;

	case MIPS_OP_ADDIU:
		if (rs)
			debug_in_asm("addiu\t%s, %s", reg_names[rt], reg_names[rs]);
		else
			debug_in_asm("li\t%s", reg_names[rt]);
		debug_in_asm(", %d\n", simm);

		if (rt)
			gpr[rt] = gpr[rs] + simm;
		break;

	case MIPS_OP_SLTI:
		debug_in_asm("slti\t%s, %s, %d\n", reg_names[rt], reg_names[rs], simm);
		if (rt)
			gpr[rt] = (int32_t)gpr[rs] < simm;
		break;

	case MIPS_OP_SLTIU:
		debug_in_asm("sltiu\t%s, %s, %d\n", reg_names[rt], reg_names[rs], simm);
		if (rt)
			gpr[rt] = gpr[rs] < (uint32_t)simm;
		break;

	case MIPS_OP_ANDI:
		debug_in_asm("andi\t%s, %s, 0x%x\n", reg_names[rt], reg_names[rs], imm);
		if (rt)
			gpr[rt] = gpr[rs] & imm;
		break;

	case MIPS_OP_ORI:
		debug_in_asm("ori\t%s, %s, 0x%x\n", reg_names[rt], reg_names[rs], imm);
		if (rt)
			gpr[rt] = gpr[rs] | imm;
		break;

	case MIPS_OP_XORI:
		debug_in_asm("xori\t%s, %s, 0x%x\n", reg_names[rt], reg_names[rs], imm);
		if (rt)
			gpr[rt] = gpr[rs] ^ imm;
		break;

	case MIPS_OP_LUI:
		debug_in_asm("lui\t%s, 0x%x\n", reg_names[rt], imm);

		if (rt)
			gpr[rt] = imm << 16;
		break;

	case MIPS_OP_SPEC2:
		op = inst & 0x3f;
		switch (op) {
		case MIPS_SPEC2_MUL:
			debug_in_asm("mul\t%s, %s, %s\n", reg_names[rd], reg_names[rs], reg_names[rt]);
			if (rd)
				gpr[rd] = gpr[rs] * gpr[rt];
			break;

		case MIPS_SPEC2_CLZ:
			debug_in_asm("clz\t%s, %s\n", reg_names[rd], reg_names[rs]);
			if (rd)
				gpr[rd] = gpr[rs] ? __builtin_clz(gpr[rs]) : 32;
			break;

		default:
			goto ri;
		}
		break;

	case MIPS_OP_SPEC3:
		op = inst & 0x3f;
		switch (op) {
		case MIPS_SPEC3_EXT:
			sz = ((inst >> 11) & 0x1f) + 1;
			lsb = (inst >> 6) & 0x1f;
			debug_in_asm("ext\t%s, %s, 0x%x, 0x%x\n", reg_names[rt], reg_names[rs], lsb, sz);
			if (rt)
				gpr[rt] = (gpr[rs] >> lsb) & ((1 << sz) - 1);
			break;

		case MIPS_SPEC3_INS:
			msb = (inst >> 11) & 0x1f;
			lsb = (inst >> 6) & 0x1f;
			sz = msb + 1 - lsb;
			debug_in_asm("ins\t%s, %s, 0x%x, 0x%x\n", reg_names[rt], reg_names[rs], lsb, sz);
			if (rt) {
				gpr[rt] &= ~(((1 << sz) - 1) << lsb);
				gpr[rt] |= (gpr[rs] & ((1 << sz) - 1)) << lsb;
			}
			break;

		case MIPS_SPEC3_BSHFL:
			op = (inst >> 6) & 0x1f;
			switch (op) {
			case MIPS_BSHFL_SEB:
				debug_in_asm("seb\t%s, %s\n", reg_names[rd], reg_names[rt]);
				if (rd)
					gpr[rd] = se8(gpr[rt]);
				break;

			case MIPS_BSHFL_SEH:
				debug_in_asm("seh\t%s, %s\n", reg_names[rd], reg_names[rt]);
				if (rd)
					gpr[rd] = se16(gpr[rt]);
				break;

			default:
				goto ri;
			}
			break;

		case MIPS_SPEC3_RDHWR:
			debug_in_asm("rdhwr\t%s, $%u\n", reg_names[rt], rd);
			if (rt)
				gpr[rt] = frontend_rdhwr(mips, rd);
			break;

		default:
			goto ri;
		}
		break;

	case MIPS_OP_LB:
		debug_in_asm("lb\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);

		if (rt) {
			ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
			gpr[rt] = se8(*(uint8_t *)ptr);
		}
		break;

	case MIPS_OP_LH:
		debug_in_asm("lh\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);

		if (rt) {
			ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
			gpr[rt] = se16(*(uint16_t *)ptr);
		}
		break;

	case MIPS_OP_LWL:
		debug_in_asm("lwl\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);

		if (rt) {
			ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
			/* TODO: FIXME! */
		}
		break;

	case MIPS_OP_LW:
		debug_in_asm("lw\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);

		if (rt) {
			ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
			gpr[rt] = *(uint32_t *)ptr;
		}
		break;

	case MIPS_OP_LBU:
		debug_in_asm("lbu\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);

		if (rt) {
			ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
			gpr[rt] = *(uint8_t *)ptr;
		}
		break;

	case MIPS_OP_LHU:
		debug_in_asm("lhu\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);

		if (rt) {
			ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
			gpr[rt] = *(uint16_t *)ptr;
		}
		break;

	case MIPS_OP_LWR:
		debug_in_asm("lwr\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);

		if (rt) {
			ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
			/* TODO: FIXME! */
			gpr[rt] = *(uint32_t *)ptr;
		}
		break;

	case MIPS_OP_SB:
		debug_in_asm("sb\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);
		ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
		*(uint8_t *)ptr = gpr[rt];
		break;

	case MIPS_OP_SH:
		debug_in_asm("sh\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);
		ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
		*(uint16_t *)ptr = gpr[rt];
		break;

	case MIPS_OP_SWL:
		debug_in_asm("swl\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);
		ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
		/* TODO: FIXME! */
		break;

	case MIPS_OP_SW:
		debug_in_asm("sw\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);
		ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
		*(uint32_t *)ptr = gpr[rt];
		break;

	case MIPS_OP_SWR:
		debug_in_asm("swr\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);
		ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
		/* TODO: FIXME! */
		*(uint32_t *)ptr = gpr[rt];
		break;

	case MIPS_OP_LL:
		debug_in_asm("ll\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);

		if (rt) {
			ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
			/* TODO: atomics! */
			gpr[rt] = *(uint32_t *)ptr;
		}
		break;

	case MIPS_OP_PREF:
		debug_in_asm("pref\t0x%x, %d(%s)\n", rt, simm, reg_names[rs]);
		break;

	case MIPS_OP_LDC1:
		debug_in_asm("ldc1\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);
		ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
		fpr[rt] = *(uint64_t *)ptr;
		break;

	case MIPS_OP_SC:
		debug_in_asm("sc\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);
		ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
		/* TODO: atomics! */
		*(uint32_t *)ptr = gpr[rt];
		gpr[rt] = 1;
		break;

	case MIPS_OP_SDC1:
		debug_in_asm("sdc1\t%s, %d(%s)\n", reg_names[rt], simm, reg_names[rs]);
		ptr = mips->sys.mem_base + (uintptr_t)gpr[rs] + simm;
		*(uint64_t *)ptr = fpr[rt];
		break;

	default:
	ri:
		debug("reserved instruction 0x%08x\n", inst);
		sys_exit(1);
	}

	if (0) {
		debug("CPU state:\n");
		debug("  zr: 0x%08x  at: 0x%08x  v0: 0x%08x  v1: 0x%08x\n",
		      mips->cpu.gpr[0], mips->cpu.gpr[1], mips->cpu.gpr[2], mips->cpu.gpr[3]);
		debug("  a0: 0x%08x  a1: 0x%08x  a2: 0x%08x  a3: 0x%08x\n",
		      mips->cpu.gpr[4], mips->cpu.gpr[5], mips->cpu.gpr[6], mips->cpu.gpr[7]);
		debug("  t0: 0x%08x  t1: 0x%08x  t2: 0x%08x  t3: 0x%08x\n",
		      mips->cpu.gpr[8], mips->cpu.gpr[9], mips->cpu.gpr[10], mips->cpu.gpr[11]);
		debug("  t4: 0x%08x  t5: 0x%08x  t6: 0x%08x  t7: 0x%08x\n",
		      mips->cpu.gpr[12], mips->cpu.gpr[13], mips->cpu.gpr[14], mips->cpu.gpr[15]);
		debug("  s0: 0x%08x  s1: 0x%08x  s2: 0x%08x  s3: 0x%08x\n",
		      mips->cpu.gpr[16], mips->cpu.gpr[17], mips->cpu.gpr[18], mips->cpu.gpr[19]);
		debug("  s4: 0x%08x  s5: 0x%08x  s6: 0x%08x  s7: 0x%08x\n",
		      mips->cpu.gpr[20], mips->cpu.gpr[21], mips->cpu.gpr[22], mips->cpu.gpr[23]);
		debug("  t8: 0x%08x  t9: 0x%08x  k0: 0x%08x  k1: 0x%08x\n",
		      mips->cpu.gpr[24], mips->cpu.gpr[25], mips->cpu.gpr[26], mips->cpu.gpr[27]);
		debug("  gp: 0x%08x  sp: 0x%08x  fp: 0x%08x  ra: 0x%08x\n",
		      mips->cpu.gpr[28], mips->cpu.gpr[29], mips->cpu.gpr[30], mips->cpu.gpr[31]);
	}

	if (do_ds) {
		mips->cpu.pc += 4;
		frontend_interp(mips);
	}

	mips->cpu.pc = next_pc;
}
