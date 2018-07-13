#include "include\GPU.hpp"
#include "include\Bits.hpp"
#include "include\Logger.hpp"
#include "include\ARM9.hpp"

using namespace CPU;
using namespace DS;

Memory* GPU::VRAM_A = NULL;
Memory* GPU::VRAM_B = NULL;
Memory* GPU::VRAM_C = NULL;
Memory* GPU::VRAM_D = NULL;
Memory* GPU::VRAM_E = NULL;
Memory* GPU::VRAM_F = NULL;
Memory* GPU::VRAM_G = NULL;
Memory* GPU::VRAM_H = NULL;
Memory* GPU::VRAM_I = NULL;

GPU::GPU(DSSystem* ds)
{
	this->ds = ds;

	this->video = new VideoGL(this);

	this->init();
}
	
GPU::~GPU()
{

}

void GPU::init()
{
	// POWCNT1
	this->ds->getARM9()->getMemory()->link(0x04000304, 4, [this](Memory* memory) { this->powerControl(memory); });
	// DISPCNT
	this->ds->getARM9()->getMemory()->link(0x04000000, 4, [this](Memory* memory) { this->displayControl(memory); });
	// VRAMCNT_A
	this->ds->getARM9()->getMemory()->link(0x04000240, 4, [this](Memory* memory) { this->vramControl(memory); });
}

void GPU::powerControl(Memory* memory)
{
	this->video->init();

	Logger::log("Powered");

	uint32_t powcnt1 = Bits::to32UBits(memory->getMemory()->get());

	uint8_t enableFlagForBothLCDs = powcnt1 & 0x01;
	uint8_t graphicsEngineA_2d = (powcnt1 >> 1) & 0x01;

	if(enableFlagForBothLCDs)
	{
		this->video->createWindows();
	}
}

void GPU::displayControl(Memory* memory)
{
	uint32_t dispcnt = (memory->getMemory()->get()[0] << 24) | (memory->getMemory()->get()[1] << 16) | (memory->getMemory()->get()[2] << 8) | memory->getMemory()->get()[3];

	// Display Mode (Engine A + B) (Engine A: 0..3, Engine B: 0..1, GBA: Green Swap)
	uint8_t displayMode = (dispcnt >> 16) & 0x03;
	// Bit 18-19 (Engine A) VRAM block (0..3 = VRAM A..D) (For Capture & above Display Mode = 2)
	uint8_t vram_block = (dispcnt >> 18) & 0x03;

	// Display Mode
	// 0: Display off (Screen becomes white)
	// 1: Graphics Display (normal BG and OBJ layers)
	// 2: Engine A only: VRAM Display (Bitmap from block selected in DISPCNT.18-19)
	// 3: Engine A only: Main Memory Display (Bitmap DMA transfer from Main RAM)

	// Mode 2-3 display raw direct color bitmap (15-bit RGB values, the upper bit in each halfword is unused) without any further BG, OBJ, 3D layers.

	switch(displayMode)
	{
		case 0:
		{
			break;
		}

		case 1:
		{
			break;
		}

		case 2:
		{
			// Use VRAM

			break;
		}

		case 3:
		{
			break;
		}

		default:
		{
			break;
		}
	}
}

void GPU::vramControl(Memory* memory)
{
	uint32_t vram = Bits::to32UBits(memory->getMemory()->get());
	uint32_t vram_index = memory->getStartAddress() & 0x0F;

	// Bit 0-2 VRAM MST (Bit2 not used by VRAM-A, B, H, I)
	uint8_t vram_mst = vram & 0x07;	
	// Bit 3-4 VRAM Offset (0-3) (Offset not used by VRAM-E, H, I)
	uint8_t vram_offset = (vram >> 3) & 0x03;
	// Bit 7 VRAM Enable (0 = Disable, 1 = Enable)
	uint8_t vram_enable = (vram >> 7) & 0x01;

	// TODO: Handle VRAM properly as Memory (Video)
	// Possibly create GPU class for these tasks
	switch((VRAM) vram_index)
	{
		case ::A:
		{
			if(vram_enable)
			{
				if(VRAM_A == NULL)
				{
					if(vram_mst == 0)
					{
						// Plain ARM9-CPU Access
						this->ds->getARM9()->getMemory()->allocate(0x6800000, 0x681FFFF, [this](Memory* memory){ this->vramWrite(memory); });
						VRAM_A = this->ds->getARM9()->getMemory()->getMemory(0x6800000);
					}
				}
			}

			break;
		}

		case ::B:
		{
			break;
		}

		case ::C:
		{
			break;
		}

		case ::D:
		{
			break;
		}

		case ::E:
		{
			break;
		}

		case ::F:
		{
			break;
		}

		case ::G:
		{
			break;
		}

		case ::H:
		{
			break;
		}

		case ::I:
		{
			break;
		}

		default:
		{
			break;
		}
	}
}

void GPU::vramWrite(Memory* memory)
{

}

VideoGL* GPU::getVideo()
{
	return this->video;
}