#include <VideoGL.hpp>

#include <Logger.hpp>
#include <Bits.hpp>

#include <GPU.hpp>

VideoGL::VideoGL(GPU* gpu)
{
	this->gpu = gpu;
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