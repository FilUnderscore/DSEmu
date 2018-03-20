#ifndef INCLUDE_OPERATION_HPP_
#define INCLUDE_OPERATION_HPP_

#include "ARM.hpp"
#include "Instruction.hpp"
#include "Opcode.hpp"

#include <cstdint>

#include <map>

#include <Logger.hpp>

using namespace std;

namespace CPU
{
	class Operation
	{
	public:
		Operation();
		Operation(Opcode opcode, ARM* arm, Instruction* instruction);
		virtual ~Operation();

		void set(ARM* arm, Instruction* instruction);

		virtual void execute();

		virtual void memory();

		virtual void write();

		Opcode getOpcode();

		static void init();

		static Operation* getOperation(Opcode opcode);

	protected:
		Opcode opcode;

		ARM* arm;

		Instruction* instruction;

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