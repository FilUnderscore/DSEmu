#ifndef INCLUDE_BRANCHINSTRUCTION_HPP_
#define INCLUDE_BRANCHINSTRUCTION_HPP_

#include "Instruction.hpp"

namespace CPU
{
	class BranchInstruction : public Instruction
	{
	public:
		BranchInstruction(uint32_t instruction, uint8_t cond, uint8_t l, uint32_t offset);
		~BranchInstruction();

		void calculate();

		bool isWithLink();

		uint32_t getOffset();

	private:
		uint8_t l;

		uint32_t offset;
	};
}

#endif