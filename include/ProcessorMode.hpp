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
		 * Supervisor (Protected) Mode
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
		 * InterRupt reQuest Mode (IRQ)
		 */
		Interrupt,

		/*
		 * Fast Interrupt reQuest Mode (FIQ)
		 */
		Fast_Interrupt
	};
}

#endif