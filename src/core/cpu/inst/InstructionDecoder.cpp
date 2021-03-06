#include "include\InstructionDecoder.hpp"

#include "include\Opcode.hpp"
#include "include\BranchInstruction.hpp"
#include "include\DataProcessingInstruction.hpp"
#include "include\HalfwordDataTransferInstruction.hpp"
#include "include\SingleDataTransferInstruction.hpp"
#include "include\String.hpp"
#include "include\Logger.hpp"
#include <string>
#include <iostream>
#include <bitset>

using namespace std;

Instruction* InstructionDecoder::decode(uint32_t instruction)
{
	// Convert Instruction to Little Endian (ARM native endianness)
	instruction = ((instruction << 8) & 0xFF00FF00) | ((instruction >> 8) & 0xFF00FF);
	instruction = (instruction << 16) | (instruction >> 16);

	Logger::log("Instruction [LE] (HEX): " + String::decToHex(instruction));
	Logger::log("Instruction [LE] (BINARY): " + std::bitset<32>(instruction).to_string());

	// Bits 31-28 are condition.
	uint8_t cond = (instruction >> 28) & 0x0F;

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

					HalfwordDataTransferInstruction* halfwordDataTransferInstruction = new HalfwordDataTransferInstruction(instruction, cond, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

					Logger::log("HDT");

					return halfwordDataTransferInstruction;
				}
			}
		}
	}


	// Data Processing / PSR Transfer
	if(((instruction >> 26) & 0x03) == 0x00)
	{
		uint8_t rotate4 = 0;
		uint8_t immediate8 = 0;

		uint8_t shift = 0;
		uint8_t rm = 0;

		// Bit 25 is Immediate Operand.
		uint8_t i = (instruction >> 25) & 0x01;

		// Bits 21-24 are opcode.
		uint8_t opcode = (instruction >> 21) & 0x0F;

		// Bit 20 is the set condition codes bit.	
		uint8_t s = (instruction >> 20) & 0x01;

		// Bits 16-19 are 1st operand register.
		uint8_t rn = (instruction >> 16) & 0x0F;

		// Bits 12-15 are destination register.
		uint8_t rd = (instruction >> 12) & 0x0F;
	
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
			shift = (instruction >> 4) & 0xFF;

			rm = instruction & 0x0F;
		}


		DataProcessingInstruction* dataProcessingInstruction = new DataProcessingInstruction(instruction, cond, i, opcode, s, rd, rn, rotate4, immediate8, shift, rm);
	
		return dataProcessingInstruction;
	}

	// Multiply Instruction
	if(((instruction >> 22) & 0x3F) == 0x00)
	{
		if(((instruction >> 4) & 0x0F) == 0x09)
		{
			return NULL;
		}
		else
		{
			// Undefined Instruction trap

			return NULL;
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

				return NULL;
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

										return NULL;
									}
								}
							}
						}
					}
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

		uint16_t immediate12 = 0;

		uint8_t shift = 0;
		uint8_t rm = 0;

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
		return NULL;
	}
	// Block Data Transfer
	else if(((instruction >> 25) & 0x07) == 0x04)
	{
		Logger::log("BDT");

		return NULL;
	}
	// Branch
	else if(((instruction >> 25) & 0x07) == 0x05)
	{
		Logger::log("Branch");

		uint8_t l = (instruction >> 24) & 0x01;

		int32_t offset = instruction & 0xFFFFFF;

		BranchInstruction* branchInstruction = new BranchInstruction(instruction, cond, l, offset);

		return branchInstruction;
	}
	// Co-processor Data Transfer
	else if(((instruction >> 25) & 0x07) == 0x06)
	{
		return NULL;
	}

	if(((instruction >> 24) & 0x0F) == 0x0E)
	{
		// Co-processor Data Operation
		if(((instruction >> 4) & 0x01) == 0x00)
		{
			return NULL;
		}
		// Co-processor Register Transfer
		else
		{
			return NULL;
		}
	}

	// Software Interrupt
	if(((instruction >> 24) & 0x0F) == 0x0F)
	{
		uint32_t immediate24 = instruction & 0xFFFFFF;

		return NULL;
	}

	return NULL;
}