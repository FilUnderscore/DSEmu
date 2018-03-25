#ifndef INCLUDE_HALFWORDDATATRANSFERINSTRUCTION_HPP_
#define INCLUDE_HALFWORDDATATRANSFERINSTRUCTION_HPP_

#include "Instruction.hpp"

using namespace CPU;

namespace CPU
{
	class HalfwordDataTransferInstruction : public Instruction
	{
	public:
		HalfwordDataTransferInstruction(uint32_t instruction, uint8_t cond, uint8_t p, uint8_t u, uint8_t w, uint8_t l, uint8_t rn, uint8_t rd, uint8_t s, uint8_t h, uint8_t rm, uint8_t offset);
		~HalfwordDataTransferInstruction();

		bool execute(ARM* arm);
	private:
		uint8_t p;
		uint8_t u;
		uint8_t w;
		uint8_t l;
		uint8_t rn;
		uint8_t rd;
		uint8_t s;
		uint8_t h;
		uint8_t rm;
		uint8_t offset;
	};
}

#endif