#include <InstructionDecoder.hpp>

#include <Logger.hpp>

#include <string>

using namespace std;

#include <iostream>
#include <bitset>

#include <Opcode.hpp>

#include <Operation.hpp>

#include <BOperation.hpp>

Instruction* InstructionDecoder::decode(uint32_t instruction)
{
	// Convert Instruction to Little Endian (ARM native endianness)
	instruction = ((instruction << 8) & 0xFF00FF00) | ((instruction >> 8) & 0xFF00FF);
	instruction = (instruction << 16) | (instruction >> 16);

	Operation* operation = NULL;

	// Bits 31-28 are condition.
	uint8_t cond = (instruction >> 28) & 0x0F;
	
	uint8_t opcode = 0;
	
	uint8_t s = 0;

	uint8_t rd = 0;
	uint8_t rn = 0;

	uint8_t rotate4 = 0;
	uint8_t immediate8 = 0;

	uint8_t shift = 0;
	uint8_t rs = 0;
	uint8_t sh = 0;
	uint8_t rm = 0;

	// Check if Instruction is a Branch or Data Processing Instruction
	if(((instruction >> 26) & 0x03) != 0x00)
	{
		if(((instruction >> 24) & 0x01) == 0x00)
		{
			// Branch Instruction (B)

			operation = new BOperation();
		}
		else
		{
			// Branch Link Instruction (BL)
			operation = new BOperation();
		}
	}
	else
	{
		// Bits 21-24 are opcode.
		opcode = (instruction >> 21) & 0x0F;

		// Bit 20 is the set condition codes bit.	
		s = (instruction >> 20) & 0x01;

		// Bits 16-19 are 1st operand register.
		rn = (instruction >> 16) & 0x0F;

		// Bits 12-15 are destination register.
		rd = (instruction >> 12) & 0x0F;
	
		// Check if there is an immediate value or shift
		if(((instruction >> 25) & 0x0F) == 0x01)
		{
			// Bits 8-11 are rotate (4 bits)
			rotate4 = (instruction >> 8) & 0x0F;

			// Bits 7-0 are immediate (8 bits)
			immediate8 = instruction & 0xFF;
		}
		else
		{
			// Check if Immediate Shift Length or Register Shift Length is used
			if(((instruction >> 4) & 0x01) == 0x01)
			{
				shift = (instruction >> 7) & 0x1F;
			}
			else
			{
				rs = (instruction >> 8) & 0x0F;
			}


			sh = (instruction >> 5) & 0x03;

			rm = instruction & 0x0F;
		}
	}

	std::cout << "Instruction (BINARY): " << std::bitset<32>(instruction) << endl;

	Instruction* decodedInstruction = new Instruction(instruction, operation, cond, opcode, s, rd, rn, rotate4, immediate8, shift, rs, sh, rm);

	return decodedInstruction;
}