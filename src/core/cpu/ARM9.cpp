#include <ARM9.hpp>

#include <DSSystem.hpp>

#include <SharedMemoryMap.hpp>

ARM9::ARM9(DSSystem* ds) : ARM(ds, 66)
{
	this->memoryMap->allocate(0x00000000, 0x00007FFF);
	this->memoryMap->mirror(0x01000000, 0x00000000); // Mirror-able to 1000000h

	this->memoryMap->allocate(0x0B000000, 0x0B003FFF);
}

ARM9::~ARM9()
{

}

void ARM9::init()
{
	ARM::init();
}

void ARM9::processPipeline()
{
	for(uint32_t index = 0; index < this->pipeline->size(); index++)
	{
		Instruction* instruction = this->pipeline->at(index);

		if(instruction->getExecutionStage() != ::WB)
		{
			if(!instruction->execute(this))
			{
				this->pipeline->erase(this->pipeline->begin() + index);

				delete instruction;
				instruction = NULL;
			}
		}
		else
		{
			this->pipeline->erase(this->pipeline->begin() + index);

			delete instruction;
			instruction = NULL;
		}
	}
}