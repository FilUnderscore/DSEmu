#ifndef INCLUDE_ARM_HPP_
#define INCLUDE_ARM_HPP_

#include "Register.hpp"
#include "ProcessorState.hpp"
#include "Pointer.hpp"
#include "ProcessorMode.hpp"
#include "MemoryMap.hpp"
#include "Logger.hpp"
#include <vector>
#include <cstdint>

using std::vector;

namespace DS
{
	class DSSystem;
}

using DS::DSSystem;

class ALU;
class BarrelShifter;

namespace CPU
{
	class Instruction;
}

using CPU::Instruction;

namespace CPU
{
	class ARM
	{
	public:
		ARM(DSSystem* ds, uint32_t clockSpeed);
		virtual ~ARM();

		virtual void init();

		void setRegister(Register register, uint32_t value);

		uint32_t getRegister(Register register);

		void print();

		void run(uint32_t entrypoint);

		virtual void processPipeline();

		void lockPipeline(bool lock);

		void tick();

		bool fetchNextInstruction();

		void processInstruction(uint32_t instruction);

		void processARMInstruction(uint32_t instruction);

		void processTHUMBInstruction(uint16_t instruction);

		bool executeAt(uint32_t address);

		void onFIQ();

		void onIRQ();

		ProcessorState getProcessorState();

		ALU* getALU();

		BarrelShifter* getBarrelShifter();

		MemoryMap* getMemory();
	protected:
		DSSystem* ds;
		
		uint32_t clockSpeed;

		ALU* alu;
		BarrelShifter* barrelShifter;

		MemoryMap* memoryMap;

		Pointer<uint32_t>* registerMap;

		map<ProcessorMode, Pointer<uint32_t>*>* registerShadowMap;

		vector<Instruction*>* pipeline;

		bool pipelineLocked = false;

		void changeProcessorState(ProcessorState newProcessorState);
	};
}

#endif