static exc_t instr_bc0t(r4k_cpu_t *cpu, instr_t instr)
{
	if (CP0_USABLE(cpu)) {
		/* Ignore (always true) */
		cpu->pc_next.ptr +=
		    (((int64_t) sign_extend_16_64(instr.i.imm)) << TARGET_SHIFT);
		cpu->branch = BRANCH_COND;
		return excJump;
	}
	
	/* Coprocessor unusable */
	cp0_cause(cpu).val &= ~cp0_cause_ce_mask;
	return excCpU;
}

static void mnemonics_bc0t(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "bc0t");
	disassemble_offset(addr, instr, mnemonics, comments);
}
