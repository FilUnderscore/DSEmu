#include "include\ALU.hpp"

#include "include\ARM.hpp"
#include "include\Bits.hpp"

using namespace CPU;

ALU::ALU(CPU::ARM* arm)
{
	this->arm = arm;
}

ALU::~ALU()
{

}

void ALU::calculateImmediate(uint8_t immediate8, uint8_t rotate4)
{
	this->result = Bits::ror32UBits(immediate8, (rotate4 * 2));
}

uint32_t ALU::calculateOperation(Opcode opcode, uint32_t operand1, uint32_t operand2, uint32_t carry, bool s, uint32_t cpsr)
{
	// TODO: Implement CPSR flags

	this->operand1 = operand1;
	this->operand2 = operand2;
	this->carry = carry;

	switch(opcode)
	{
		case ::AND:
		{
			break;
		}

		case ::EOR:
		{
			break;
		}

		case ::SUB:
		{
			this->aluResult = operand1 - operand2;
			
			if(operand1 == 0)
			{
				this->result = 0;
			}
			else
			{
				this->result = this->aluResult;
			}

			break;
		}

		case ::RSB:
		{
			break;
		}

		case ::ADD:
		{
			break;
		}

		case ::ADC:
		{
			break;
		}

		case ::SBC:
		{
			break;
		}

		case ::RSC:
		{
			break;
		}

		case ::TST:
		{
			break;
		}

		case ::TEQ:
		{
			break;
		}

		case ::CMP:
		{
			break;
		}

		case ::CMN:
		{
			break;
		}

		case ::ORR:
		{
			break;
		}

		case ::MOV:
		{
			this->aluResult = operand2;
			this->result = aluResult;

			break;
		}

		case ::BIC:
		{
			break;
		}

		case ::MVN:
		{
			break;
		}

		default:
		{
			break;
		}
	}

	// Set condition codes
	if(s)
	{
		switch(opcode)
		{
			case ::AND:
			case ::EOR:
			case ::TST:
			case ::TEQ:
			case ::ORR:
			case ::MOV:
			case ::BIC:
			case ::MVN:
			{
				// Logical operations

				// Negative flag (Bit31)
				cpsr |= ((this->result >> 31) << 31);

				// Zero flag (Bit30)
				cpsr |= ((this->result == 0x00) << 30);

				// Carry flag (Bit29)
				// Set from barrel shifter carry value
				cpsr |= (carry << 29);

				// Overflow flag (Bit28)
				// TODO: If the S bit is set (and Rd is not R15), the V (Overflow) flag in the CPSR will be unaffected.

				break;
			}

			case ::SUB:
			case ::RSB:
			case ::ADD:
			case ::ADC:
			case ::SBC:
			case ::RSC:
			case ::CMP:
			case ::CMN:
			{
				// Arithmetic operations

				// Negative flag (Bit31)
				// Set to bit31 of the result
				cpsr |= ((this->result >> 31) << 31);

				// Zero flag (Bit30)
				cpsr |= ((this->result == 0x00) << 30);

				// Carry flag (Bit29)
				// Set to carry out of bit31 of the ALU
				cpsr |= ((this->aluResult >> 31) << 29);

				// Overflow flag (Bit28)
				// Only if operands were considered signed
				// Ignored if operands were considered unsigned
				if(((operand1 >> 31) & 0x01) == (((operand2) >> 31) & 0x01))
				{
					// If the result does not match the same signs as the operands, overflow has occurred.
					cpsr |= ((((this->result >> 31) & 0x01) != ((operand1 >> 31) & 0x01)) << 28);
				}
				else
				{
					// Both operands have different signs, indicating overflow.

					cpsr |= (1 << 28);
				}

				break;
			}

			default:
			{
				break;
			}
		}
	}

	// TODO: Handle carry

	return cpsr;
}

uint32_t ALU::getOperand1()
{
	return this->operand1;
}

uint32_t ALU::getOperand2()
{
	return this->operand2;
}

uint32_t ALU::getCarry()
{
	return this->carry;
}

uint32_t ALU::getResult()
{
	return this->result;
}