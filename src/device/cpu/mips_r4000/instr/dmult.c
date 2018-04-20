static exc_t instr_dmult(r4k_cpu_t *cpu, instr_t instr)
{
	if (CPU_64BIT_INSTRUCTION(cpu)) {
		ASSERT(false);
		return excNone;
	}
	
	return excRI;
}

static void mnemonics_dmult(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "dmult");
	disassemble_rs_rt(instr, mnemonics, comments);
}
