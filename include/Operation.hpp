#ifndef INCLUDE_OPERATION_HPP_
#define INCLUDE_OPERATION_HPP_

#include "Opcode.hpp"

#include <cstdint>

#include <map>

#include "Logger.hpp"

using namespace std;

namespace CPU
{
	class ARM;

	class DataProcessingInstruction;

	class MOVOperation;
	class SUBOperation;

	class Operation
	{
	public:
		Operation();
		Operation(Opcode opcode);
		virtual ~Operation();

		void set(ARM* arm, DataProcessingInstruction* instruction);

		virtual void execute();

		virtual void memory();

		Opcode getOpcode();

		static void init();

		static Operation* getOperation(Opcode opcode);

		uint32_t getResult();

	protected:
		Opcode opcode;

		ARM* arm;

		DataProcessingInstruction* instruction;

		uint32_t result;

	private:
		static map<Opcode, Operation*(*)()>* operations;

		template<typename T>
		static Operation* createInstance()
		{
			return new T;
		}
	};
}

#endif