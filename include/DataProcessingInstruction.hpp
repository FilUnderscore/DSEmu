#ifndef INCLUDE_DATAPROCESSINGINSTRUCTION_HPP_
#define INCLUDE_DATAPROCESSINGINSTRUCTION_HPP_

#include "Instruction.hpp"
#include <cstdint>

namespace CPU
{
	class DataProcessingInstruction : public Instruction
	{
	public:
		DataProcessingInstruction(uint32_t instruction, uint8_t cond, uint8_t opcode, uint8_t s, uint8_t rd, uint8_t rn, uint8_t rotate4, uint8_t immediate8, uint8_t shift, uint8_t rs, uint8_t sh, uint8_t rm);
		~DataProcessingInstruction();

		bool execute(ARM* arm);

		uint8_t getOpcode();

		uint8_t getDestinationRegister();

		uint8_t getFirstOperandRegister();

		uint32_t getOperand2();
	
	private:
		uint8_t opcode;

		uint8_t s;

		uint8_t rd;
		uint8_t rn;

		uint32_t operand2;

		uint8_t rotate4;
		uint8_t immediate8;

		uint8_t shift;
		uint8_t rs;
		uint8_t sh;
		uint8_t rm;

		uint32_t cpsr;

		uint32_t carry;
		uint32_t result;
	};
}

#endif