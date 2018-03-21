#ifndef INCLUDE_INSTRUCTION_HPP_
#define INCLUDE_INSTRUCTION_HPP_

#include <cstdint>

using namespace std;

#include "Operation.hpp"

#include "InstructionExecutionStage.hpp"

#include "Register.hpp"

namespace CPU
{
	class Instruction
	{
	public:
		Instruction(uint32_t instruction, uint8_t cond);
		virtual ~Instruction();

		virtual void execute(ARM* arm);

		uint32_t getInstruction();

		uint8_t getCondition();

		InstructionExecutionStage getExecutionStage();
	
	protected:
		uint32_t instruction;

		uint8_t cond;

		InstructionExecutionStage executionStage;
	};
}

#endif