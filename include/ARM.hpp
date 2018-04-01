#ifndef INCLUDE_ARM_HPP_
#define INCLUDE_ARM_HPP_

#include "Register.hpp"
#include "ProcessorState.hpp"
#include "Instruction.hpp"
#include "Pointer.hpp"
#include "ProcessorMode.hpp"
#include "MemoryMap.hpp"
#include "ALU.hpp"
#include "Logger.hpp"
#include <vector>
#include <cstdint>

using std::vector;

using namespace CPU;

namespace DS
{
	class DSSystem;
}

using DS::DSSystem;

namespace CPU
{
	class ARM
	{
	public:
		ARM(DSSystem* ds);
		virtual ~ARM();

		virtual void init();

		void setRegister(Register register, uint32_t value);

		uint32_t getRegister(Register register);

		void print();

		void run();

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

		MemoryMap* getMemory();
	protected:
		DSSystem* ds;

		ALU* alu;

		MemoryMap* memoryMap;

		Pointer<uint32_t>* registerMap;

		map<ProcessorMode, Pointer<uint32_t>*>* registerShadowMap;

		vector<Instruction*>* pipeline;

		bool pipelineLocked = false;

		void changeProcessorState(ProcessorState newProcessorState);
	};
}

#endif