#include <HalfwordDataTransferInstruction.hpp>

using namespace CPU;

HalfwordDataTransferInstruction::HalfwordDataTransferInstruction(uint32_t instruction, uint8_t cond, uint8_t p, uint8_t u, uint8_t w, uint8_t l, uint8_t rn, uint8_t rd, uint8_t s, uint8_t h, uint8_t rm, uint8_t offset) : Instruction(instruction, cond)
{
	this->p = p;
	this->u = u;
	this->w = w;
	this->l = l;
	this->rn = rn;
	this->rd = rd;
	this->s = s;
	this->h = h;
	this->rm = rm;
	this->offset = offset;
}

HalfwordDataTransferInstruction::~HalfwordDataTransferInstruction()
{

}

void HalfwordDataTransferInstruction::calculate(ARM* arm)
{
	if(((this->instruction >> 22) & 0x01) == 0x00)
	{
		// Register Offset

		this->offset = 0;
	}
	else if(((this->instruction >> 22) & 0x01) == 0x01)
	{
		// Immediate Offset

		// this->offset is Immediate Offset (low nibble)

		// Immediate Offset (high nibble)
		uint32_t hiImmediateOffset = ((this->instruction >> 8) & 0x0F);

		// Concatenate bits 11-8 and 3-0 (bit 11 = MSB, bit 0 = LSB)
		this->offset = hiImmediateOffset | this->offset;
	}
}

bool HalfwordDataTransferInstruction::execute(ARM* arm)
{
	if(!Instruction::execute(arm))
	{
		Logger::log("HalfwordDataTransferInstruction cancelled.");

		return false;
	}

	switch(this->executionStage)
	{
		case ::EX:
		{
			this->calculate(arm);

			break;
		}

		case ::MEM:
		{
			break;
		}

		case ::WB:
		{
			break;
		}

		default:
		{
			break;
		}
	}

	return true;
}