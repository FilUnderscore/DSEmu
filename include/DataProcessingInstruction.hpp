#ifndef INCLUDE_DATAPROCESSINGINSTRUCTION_HPP_
#define INCLUDE_DATAPROCESSINGINSTRUCTION_HPP_

#include <cstdint>

using namespace std;

#include "Instruction.hpp"

namespace CPU
{
	class DataProcessingInstruction : public Instruction
	{
	public:
		DataProcessingInstruction(uint32_t instruction, uint8_t cond, uint8_t opcode, uint8_t s, uint8_t rd, uint8_t rn, uint8_t rotate4, uint8_t immediate8, uint8_t shift, uint8_t rs, uint8_t sh, uint8_t rm);
		~DataProcessingInstruction();

		void calculate();

		bool execute(ARM* arm);

		uint8_t getOpcode();

		uint8_t getDestinationRegister();

		uint8_t getFirstOperandRegister();

		uint32_t getValue();
	
	private:
		Operation* operation;

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