#include <iostream>
#include <sstream>

#define GLEW_STATIC
#include "GL/glew.h"  //GL/glew.h must come before the GLFW/glfw3.h
#include "GLFW/glfw3.h"


const char* APP_TITLE = "Introduction to Modern OpenGL - Hello Window 1";  //window title
const int gWindowWidth = 800;  //window height
const int gWindowHeight = 600;  //window width
GLFWwindow* gWindow = NULL;
//bool gFullScreen = false;  //set fullscreen

void flgw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);  //function for recognizing when keys are pressed on the keyboard
void showFPS(GLFWwindow* window);  //used to show FPS on current window
bool initOpenGL();

int main()
{
	if (!initOpenGL())
	{
		std::cerr << "GLFW initialization failed!" << std::endl;

		return -1;
	}

	//Main Loop----------------------------
	//--------------------------------------
	while (!glfwWindowShouldClose(gWindow)) //to stay in the application
	{
		showFPS(gWindow);

		glfwPollEvents();  //used to check for keyboard and mouse events

		glClear(GL_COLOR_BUFFER_BIT);  //clears screen with the color set above


		glfwSwapBuffers(gWindow);  //swaps the buffer being displayed with the buffer being drawn on, front buffer become back and back becomes front
									// used to elimate flickering and tearing by drawing on back buffer instead of buffer being displayed
	}

	glfwTerminate();  //terminates GLFW
	return 0;
}

//handles key presses
void flgw_onKey(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  //PRESS means keydown 
	{
		glfwSetWindowShouldClose(window, GL_TRUE);  //grabs the window and sets it to true to close it.
	}
}

//shows game performance on window
void showFPS(GLFWwindow * window)
{
	static double previousSeconds = 0.0;  
	static int frameCount = 0;  //frame rate
	double elapsedSeconds; 
	double currentSeconds = glfwGetTime();  //this built in funciton returns the number of seconds since glfw started

	elapsedSeconds = currentSeconds - previousSeconds;

	//limit text update 4 times a second
	if (elapsedSeconds >= .25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;  //calculates fps by number of frames per second
		double msPerFram = 1000.0 / fps;  //calculates miliseconds per fram

		std::ostringstream outs;  //need to include <sstream> in order to use this
		outs.precision(3);  //used to determine decimal places after the whole number
		outs << std::fixed << APP_TITLE << "   "  << "FPS: " << fps << "    " << "Frame Time: " << msPerFram << " (ms)";  //Title construction

		glfwSetWindowTitle(window, outs.str().c_str());  //actively updates the title

		frameCount = 0;  //rest frame count after .25 seconds

	}

	frameCount++;
}

bool initOpenGL()
{
	if (!glfwInit())  //initializes glfw which is used to create windows to display openGL and take user input
	{
		std::cerr << "GLFW initialization failed!" << std::endl;
		return -1;
	}

	//create a window-------------------------
	//----------------------------------------
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //sets version of openGL, major
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //sets version of openGL, minimum
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //creates a core profile of modern openGL
	//for mac users:
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  //needed for mac users

	GLFWwindow* pWindow = NULL;  //checks if screen is null

	//Full Screen---------------------------------------
	//-------------------------------------------------
	//if (gFullScreen)
	//{
	//	GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();  //gets a point to the primary monitor
	//	const GLFWvidmode* pVmode = glfwGetVideoMode(pMonitor);

	//	if (pVmode != NULL)
	//	{
	//		pWindow = glfwCreateWindow(pVmode->width, pVmode->height, APP_TITLE, pMonitor, NULL);  //actually creates the full screen window
	//	}


	//}
	//else
	//{
		gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);  //actually creates the window

	//}

	if (gWindow == NULL)  //if window fails to be created
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();  //terminates GLFW
		return false;
	}

	glfwMakeContextCurrent(gWindow);  //This is the window that we want to make current

	glfwSetKeyCallback(gWindow, flgw_onKey);  //keyboard callback function, pointer to the window first parameter and the name of the second parameter is chosen by me then declared about int main()

	glewExperimental = GL_TRUE;	//need to set to true to use GLEW
	if (glewInit() != GLEW_OK)  //checks if you can initializes glew
	{
		std::cerr << "GLEW initialization failed!" << std::endl;
		return false;
	}

	glClearColor(0.23f, 0.38f, 0.47f, 1.0f); //sets the color when screen is cleared

	return true;
}
