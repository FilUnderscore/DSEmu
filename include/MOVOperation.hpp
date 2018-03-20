#ifndef INCLUDE_MOVOPERATION_HPP_
#define INCLUDE_MOVOPERATION_HPP_

#include "Operation.hpp"

namespace CPU
{
	class MOVOperation : public Operation
	{
	public:
		MOVOperation();
		MOVOperation(ARM* arm, Instruction* instruction);
		~MOVOperation();

		void execute();

		void memory();

		void write();
	};
}

#endif