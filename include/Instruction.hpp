#ifndef INCLUDE_INSTRUCTION_HPP_
#define INCLUDE_INSTRUCTION_HPP_

#include <cstdint>

using namespace std;

#include "Operation.hpp"

#include "InstructionExecutionStage.hpp"

#include "Register.hpp"

#include "Condition.hpp"

namespace CPU
{
	class Instruction
	{
	public:
		Instruction(uint32_t instruction, uint8_t cond);
		virtual ~Instruction();

		virtual bool execute(ARM* arm);

		uint32_t getInstruction();

		Condition getCondition();

		InstructionExecutionStage getExecutionStage();
	
	protected:
		uint32_t instruction;

		Condition cond;

		InstructionExecutionStage executionStage;
	};
}

#endif