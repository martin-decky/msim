static exc_t instr_ddivu(cpu_t *cpu, instr_t instr)
{
	if (CPU_64BIT_INSTRUCTION(cpu)) {
		uint64_t rt = cpu->regs[instr.r.rt].val;
		
		if (rt == 0) {
			cpu->loreg.val = 0;
			cpu->hireg.val = 0;
		} else {
			uint64_t rs = cpu->regs[instr.r.rs].val;
			
			cpu->loreg.val = rs / rt;
			cpu->hireg.val = rs % rt;
		}
		
		return excNone;
	}
	
	return excRI;
}

static void mnemonics_ddivu(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "ddivu");
	disassemble_rs_rt(instr, mnemonics, comments);
}
