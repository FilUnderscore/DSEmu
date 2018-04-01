#include <VideoGL.hpp>

#include <Logger.hpp>
#include <Bits.hpp>

VideoGL::VideoGL(DSSystem* ds)
{
	this->ds = ds;

	// POWCNT1
	std::function<void(Memory*)> f1 = [ds](Memory* memory){ ds->getVideo()->power(memory); };
	this->ds->getARM9()->getMemory()->link(0x04000304, 4, f1);

	// DISPCNT
	std::function<void(Memory*)> f2 = [ds](Memory* memory){ ds->getVideo()->changeDisplayMode(memory); };
	this->ds->getARM9()->getMemory()->link(0x04000000, 4, f2);

	std::function<void(Memory*)> f3 = [ds](Memory* memory) { ds->getVideo()->changeVRAMSettings(memory); };
	this->ds->getARM9()->getMemory()->link(0x04000240, 4, f3);
}

VideoGL::~VideoGL()
{

}

void VideoGL::init()
{
	if(!glfwInit())
	{
		Logger::log("Failed to initialize GLFW!");

		exit(0);

		return;
	}
}

void VideoGL::power(Memory* memory)
{
	this->init();

	Logger::log("Powered");

	uint32_t powcnt1 = Bits::to32UBits(memory->getMemory()->get());

	uint8_t enableFlagForBothLCDs = powcnt1 & 0x01;
	uint8_t graphicsEngineA_2d = (powcnt1 >> 1) & 0x01;

	if(enableFlagForBothLCDs)
	{
		this->createWindows();
	}
}

void VideoGL::changeDisplayMode(Memory* memory)
{
	uint32_t dispcnt = (memory->getMemory()->get()[0] << 24) | (memory->getMemory()->get()[1] << 16) | (memory->getMemory()->get()[2] << 8) | memory->getMemory()->get()[3];

	uint8_t displayMode = (dispcnt >> 16) & 0x03;

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

void VideoGL::changeVRAMSettings(Memory* memory)
{
	uint32_t vram = Bits::to32UBits(memory->getMemory()->get());
	uint32_t vram_index = memory->getStartAddress() & 0x0F;

	// Bit 0-2 VRAM MST (Bit2 not used by VRAM-A, B, H, I)
	uint8_t vram_mst = vram & 0x07;	
	// Bit 3-4 VRAM Offset (0-3) (Offset not used by VRAM-E, H, I)
	uint8_t vram_offset = (vram >> 3) & 0x03;
	// Bit 7 VRAM Enable (0 = Disable, 1 = Enable)
	uint8_t vram_enable = (vram >> 7) & 0x01;

	this->ds->terminate();
}

void error_callback(int error, const char* description)
{
	Logger::log("Err: " + string(description));
}

void VideoGL::createWindows()
{
	this->topWindow = glfwCreateWindow(256, 192, "DSEmu Top Window", NULL, NULL);
	this->bottomWindow = glfwCreateWindow(256, 192, "DSEmu Bottom Window", NULL, this->topWindow);

	if(!this->topWindow || !this->bottomWindow)
	{
		glfwTerminate();

		Logger::log("Failed to create GLFW window!");

		exit(0);

		return;
	}

	glfwSetErrorCallback(error_callback);

	glfwMakeContextCurrent(this->topWindow);

	if(gl3wInit())
	{
		Logger::log("Failed to initialize OpenGL (GL3W).");

		glfwTerminate();

		exit(0);

		return;
	}
}

void VideoGL::tick()
{
	// exit() will cause GLX error.
	if(this->topWindow != NULL && this->bottomWindow != NULL)
	{
		glfwMakeContextCurrent(this->topWindow);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(this->topWindow);

		glfwMakeContextCurrent(this->bottomWindow);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(this->bottomWindow);

		glfwPollEvents();
	}
}

GLFWwindow* VideoGL::getTopWindow()
{
	return this->topWindow;
}

GLFWwindow* VideoGL::getBottomWindow()
{
	return this->bottomWindow;
}