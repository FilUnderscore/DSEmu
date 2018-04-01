#ifndef INCLUDE_ALU_HPP_
#define INCLUDE_ALU_HPP_

#include <Opcode.hpp>
#include <cstdint>

using namespace CPU;

class ALU
{
public:
	ALU();
	~ALU();

	void calculateImmediate(uint8_t immediate8, uint8_t rotate4);

	uint32_t calculateShiftAmount(uint8_t rm, uint8_t shiftAmount, uint8_t shiftType, uint32_t cpsr);

	uint32_t calculateShiftRegister(uint8_t rm, uint8_t rs, uint8_t shiftType, uint32_t cpsr);

	uint32_t calculateOperation(Opcode opcode, uint32_t operand1, uint32_t operand2, uint32_t carry, bool s, uint32_t cpsr);

	uint32_t getOperand1();

	uint32_t getOperand2();

	uint32_t getCarry();

	uint32_t getResult();

private:
	uint32_t aluResult;

	uint32_t operand1;
	uint32_t operand2;
	uint32_t carry;
	uint32_t result;
};

#endif