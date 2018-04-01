#include <DataProcessingInstruction.hpp>

#include <ARM.hpp>
#include <Logger.hpp>
#include <limits>

using namespace CPU;

using std::numeric_limits;

DataProcessingInstruction::DataProcessingInstruction(uint32_t instruction, uint8_t cond, uint8_t opcode, uint8_t s, uint8_t rd, uint8_t rn, uint8_t rotate4, uint8_t immediate8, uint8_t shift, uint8_t rs, uint8_t sh, uint8_t rm) : Instruction(instruction, cond)
{
	this->opcode = opcode;

	this->s = s;

	this->rd = rd;
	this->rn = rn;

	this->rotate4 = rotate4;
	this->immediate8 = immediate8;

	this->shift = shift;
	this->rs = rs;
	this->sh = sh;
	this->rm = rm;
}

DataProcessingInstruction::~DataProcessingInstruction()
{

}

bool DataProcessingInstruction::execute(ARM* arm)
{
	if(!Instruction::execute(arm))
	{
		Logger::log("DataProcessingInstruction cancelled.");

		return false;
	}

	switch(this->executionStage)
	{
		case ::EX:
		{
			if(((this->instruction >> 25) & 0x01) == 0x00)
			{
				uint32_t rm = arm->getRegister((Register) this->rm);

				if(((this->instruction >> 4) & 0x01) == 0x01)
				{
					// Calculate shift
					uint32_t rs = arm->getRegister((Register) this->rs);
					rs &= 0x0F;
					arm->getALU()->calculateShiftRegister(rm, rs, this->sh);

					this->carry = arm->getALU()->getCarry();
					this->operand2 = arm->getALU()->getResult();
				}
				else
				{
					arm->getALU()->calculateShiftAmount(rm, this->shift, this->sh);
					
					this->carry = arm->getALU()->getCarry();
					this->operand2 = arm->getALU()->getResult();
				}
			}
			else
			{
				arm->getALU()->calculateImmediate(this->immediate8, this->rotate4);

				this->carry = arm->getALU()->getCarry();
				this->operand2 = arm->getALU()->getResult();
			}

			// Calculate result and carry
			uint32_t rn = arm->getRegister((Register) this->getFirstOperandRegister());
			arm->getALU()->calculateOperation((Opcode) this->opcode, rn, this->getOperand2(), this->carry);

			this->carry = arm->getALU()->getCarry();
			this->result = arm->getALU()->getResult();

			break;
		}

		case ::MEM:
		{
			break;
		}

		case ::WB:
		{
			arm->setRegister((Register) this->getDestinationRegister(), this->result);
		
			if(this->s == 0x01)
			{
				// Set condition codes in CPSR
				uint32_t cpsr = arm->getRegister(::CPSR);

				/*
				if(this->operation->getOptype() == ::LOGICAL)
				{
					//Bit 31 (Negative flag)
					// Set to Bit 31 of the result.
					cpsr |= ((result >> 31) << 31);

					// Bit 30 (Zero flag)
					// Set Zero flag if the result is 0.
					cpsr |= ((result == 0x00) << 30);

					// TODO: Bit 29 and Bit 28
				}
				else if(this->operation->getOptype() == ::ARITHMETIC)
				{
					// Bit 31 (Negative flag)
					// Set to Bit 31 of the result.
					cpsr |= ((result >> 31) << 31);

					// Bit 30 (Zero flag)
					// Set Zero flag if the result is 0.
					cpsr |= ((result == 0x00) << 30);

					// Bit 29 (Carry flag)
					// Set Carry flag of carry out bit 31 in ALU (TODO)
					cpsr |= ((result >> 31) << 29);

					if(this->rd != ::PC)
					{
						// Bit 28 (Overflow flag)
						// Set Overflow flag if RD is not R15 and bit 31 of result will set the CPSR if the result is overflow.
						cpsr |= ((result >> 31) << 28);
					}
				}
				*/

				arm->setRegister(::CPSR, cpsr);
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

uint8_t DataProcessingInstruction::getOpcode()
{
	return this->opcode;
}

uint8_t DataProcessingInstruction::getDestinationRegister()
{
	return this->rd;
}

uint8_t DataProcessingInstruction::getFirstOperandRegister()
{
	return this->rn;
}

uint32_t DataProcessingInstruction::getOperand2()
{
	return this->operand2;
}