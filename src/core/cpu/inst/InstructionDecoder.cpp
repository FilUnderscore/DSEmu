#include <InstructionDecoder.hpp>

#include <Logger.hpp>

#include <string>

using namespace std;

#include <iostream>
#include <bitset>

#include <Opcode.hpp>

#include <BranchInstruction.hpp>
#include <DataProcessingInstruction.hpp>
#include <SingleDataTransferInstruction.hpp>

Instruction* InstructionDecoder::decode(uint32_t instruction)
{
	// Convert Instruction to Little Endian (ARM native endianness)
	instruction = ((instruction << 8) & 0xFF00FF00) | ((instruction >> 8) & 0xFF00FF);
	instruction = (instruction << 16) | (instruction >> 16);

	std::cout << "Instruction (BINARY): " << std::bitset<32>(instruction) << endl;

	// Bits 31-28 are condition.
	uint8_t cond = (instruction >> 28) & 0x0F;

	// Data Processing / PSR Transfer
	if(((instruction >> 26) & 0x03) == 0x00)
	{
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


		DataProcessingInstruction* dataProcessingInstruction = new DataProcessingInstruction(instruction, cond, opcode, s, rd, rn, rotate4, immediate8, shift, rs, sh, rm);
	
		return dataProcessingInstruction;
	}

	// Multiply Instruction
	if(((instruction >> 22) & 0x3F) == 0x00)
	{
		if(((instruction >> 4) & 0x0F) == 0x09)
		{

		}
		else
		{
			// Undefined Instruction trap
		}
	}

	// Single Data Swap
	if(((instruction >> 23) & 0x1F) == 0x02)
	{
		if(((instruction >> 4) & 0x0F) == 0x09)
		{
			if(((instruction >> 8) & 0x0F) == 0x00)
			{
				// Single Data Swap
			}
		}
	}

	// Branch and Exchange
	if(((instruction >> 4) & 0x1F) == 0x11)
	{
		if(((instruction >> 9) & 0x0F) == 0x0F)
		{
			if(((instruction >> 13) & 0x01) == 0x01)
			{
				if(((instruction >> 14) & 0x0F) == 0x0F)
				{
					if(((instruction >> 18) & 0x01) == 0x01)
					{
						if(((instruction >> 19) & 0x07) == 0x05)
						{
							if(((instruction >> 22) & 0x01) == 0x00)
							{
								if(((instruction >> 23) & 0x01) == 0x00)
								{
									if(((instruction >> 24) & 0x0F) == 0x01)
									{
										// BX (switch processor state)
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// Halfword Data Transfer
	if(((instruction >> 25) & 0x07) == 0x00)
	{
		if(((instruction >> 4) & 0x01) == 0x01)
		{
			if(((instruction >> 7) & 0x01) == 0x01)
			{
				if(((instruction >> 8) & 0x0F) == 0x00)
				{
					// Halfword and Signed Data Transfer
					// (LDRH/STRH/LDRSB/LDRSH)
				}
			}
		}
	}

	// Single Data Transfer
	if(((instruction >> 26) & 0x03)  == 0x01)
	{
		uint8_t i = (instruction >> 25) & 0x01;
		uint8_t p = (instruction >> 24) & 0x01;
		uint8_t u = (instruction >> 23) & 0x01;
		uint8_t b = (instruction >> 22) & 0x01;
		uint8_t w = (instruction >> 21) & 0x01;
		uint8_t l = (instruction >> 20) & 0x01;

		uint8_t rn = (instruction >> 16) & 0x0F;
		uint8_t rd = (instruction >> 12) & 0x0F;

		uint8_t immediate12;

		uint8_t shift;
		uint8_t rm;

		if(i == 0x00)
		{
			immediate12 = instruction & 0x0FFF;
		}
		else if(i == 0x01)
		{
			shift = (instruction >> 4) & 0xFF;
			rm = instruction & 0x0F;
		}

		SingleDataTransferInstruction* singleDataTransferInstruction = new SingleDataTransferInstruction(instruction, cond, i, p, u, b, w, l, rn, rd , immediate12, shift, rm);

		return singleDataTransferInstruction;
	}

	// Undefined
	if(((instruction >> 25) & 0x07) == 0x03)
	{

	}
	// Block Data Transfer
	else if(((instruction >> 25) & 0x07) == 0x04)
	{

	}
	// Branch
	else if(((instruction >> 25) & 0x07) == 0x05)
	{
		Logger::log("Branch");

		uint8_t l = (instruction >> 24) & 0x01;

		uint32_t offset = instruction & 0xFFFFFF;

		BranchInstruction* branchInstruction = new BranchInstruction(instruction, cond, l, offset);

		return branchInstruction;
	}
	// Co-processor Data Transfer
	else if(((instruction >> 25) & 0x07) == 0x06)
	{

	}

	if(((instruction >> 24) & 0x0F) == 0x0E)
	{
		// Co-processor Data Operation
		if(((instruction >> 4) & 0x01) == 0x00)
		{

		}
		// Co-processor Register Transfer
		else
		{

		}
	}

	// Software Interrupt
	if(((instruction >> 24) & 0x0F) == 0x0F)
	{
		uint32_t immediate24 = instruction & 0xFFFFFF;
	}

	return NULL;
}