#include <SingleDataTransferInstruction.hpp>

#include <ARM.hpp>
#include <Bits.hpp>
#include <String.hpp>
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

		Logger::log("OFFSET: " + to_string(this->immediate12));
	}	
	else if(this->i == 0x01)
	{
		// Offset is a register.
	}
}

void SingleDataTransferInstruction::addOffset(ARM* arm)
{
	if(!this->u)
	{
		// Down; subtract offset from base register value
				
		uint32_t rn = arm->getRegister((Register) this->rn);

		this->address = rn - this->offset;
	}
	else if(this->u)
	{
		// Up; add offset to base register value

		uint32_t rn = arm->getRegister((Register) this->rn);

		this->address = rn + this->offset;
	}
}

bool SingleDataTransferInstruction::execute(ARM* arm)
{
	if(!Instruction::execute(arm))
	{
		Logger::log("SingleDataTransferInstruction cancelled.");

		return false;
	}

	switch(this->executionStage)
	{
		case ::EX:
		{
			this->calculateOffset();

			// Calculate address

			if(this->offset == 0x00)
			{
				// Zero offset
				// Value in RN is used as the address for the transfer.

				uint32_t rn = arm->getRegister((Register) this->rn);

				this->address = rn;
			}
			else
			{
				if(this->p == 0x01)
				{
					// Add offset before transfer.

					this->addOffset(arm);
				}
			}

			break;
		}

		case ::MEM:
		{
			if(this->l == 0x00)
			{
				// Store to memory

				uint32_t value = arm->getRegister((Register) this->rd);

				// Load value into memory

				if(this->b == 0x00)
				{
					// Transfer word quantity (32 bits)

					uint8_t* valueBits = Bits::from32UBits(value); 

					if(!arm->getMemory()->write(this->address, valueBits, sizeof(uint32_t)))
					{
						Logger::log("Failed to transfer word (Single Data Transfer) to out of range memory address: " + String::decToHex(this->address));

						// Free memory
						delete valueBits;
						valueBits = NULL;

						return false;
					}

					// Free memory
					delete valueBits;
					valueBits = NULL;
				}
				else if(this->b == 0x01)
				{
					// Transfer byte quantity (8 bits)

					uint8_t* valueBits = Bits::from8UBits(value);

					if(!arm->getMemory()->write(this->address, valueBits, sizeof(uint8_t)))
					{
						Logger::log("Failed to transfer byte (Single Data Transfer) to out of range memory address: " + String::decToHex(this->address));

						// Free memory
						delete valueBits;
						valueBits = NULL;

						return false;
					}

					// Free memory
					delete valueBits;
					valueBits = NULL;
				}
			}
			else if(this->l == 0x01)
			{
				// Load from memory

				if(this->b == 0x00)
				{
					// Transfer word quantity (32 bits)

					Memory* memory = arm->getMemory()->getMemory(this->address);

					if(memory == NULL)
					{
						Logger::log("Failed to transfer word (Single Data Transfer) from out of range memory address: " + String::decToHex(this->address));

						return false;
					}

					uint32_t address = this->address - memory->getStartAddress();

					uint8_t valueBits[sizeof(uint32_t)] = {};

					memcpy(valueBits, memory->getMemory()->get() + address, sizeof(valueBits));

					this->value = Bits::to32UBits(valueBits);
				}
				else if(this->b == 0x01)
				{
					// Transfer byte quantity (8 bits)

					Memory* memory = arm->getMemory()->getMemory(this->address);

					if(memory == NULL)
					{
						Logger::log("Failed to transfer byte (Single Data Transfer) from out of range memory address: " + String::decToHex(this->address));

						return false;
					}

					uint32_t address = this->address - memory->getStartAddress();

					uint8_t valueBits[sizeof(uint8_t)] = {};

					memcpy(valueBits, memory->getMemory()->get() + address, sizeof(valueBits));

					this->value = Bits::to8UBits(valueBits);
				}
			}

			break;
		}

		case ::WB:
		{
			if(this->p == 0x00)
			{
				// Add offset after transfer.

				this->addOffset(arm);
			}

			if(this->l == 0x01)
			{
				// Write back value loaded from memory into destination register.

				arm->setRegister((Register) this->rd, this->value);
			}

			if(this->w == 0x01)
			{
				if(this->rn == 0x15)
				{
					// Can't write address into R15 (PC)
					return false;
				}

				// Write back address into Base register (RN)
				arm->setRegister((Register) this->rn, this->address);
			}

			break;
		}

		default:
		{
			break;
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