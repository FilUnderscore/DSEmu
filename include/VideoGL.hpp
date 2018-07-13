#ifndef INCLUDE_VIDEOGL_HPP_
#define INCLUDE_VIDEOGL_HPP_

#include "include\GL\gl3w.h"
#include "include\GLFW\glfw3.h"

class GPU;

class VideoGL
{
public:
	VideoGL(GPU* gpu);
	~VideoGL();

	void init();

	void createWindows();
	
	void tick();

	GLFWwindow* getTopWindow();
	GLFWwindow* getBottomWindow();

private:
	GPU* gpu;

	GLFWwindow* topWindow;
	GLFWwindow* bottomWindow;
};

#endif