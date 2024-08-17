#include<GL/glew.h>
#include<GLFW/glfw3.h>
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma warning(disable: 4711 4710 4100)
#include<stdio.h>
#include<string.h> //for strrchr()


const unsigned int WIN_W = 300;
const unsigned int WIN_H = 300;
const unsigned int WIN_X = 100;
const unsigned int WIN_Y = 100;

void refreshFunc(GLFWwindow* window)
{
	//refresh
	printf("refresh called\n");
	fflush(stdout);
	glClear(GL_COLOR_BUFFER_BIT);
	glFinish();

	//GLFW action
	glfwSwapBuffers(window);
}

int main(int argc, char* argv[])
{
#if defined(_WIN32) || defined(_WIN64)
	char* win_name = (strrchr(argv[0],'\\') == NULL) ? argv[0] : (strrchr(argv[0],'\\') + 1);
#else //Unix, Linux, MacOS
	char* win_name = (strrchr(argv[0],'/') == NULL) ? argv[0] : (strrchr(argv[0],'/'') + 1);
#endif


	//Start
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, win_name, NULL, NULL);
	glfwSetWindowPos(window, WIN_X, WIN_Y);
	glfwMakeContextCurrent(window);

	//start GLEW 
	glewInit();

	//prepare
	glfwSetWindowRefreshCallback(window, refreshFunc);
	glClearColor(0.5F, 0.8F, 0.8F, 1.0F);

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		//draw
		glClear(GL_COLOR_BUFFER_BIT);
		glFinish();

		//GLFW actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//done
	glfwTerminate();
	return 0;
}

