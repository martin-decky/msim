static exc_t instr_sra(r4k_cpu_t *cpu, instr_t instr)
{
	uint32_t rt = cpu->regs[instr.r.rt].lo;
	
	cpu->regs[instr.r.rd].val =
	    sign_extend_32_64((uint32_t) (((int32_t) rt) >> instr.r.sa));
	
	return excNone;
}

static void mnemonics_sra(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "sra");
	disassemble_rd_rt_sa(instr, mnemonics, comments);
}
