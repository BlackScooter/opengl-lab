#include<GL/glew.h>
#include<GLFW/glfw3.h>
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#include<stdint.h>

const unsigned int WIN_W = 300;
const unsigned int WIN_H = 300;
const unsigned int WIN_X = 100;
const unsigned int WIN_Y = 100;

int main(void)
{
	//Start
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "Hello GLFW", NULL, NULL);
	glfwSetWindowPos(window, WIN_X, WIN_Y);
	glfwMakeContextCurrent(window);

	//start GLEW 
	glewInit();

	//prepare

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		//draw
		glClear(GL_COLOR_BUFFER_BIT);
		
		//GLFW actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//done
	glfwTerminate();
	return 0;
}