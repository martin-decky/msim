static exc_t instr_swc2(r4k_cpu_t *cpu, instr_t instr)
{
	if (cp0_status_cu2(cpu)) {
		/* Ignored */
		return excNone;
	}
	
	/* Coprocessor unusable */
	cp0_cause(cpu).val &= ~cp0_cause_ce_mask;
	cp0_cause(cpu).val |= cp0_cause_ce_cu2;
	return excCpU;
}

static void mnemonics_swc2(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "swc2");
	disassemble_rt_offset_base(instr, mnemonics, comments);
}
