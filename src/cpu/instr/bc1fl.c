static exc_t instr_bc1fl(cpu_t *cpu, instr_t instr)
{
	if (cp0_status_cu1(cpu)) {
		/* Ignore (always false) */
		cpu->pc_next.ptr += 4;
		return excNone;
	}
	
	/* Coprocessor unusable */
	cp0_cause(cpu).val &= ~cp0_cause_ce_mask;
	cp0_cause(cpu).val |= cp0_cause_ce_cu1;
	return excCpU;
}

static void mnemonics_bc1fl(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "bc1fl");
	disassemble_offset(addr, instr, mnemonics, comments);
}
