static exc_t instr_addi(cpu_t *cpu, instr_t instr)
{
	uint32_t rs = cpu->regs[instr.i.rs].lo;
	uint32_t imm = sign_extend_16_32(instr.i.imm);
	uint32_t sum = rs + imm;
	
	if (!((rs ^ imm) & SBIT32) && ((rs ^ sum) & SBIT32))
		return excOv;
	
	cpu->regs[instr.i.rt].val = sign_extend_32_64(sum);
	return excNone;
}

static void mnemonics_addi(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "addi");
	disassemble_rt_rs_imm(instr, mnemonics, comments);
}
