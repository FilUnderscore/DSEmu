#ifndef INCLUDE_INSTRUCTION_HPP_
#define INCLUDE_INSTRUCTION_HPP_

#include <cstdint>

using namespace std;

namespace CPU
{
	class Instruction
	{
	public:
		Instruction(uint8_t opcode, uint8_t type, uint8_t rd, uint8_t rn, uint8_t rotate4, uint8_t immediate8);
		~Instruction();

		void calculate();

		uint8_t getOpcode();

		uint8_t getType();

		uint8_t getDestinationRegister();

		uint8_t getFirstOperandRegister();

		uint32_t getValue();
	
	private:
		uint8_t opcode;

		uint8_t type;

		uint8_t rd;
		uint8_t rn;

		uint8_t rotate4;
		uint8_t immediate8;

		uint32_t value;
	};
}

#endif