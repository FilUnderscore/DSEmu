#ifndef INCLUDE_CMPOPERATION_HPP_
#define INCLUDE_CMPOPERATION_HPP_

#include "Operation.hpp"

namespace CPU
{
	class CMPOperation : public Operation
	{
	public:
		CMPOperation();
		~CMPOperation();

		void execute();

		void memory();
	};
}

#endif