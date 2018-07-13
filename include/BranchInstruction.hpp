#ifndef INCLUDE_BRANCHINSTRUCTION_HPP_
#define INCLUDE_BRANCHINSTRUCTION_HPP_

#include "Instruction.hpp"

namespace CPU
{
	class BranchInstruction : public Instruction
	{
	public:
		BranchInstruction(uint32_t instruction, uint8_t cond, uint8_t l, int32_t offset);
		~BranchInstruction();

		void calculate();

		bool execute(CPU::ARM* arm);

		bool isWithLink();

		int32_t getOffset();

	private:
		uint8_t l;

		int32_t offset;
	};
}

#endif