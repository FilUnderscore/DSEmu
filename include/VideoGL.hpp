#ifndef INCLUDE_VIDEOGL_HPP_
#define INCLUDE_VIDEOGL_HPP_

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "Memory.hpp"
#include "DSSystem.hpp"
#include <vector>

using std::vector;

class VideoGL
{
public:
	VideoGL(DSSystem* ds);
	~VideoGL();

	void init();
	void power(Memory* memory);
	void changeDisplayMode(Memory* memory);
	void createWindows();
	void tick();

	GLFWwindow* getTopWindow();
	GLFWwindow* getBottomWindow();

private:
	DSSystem* ds;

	GLFWwindow* topWindow;
	GLFWwindow* bottomWindow;
};

#endif