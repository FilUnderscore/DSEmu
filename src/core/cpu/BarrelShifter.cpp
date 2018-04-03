#include <BarrelShifter.hpp>

#include <ARM.hpp>

BarrelShifter::BarrelShifter(CPU::ARM* arm)
{
	this->arm = arm;

	// Shift by 16 (10001) bits left (00) right (01)
	// Shift by 17 (10001) bits left (00) right (01)
	shift(0xFFFF0000, 0b10001010);

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

			Logger::log("Result: " + to_string(this->result));
			Logger::log("Bitset: " + std::bitset<32>(this->result).to_string());

			// LSB discarded bit is carry out
			this->carry = (rm >> (32 - shiftAmount)) & 0x01;

			Logger::log("Carry: " + to_string(this->carry));
			Logger::log("Bitset: " + std::bitset<32>(this->carry).to_string());

			break;
		}

		// Logical right
		case 0x01:
		{
			Logger::log("RM: " + to_string(rm));
			Logger::log("Bitset: " + std::bitset<32>(rm).to_string());

			this->result = (rm >> shiftAmount);

			Logger::log("Result: " + to_string(this->result));
			Logger::log("Bitset: " + std::bitset<32>(this->result).to_string());

			// MSB discarded bit is carry out
			this->carry = (rm >> (31 + shiftAmount)) & 0x01;

			Logger::log("Carry: " + to_string(this->carry));
			Logger::log("Bitset: " + std::bitset<32>(this->carry).to_string());

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