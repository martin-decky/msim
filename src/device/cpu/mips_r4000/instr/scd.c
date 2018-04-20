static exc_t instr_scd(r4k_cpu_t *cpu, instr_t instr)
{
	if (CPU_64BIT_INSTRUCTION(cpu)) {
		if (!cpu->llbit) {
			/* If we are not tracking LLD-SCD,
			   then SC has to fail */
			cpu->regs[instr.i.rt].val = 0;
			return excNone;
		}
		
		/* We do track LLD-SCD address */
		
		/* Compute target address */
		ptr64_t addr;
		addr.ptr = cpu->regs[instr.i.rs].val + sign_extend_16_64(instr.i.imm);
		
		/* Perform the write operation */
		exc_t res = cpu_write_mem64(cpu, addr, cpu->regs[instr.i.rt].val, true);
		if (res == excNone) {
			/* The operation has been successful,
			   write the result, but ... */
			cpu->regs[instr.i.rt].val = 1;
			
			/* ... we are too polite if LLD and SCD addresses differ.
			   In such a case, the behaviour of SCD is undefined.
			   Let's check that. */
			ptr36_t phys;
			convert_addr(cpu, addr, &phys, false, false);
		
			/* sc_addr now contains physical target address */
			if (phys != cpu->lladdr) {
				/* LLD and SCD addresses do not match ;( */
				alert("R4000: LLD/SCD addresses do not match");
			}
		}
		
		/* SCD always stops LLD-SCD address tracking */
		sc_unregister(cpu);
		cpu->llbit = false;
		
		return res;
	}
	
	return excRI;
}

static void mnemonics_scd(ptr64_t addr, instr_t instr,
    string_t *mnemonics, string_t *comments)
{
	string_printf(mnemonics, "scd");
	disassemble_rt_offset_base(instr, mnemonics, comments);
}
