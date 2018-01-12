static exc_t instr_teq(cpu_t *cpu, instr_t instr)
{
	bool cond;
	
	if (CPU_64BIT_MODE(cpu))
		cond = (cpu->regs[instr.r.rs].val == cpu->regs[instr.r.rt].val);
	else
		cond = (cpu->regs[instr.r.rs].lo == cpu->regs[instr.r.rt].lo);
	
	if (cond)
		return excTr;
	
	return excNone;
}

static void mnemonics_teq(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "teq");
	disassemble_rs_rt(instr, mnemonics, comments);
}
