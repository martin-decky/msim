static exc_t instr_jal(r4k_cpu_t *cpu, instr_t instr)
{
	cpu->regs[31].val = cpu->pc.ptr + 8;
	cpu->pc_next.ptr =
	    (cpu->pc_next.ptr & TARGET_COMB) | (instr.j.target << TARGET_SHIFT);
	cpu->branch = BRANCH_COND;
	return excJump;
}

static void mnemonics_jal(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "jal");
	disassemble_target(addr, instr, mnemonics, comments);
}
