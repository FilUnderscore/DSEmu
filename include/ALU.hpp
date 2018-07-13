#ifndef INCLUDE_ALU_HPP_
#define INCLUDE_ALU_HPP_

#include "Opcode.hpp"
#include "ARM.hpp"
#include <cstdint>

using CPU::ARM;
using CPU::Opcode;

class ALU
{
public:
	ALU(CPU::ARM* arm);
	~ALU();

	void calculateImmediate(uint8_t immediate8, uint8_t rotate4);

	uint32_t calculateOperation(Opcode opcode, uint32_t operand1, uint32_t operand2, uint32_t carry, bool s, uint32_t cpsr);

	uint32_t getOperand1();

	uint32_t getOperand2();

	uint32_t getCarry();

	uint32_t getResult();

private:
	CPU::ARM* arm;

	uint32_t aluResult;

	uint32_t operand1;
	uint32_t operand2;
	uint32_t carry;
	uint32_t result;
};

#endif