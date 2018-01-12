static exc_t instr_bc1t(cpu_t *cpu, instr_t instr)
{
	if (cp0_status_cu1(cpu)) {
		/* Ignore (always true) */
		cpu->pc_next.ptr +=
		    (((int64_t) sign_extend_16_64(instr.i.imm)) << TARGET_SHIFT);
		cpu->branch = BRANCH_COND;
		return excJump;
	}
	
	/* Coprocessor unusable */
	cp0_cause(cpu).val &= ~cp0_cause_ce_mask;
	cp0_cause(cpu).val |= cp0_cause_ce_cu1;
	return excCpU;
}

static void mnemonics_bc1t(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "bc1t");
	disassemble_offset(addr, instr, mnemonics, comments);
}
