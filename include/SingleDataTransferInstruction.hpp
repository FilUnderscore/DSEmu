#ifndef INCLUDE_SINGLEDATATRANSFERINSTRUCTION_HPP_
#define INCLUDE_SINGLEDATATRANSFERINSTRUCTION_HPP_

#include "Instruction.hpp"

using namespace CPU;

namespace CPU
{
	class SingleDataTransferInstruction : public Instruction
	{
	public:
		SingleDataTransferInstruction(uint32_t instruction, uint8_t cond, uint8_t i, uint8_t p, uint8_t u, uint8_t b, uint8_t w, uint8_t l, uint8_t rn, uint8_t rd, uint8_t immediate12, uint8_t shift, uint8_t rm);
		~SingleDataTransferInstruction();
	};
}

#endif