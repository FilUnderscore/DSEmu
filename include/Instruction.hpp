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
		Instruction(uint32_t instruction, Operation* operation, uint8_t cond, uint8_t opcode, uint8_t s, uint8_t rd, uint8_t rn, uint8_t rotate4, uint8_t immediate8, uint8_t shift, uint8_t rs, uint8_t sh, uint8_t rm);
		~Instruction();

		void calculate();

		uint32_t getInstruction();

		Operation* getOperation();

		uint8_t getOpcode();

		uint8_t getDestinationRegister();

		uint8_t getFirstOperandRegister();

		uint32_t getValue();
	
	private:
		uint32_t instruction;

		Operation* operation;

		uint8_t cond;

		uint8_t opcode;

		uint8_t s;

		uint8_t rd;
		uint8_t rn;

		uint8_t rotate4;
		uint8_t immediate8;

		uint8_t shift;
		uint8_t rs;
		uint8_t sh;
		uint8_t rm;

		uint32_t value;
	};
}

#endif