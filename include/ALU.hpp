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

	void calculateShiftAmount(uint8_t rm, uint8_t shiftAmount, uint8_t shiftType);

	void calculateShiftRegister(uint8_t rm, uint8_t rs, uint8_t shiftType);

	void calculateOperation(Opcode opcode, uint32_t operand1, uint32_t operand2, uint32_t carry);

	uint32_t getOperand1();

	uint32_t getOperand2();

	uint32_t getCarry();

	uint32_t getResult();

private:
	uint32_t operand1;
	uint32_t operand2;
	uint32_t carry;
	uint32_t result;
};

#endif