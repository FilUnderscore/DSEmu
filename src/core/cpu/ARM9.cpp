#include <ARM9.hpp>

#include <DSSystem.hpp>

ARM9::ARM9(DSSystem* ds) : ARM(ds)
{
	
}

ARM9::~ARM9()
{

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