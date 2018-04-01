#include <ARM7.hpp>

#include <DSSystem.hpp>

#include <SharedMemoryMap.hpp>
ARM7::ARM7(DSSystem* ds) : ARM(ds, 33)
{
	this->memoryMap->allocate(0x00000000, 0x00003FFF);

	this->memoryMap->allocate(0x03800000, 0x0380FFFF);
}

ARM7::~ARM7()
{

}

void ARM7::init()
{
	ARM::init();

	Logger::log("I");
}

void ARM7::processPipeline()
{
	for(uint32_t index = 0; index < this->pipeline->size(); index++)
	{
		Instruction* instruction = this->pipeline->at(index);

		// ARM7 has 3 stage pipeline, so after execute in same cycle - call MEM and WB stages to support instructions with ARM9.
		while(instruction->getExecutionStage() != ::WB)
		{
			if(!instruction->execute(this))
			{
				break;
			}	
		}

		this->pipeline->erase(this->pipeline->begin() + index);

		delete instruction;
		instruction = NULL;
		index--;
	}
}