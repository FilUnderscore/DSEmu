#ifndef INCLUDE_BARRELSHIFTER_HPP_
#define INCLUDE_BARRELSHIFTER_HPP_

#include "ARM.hpp"
#include <cstdint>

using CPU::ARM;

class BarrelShifter
{
public:
	BarrelShifter(CPU::ARM* arm);
	~BarrelShifter();
	
	void shift(uint32_t rm, uint8_t shift);

	uint8_t getCarry();
	uint32_t getResult();

private:
	CPU::ARM* arm;

	// Carry can be uint8_t?
	uint8_t carry;
	uint32_t result;
};

#endif