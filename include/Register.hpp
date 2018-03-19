#ifndef INCLUDE_REGISTER_HPP_
#define INCLUDE_REGISTER_HPP_

namespace CPU
{
	enum Register
	{
		/*
		 * Lo registers
		 *
		 * May be accessed freely in THUMB mode
		 */
		R0,
		R1,
		R2,
		R3,
		R4,
		R5,
		R6,
		R7,

		/*
		 * Hi registers
		 *
		 * Can be accessed only by some instructions in THUMB mode
		 */
		R8,
		R9,
		R10,
		R11,
		R12,

		/*
		 * SP (Stack Pointer) in THUMB state
		 *
		 * In ARM state, the register or other register(s) can be used as stack pointer(s) or as general purpose register(s).
		 */
		SP,

		/*
		 * LR (Link Register) in THUMB mode
		 *
		 * In ARM mode, may be used as a general purpose register, provided that the usage of LR register isn't required.
		 */
		LR,

		/*
		 * Program Counter
		 *
		 * usually returns a value of PC + nn because of read-ahead (pipelining)
		 *
		 * 'nn' depends on instruction and on the CPU state (ARM or THUMB)
		 */
		PC,

		/*
		 * Current Processor Status Register
		 *
		 * Bit 0 = Negative Flag (The result of the operation is 0, which is considered positive, so the N bit is set to 0.)
		 * Bit 1 = Zero Flag (The result of the operation is 0, so the Z bit is set to 1.)
		 * Bit 2 = (Unsigned Overflow) Carry Flag (Data loss because the result did not fit into 32 bits, so the processor indicates this by setting C bit to 1.)
		 * Bit 3 = (Signed) Overflow Flag (From a signed-artithmetic viewpoint, 0xffffffff really means -1, so the operation was (-1) + 1 = 0. The operation does not overflow, so V bit is set to 0.)
		 */
		CPSR,
		
		SPSR,
	};
}

#endif