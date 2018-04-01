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
			uint32_t cpsr = arm->getRegister(::CPSR);

			if(((this->instruction >> 25) & 0x01) == 0x00)
			{
				uint32_t rm = arm->getRegister((Register) this->rm);

				if(((this->instruction >> 4) & 0x01) == 0x01)
				{
					// Calculate shift
					uint32_t rs = arm->getRegister((Register) this->rs);
					rs &= 0x0F;
					this->cpsr = arm->getALU()->calculateShiftRegister(rm, rs, this->sh, cpsr);

					this->carry = arm->getALU()->getCarry();
					this->operand2 = arm->getALU()->getResult();
				}
				else
				{
					this->cpsr = arm->getALU()->calculateShiftAmount(rm, this->shift, this->sh, cpsr);
					
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
			this->cpsr = arm->getALU()->calculateOperation((Opcode) this->opcode, rn, this->getOperand2(), this->carry, this->s, cpsr);

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
				arm->setRegister(::CPSR, this->cpsr);
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