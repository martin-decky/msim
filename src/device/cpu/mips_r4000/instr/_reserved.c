static exc_t instr__reserved(r4k_cpu_t *cpu, instr_t instr)
{
	return excRI;
}

static void mnemonics__reserved(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "(reserved)");
}
