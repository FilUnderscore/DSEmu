#include <HalfwordDataTransferInstruction.hpp>

using namespace CPU;

HalfwordDataTransferInstruction::HalfwordDataTransferInstruction(uint32_t instruction, uint8_t cond, uint8_t p, uint8_t u, uint8_t w, uint8_t l, uint8_t rn, uint8_t rd, uint8_t s, uint8_t h, uint8_t rm, uint8_t offset) : Instruction(instruction, cond)
{

}

HalfwordDataTransferInstruction::~HalfwordDataTransferInstruction()
{

}