static exc_t instr_srl(cpu_t *cpu, instr_t instr)
{
	uint32_t rt = cpu->regs[instr.r.rt].lo;
	
	cpu->regs[instr.r.rd].val = sign_extend_32_64(rt >> instr.r.sa);
	
	return excNone;
}

static void mnemonics_srl(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "srl");
	disassemble_rd_rt_sa(instr, mnemonics, comments);
}
