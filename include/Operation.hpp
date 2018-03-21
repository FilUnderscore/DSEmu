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

	class Operation
	{
	public:
		Operation();
		Operation(Opcode opcode);
		virtual ~Operation();

		void set(ARM* arm, DataProcessingInstruction* instruction);

		virtual void execute();

		virtual void memory();

		virtual void write();

		Opcode getOpcode();

		static void init();

		static Operation* getOperation(Opcode opcode);

	protected:
		Opcode opcode;

		ARM* arm;

		DataProcessingInstruction* instruction;

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