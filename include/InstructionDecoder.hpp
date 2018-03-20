#ifndef INCLUDE_INSTRUCTIONDECODER_HPP_
#define INCLUDE_INSTRUCTIONDECODER_HPP_

#include "Instruction.hpp"

using namespace CPU;

#include <cstdint>

using namespace std;

class InstructionDecoder
{
public:
	static Instruction* decode(uint32_t instruction);
};

#endif