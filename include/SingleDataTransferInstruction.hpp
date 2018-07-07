#ifndef INCLUDE_SINGLEDATATRANSFERINSTRUCTION_HPP_
#define INCLUDE_SINGLEDATATRANSFERINSTRUCTION_HPP_

#include "Instruction.hpp"

using namespace CPU;

namespace CPU
{
	class SingleDataTransferInstruction : public Instruction
	{
	public:
		SingleDataTransferInstruction(uint32_t instruction, uint8_t cond, uint8_t i, uint8_t p, uint8_t u, uint8_t b, uint8_t w, uint8_t l, uint8_t rn, uint8_t rd, uint16_t immediate12, uint8_t shift, uint8_t rm);
		~SingleDataTransferInstruction();

		void calculateOffset(ARM* arm);

		void addOffset(ARM* arm);

		bool execute(ARM* arm);

		uint8_t getImmediateOffset();

		uint8_t getPrePostIndexingBit();

		uint8_t getUpDownBit();

		uint8_t getByteWordBit();

		uint8_t getWritebackBit();

		uint8_t getLoadStoreBit();

		uint8_t getBaseRegister();

		uint8_t getSourceDestinationRegister();

		uint8_t getOffset();

	private:
		uint8_t i;
		uint8_t p;
		uint8_t u;
		uint8_t b;
		uint8_t w;
		uint8_t l;
		uint8_t rn;
		uint8_t rd;

		uint16_t immediate12;

		uint8_t shift;
		uint8_t rm;

		uint16_t offset;

		uint32_t address;
		uint32_t value;
	};
}

#endif