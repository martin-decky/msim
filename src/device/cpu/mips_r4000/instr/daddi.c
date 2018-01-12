static exc_t instr_daddi(cpu_t *cpu, instr_t instr)
{
	if (CPU_64BIT_INSTRUCTION(cpu)) {
		uint64_t rs = cpu->regs[instr.i.rs].val;
		uint64_t imm = sign_extend_16_64(instr.i.imm);
		uint64_t sum = rs + imm;
		
		if (!((rs ^ imm) & SBIT64) && ((rs ^ sum) & SBIT64))
			return excOv;
		
		cpu->regs[instr.i.rt].val = sum;
	} else
		return excRI;
	
	return excNone;
}

static void mnemonics_daddi(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "daddi");
	disassemble_rt_rs_imm(instr, mnemonics, comments);
}
