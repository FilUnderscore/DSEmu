#include <VideoGL.hpp>

#include <Logger.hpp>
#include <Bits.hpp>

VideoGL::VideoGL(DSSystem* ds)
{
	this->ds = ds;

	// POWCNT1
	std::function<void(Memory*)> f = [ds](Memory* memory){ ds->getVideo()->power(memory); };
	this->ds->getARM9()->getMemory()->allocate(0x04000304, 0x04000308, f);

	// DISPCNT
	std::function<void(Memory*)> f2 = [ds](Memory* memory){ ds->getVideo()->changeDisplayMode(memory); };

	// STR to 0x04000000 causes strange MOV behaviour in R2 (go from 49152 to 131072)?

	//this->ds->getARM9()->getMemory()->allocate(0x04000000, 0x04000004, f2);
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
	uint32_t dispcnt = Bits::to32UBits(memory->getMemory()->get());	
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