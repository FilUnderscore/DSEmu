#include <ALU.hpp>

#include <Bits.hpp>

ALU::ALU()
{

}

ALU::~ALU()
{

}

void ALU::calculateImmediate(uint8_t immediate8, uint8_t rotate4)
{
	this->result = Bits::ror32UBits(immediate8, (rotate4 * 2));
}

void ALU::calculateShiftAmount(uint8_t rm, uint8_t shiftAmount, uint8_t shiftType)
{
	switch(shiftType)
	{
		// Logical left
		case 0x00:
		{
			break;
		}

		// Logical right
		case 0x01:
		{
			break;
		}

		// Arithmetic right
		case 0x02:
		{
			break;
		}

		// Rotate right
		case 0x03:
		{
			break;
		}

		default:
		{
			break;
		}
	}
}

void ALU::calculateShiftRegister(uint8_t rm, uint8_t rs, uint8_t shiftType)
{
	switch(shiftType)
	{
		// Logical left
		case 0x00:
		{
			break;
		}

		// Logical right
		case 0x01:
		{
			break;
		}

		// Arithmetic right
		case 0x02:
		{
			break;
		}

		// Rotate right
		case 0x03:
		{
			break;
		}

		default:
		{
			break;
		}
	}
}

void ALU::calculateOperation(Opcode opcode, uint32_t operand1, uint32_t operand2, uint32_t carry)
{
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
			this->result = operand1 - operand2;

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
			this->result = operand2;

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