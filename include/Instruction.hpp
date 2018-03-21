#ifndef INCLUDE_INSTRUCTION_HPP_
#define INCLUDE_INSTRUCTION_HPP_

#include <cstdint>

using namespace std;

#include "Operation.hpp"

namespace CPU
{
	class Instruction
	{
	public:
		Instruction(uint32_t instruction, uint8_t cond);
		virtual ~Instruction();

		uint32_t getInstruction();

		uint8_t getCondition();
	
	protected:
		uint32_t instruction;

		uint8_t cond;
	};
}

#endif