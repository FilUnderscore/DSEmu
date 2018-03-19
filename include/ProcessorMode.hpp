#ifndef INCLUDE_PROCESSORMODE_HPP_
#define INCLUDE_PROCESSORMODE_HPP_

namespace CPU
{
	enum ProcessorMode
	{
		/*
		 * User and System Mode
		 */
		System,

		/*
		 * Supervisor Mode
		 */
		Supervisor,

		/*
		 * Abort Mode
		 */
		Abort,

		/*
		 * Undefined Mode
		 */
		Undefined,

		/*
		 * Interrupt Mode
		 */
		Interrupt,

		/*
		 * Fast Interrupt Mode
		 */
		Fast_Interrupt;
	};
}

#endif