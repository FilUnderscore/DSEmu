#ifndef INCLUDE_ARM_HPP_
#define INCLUDE_ARM_HPP_

#include <cstdint>

#include "Register.hpp"

#include "ProcessorState.hpp"

#include "Operation.hpp"

#include <vector>

using namespace CPU;

using namespace std;

class DS;

namespace CPU
{
	class ARM
	{
	public:
		ARM(DS* ds);
		virtual ~ARM();

		void init();

		void setRegister(Register register, uint32_t value);

		uint32_t getRegister(Register register);

		void setMemoryRegister(Register register, uint32_t value);

		void print();

		void run();

		void processPipeline();

		void tick();

		void processInstruction(uint32_t instruction);

		void processARMInstruction(uint32_t instruction);

		void processTHUMBInstruction(uint16_t instruction);

		ProcessorState getProcessorState();

		void executeAt(uint32_t address);

		void onFIQ();

		void onIRQ();
	protected:
		DS* ds;

		uint32_t* registerMap;
		uint32_t registerMapSize;

		// Used for MEM and WB pipeline stages
		uint32_t* memoryRegisterMap;
		uint32_t memoryRegisterMapSize;

		vector<Operation*>* pipeline;

		ProcessorState processorState;

		void changeProcessorState(ProcessorState newProcessorState);
	};
}

#endif