static exc_t instr_sb(cpu_t *cpu, instr_t instr)
{
	ptr64_t addr;
	addr.ptr = cpu->regs[instr.i.rs].val + sign_extend_16_64(instr.i.imm);
	
	return cpu_write_mem8(cpu, addr, (uint8_t) cpu->regs[instr.i.rt].lo,
	    true);
}

static void mnemonics_sb(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "sb");
	disassemble_rt_offset_base(instr, mnemonics, comments);
}
