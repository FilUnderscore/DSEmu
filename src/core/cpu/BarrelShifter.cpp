#include <BarrelShifter.hpp>

#include <ARM.hpp>

BarrelShifter::BarrelShifter(CPU::ARM* arm)
{
	this->arm = arm;

	// Shift by 16 bits left
	shift(0xFFFF, 0x88);

	exit(0);
}

BarrelShifter::~BarrelShifter()
{

}

#include <Logger.hpp>
#include <bitset>

void BarrelShifter::shift(uint32_t rm, uint8_t shift)
{
	uint8_t isRegister = shift & 0x01;
	uint8_t shiftType = (shift >> 1) & 0x03;
	uint8_t shiftAmount;

	if(isRegister)
	{
		uint8_t rs = (shift >> 4) & 0x0F;

		shiftAmount = arm->getRegister((Register) rs);

		// Shift amount specified in bottom byte of Rs
		shiftAmount &= 0x0F;
	}
	else
	{
		// 5 bit unsigned integer
		shiftAmount = (shift >> 3) & 0x1F;
	}

	switch(shiftType)
	{
		// Logical left
		case 0x00:
		{
			this->result = (rm << shiftAmount);

			// LSB discarded bit is carry out
			this->carry = (rm >> (32 - shiftAmount)) & 0x01;

			break;
		}

		// Logical right
		case 0x01:
		{
			this->result = (rm >> shiftAmount);

			// MSB discarded bit is carry out
			this->carry = 0;

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