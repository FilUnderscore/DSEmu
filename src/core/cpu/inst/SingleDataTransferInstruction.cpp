#include <SingleDataTransferInstruction.hpp>

SingleDataTransferInstruction::SingleDataTransferInstruction(uint32_t instruction, uint8_t cond, uint8_t i, uint8_t p, uint8_t u, uint8_t b, uint8_t w, uint8_t l, uint8_t rn, uint8_t rd, uint8_t immediate12, uint8_t shift, uint8_t rm) : Instruction(instruction, cond)
{

}

SingleDataTransferInstruction::~SingleDataTransferInstruction()
{

}