#include <InstructionDecoder.hpp>

#include <Logger.hpp>

#include <string>

using namespace std;

#include <iostream>
#include <bitset>

Instruction* InstructionDecoder::decode(uint32_t instruction)
{
	// Bits 0-7 are opcode.
	uint8_t opcode = instruction & 0xFF;

	// Bits 20-23 are destination register.
	uint8_t rd = (instruction >> 20) & 0x0F;

	// Bits 8-11 are 1st operand register.
	uint8_t rn = (instruction >> 8) & 0x0F;

	// Bits 12-15 are type?
	uint8_t type = (instruction >> 12) & 0x0F;

	// Bits 16-19 are rotate (4 bits)
	uint8_t rotate4 = (instruction >> 16) & 0x0F;

	// Bits 24-31 are immediate (8 bits)
	uint8_t immediate8 = (instruction >> 24) & 0xFF;

	Instruction* decodedInstruction = new Instruction(opcode, type, rd, rn, rotate4, immediate8);

	return decodedInstruction;
}