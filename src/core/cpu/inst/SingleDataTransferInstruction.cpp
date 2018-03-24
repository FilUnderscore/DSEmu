#include <SingleDataTransferInstruction.hpp>

#include <ARM.hpp>

#include <Bits.hpp>

#include <cstring>

using namespace std;

SingleDataTransferInstruction::SingleDataTransferInstruction(uint32_t instruction, uint8_t cond, uint8_t i, uint8_t p, uint8_t u, uint8_t b, uint8_t w, uint8_t l, uint8_t rn, uint8_t rd, uint16_t immediate12, uint8_t shift, uint8_t rm) : Instruction(instruction, cond)
{
	this->i = i;
	this->p = p;
	this->u = u;
	this->b = b;
	this->w = w;
	this->l = l;
	this->rn = rn;
	this->rd = rd;

	this->immediate12 = immediate12;

	this->shift = shift;
	this->rm = rm;
}

SingleDataTransferInstruction::~SingleDataTransferInstruction()
{

}

void SingleDataTransferInstruction::calculateOffset()
{
	if(this->i == 0x00)
	{
		// Offset is an immediate value.
		this->offset = this->immediate12;
	}	
	else if(this->i == 0x01)
	{
		// Offset is a register.
	}
}

bool SingleDataTransferInstruction::execute(ARM* arm)
{
	Logger::log("SDTI");

	switch(this->executionStage)
	{
		case ::EX:
		{
			this->calculateOffset();

			// Calculate address
		}

		case ::MEM:
		{
			if(this->l == 0x00)
			{
				// Store to memory

				uint32_t value = arm->getRegister((Register) this->rd);

				// Load value into memory

				uint8_t* valueBits = Bits::from32UBits(value); 

				arm->getRAM()->load(valueBits, 4, this->address);

				// Free memory
				delete valueBits;
			}
			else if(this->l == 0x01)
			{
				// Load from memory

				uint8_t valueBits[4] = {};

				memcpy(valueBits, arm->getRAM()->getRAM() + this->address, sizeof(valueBits));

				this->value = Bits::to32UBits(valueBits);
			}
		}

		case ::WB:
		{
			if(this->w == 0x01)
			{
				if(this->rn == 0x15)
				{
					// Can't write address into R15 (PC)
					return false;
				}

				if(this->l == 0x01)
				{
					// Write back value loaded from memory into destination register.
					arm->setRegister((Register) this->rd, this->value);
				}

				// Write back address into Base register (RN)
				arm->setRegister((Register) this->rn, this->address);
			}
		}
	}

	return true;
}

uint8_t SingleDataTransferInstruction::getImmediateOffset()
{
	return this->i;
}

uint8_t SingleDataTransferInstruction::getPrePostIndexingBit()
{
	return this->p;
}

uint8_t SingleDataTransferInstruction::getUpDownBit()
{
	return this->u;
}

uint8_t SingleDataTransferInstruction::getByteWordBit()
{
	return this->b;
}

uint8_t SingleDataTransferInstruction::getWritebackBit()
{
	return this->w;
}

uint8_t SingleDataTransferInstruction::getLoadStoreBit()
{
	return this->l;
}

uint8_t SingleDataTransferInstruction::getBaseRegister()
{
	return this->rn;
}

uint8_t SingleDataTransferInstruction::getSourceDestinationRegister()
{
	return this->rd;
}

uint8_t SingleDataTransferInstruction::getOffset()
{
	return this->offset;
}