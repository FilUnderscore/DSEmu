#include <VideoGL.hpp>

#include <Logger.hpp>
#include <Bits.hpp>

VideoGL::VideoGL(DSSystem* ds)
{
	this->ds = ds;

	// Test of I/O interaction with Memory Map
	std::function<void(Memory*)> f = [ds](Memory* memory){ ds->getVideo()->power(memory); };
	this->ds->getARM9()->getMemory()->allocate(0x4000304, 0x4000308, f);
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