#include<GL/glew.h>
#include<GLFW/glfw3.h>
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma warning(disable: 4711 4710 4100 4996)
#include<stdio.h>
#include<string.h> //for strrchr()
#include<stdlib.h> 

const unsigned int WIN_W = 300;
const unsigned int WIN_H = 300;
const unsigned int WIN_X = 100;
const unsigned int WIN_Y = 100;

GLfloat clr[4] = {0.933F, 0.769F, 0.898F, 1.0F};

const char* vertSource =
"#version 330 core \n\
in vec4 vertexPos; \n\
void main(void) { \n\
	gl_Position = vertexPos; \n\
}";

const char* fragSource =
"#version 330 core \n\
out vec4 FragColor; \n\
void main(void) { \n\
	FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n\
}";

GLuint vert = 0; //vertex shader ID nunmber
GLuint frag = 0; //fragment shader ID number
GLuint prog = 0; //shader program ID number

GLfloat vertPos[] = {
	-0.5F, -0.5F, 0.0F, 1.0F,
	+0.5F, -0.5F, 0.0F ,1.0F,
	-0.5F, +0.5F, 0.0F, 1.0F,
};

const char* getBaseName(const char* progname) {
#if defined(_WIN32) || defined(_WIN64)
	const char* ptr = (strrchr(progname, '\\') == NULL) ? progname : (strrchr(progname, '\\') + 1);
#else // Unix, Linux, MacOS
	const char* ptr = (strrchr(progname, '/') == NULL) ? progname : (strrchr(progname, '/') + 1);
#endif
	
	//size_t len = strlen(ptr) + 1; // 문자열 길이 + null 문자	 
	char* buf = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));
	if (buf == NULL)
		return NULL;

	strcpy(buf, ptr);
	if (strrchr(buf, '.') != NULL) { // cut-off ".exe", if exists
		*(strrchr(buf, '.')) = '\0';
	}
	return (const char*)buf;
}

void initFunc(void)
{
	//vert: vertex shader
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert,1,&vertSource,NULL);
	glCompileShader(vert); //compile to get.OBJ

	//frag:fragment shader
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag,1,&fragSource,NULL);
	glCompileShader(frag);

	//prog:program
	prog = glCreateProgram();
	glAttachShader(prog,vert);
	glAttachShader(prog,frag);
	glLinkProgram(prog); //link to get.EXE

	//excute it!
	glUseProgram(prog); 

}

void drawFunc(void)
{
	//clear in gray color
	glClear(GL_COLOR_BUFFER_BIT);
	//provide the vertex attributes
	GLuint loc = glGetAttribLocation(prog, "vertexPos");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertPos);
	//draw a triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//done 
	glFinish();

}

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

void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case 'Q': 
		clr[0] += 0.01F; if(clr[0] > 1.0F) clr[0] = 1.0F;
		break;
	case 'W':
		clr[1] += 0.01F; if(clr[1] > 1.0F) clr[1] = 1.0F;
		break;
	case 'E':
		clr[2] += 0.01F; if(clr[2] > 1.0F) clr[2] = 1.0F;
		break;
	case 'A':
		clr[0] -= 0.01F; if(clr[0] < 0.0F) clr[0] = 0.0F;
		break;
	case 'S':
		clr[1] -= 0.01F; if(clr[1] < 0.0F) clr[1] = 0.0F;
		break;
	case 'D':
		clr[2] -= 0.01F; if(clr[2] < 0.0F) clr[2] = 0.0F;
		break;
	case GLFW_KEY_ESCAPE:
		if(action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	default:
		break;
	}

	glClearColor(clr[0], clr[1], clr[2], clr[3]);
}

int main(int argc, char* argv[])
{
	const char* basename = getBaseName(argv[0]);

	//Start
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, basename, NULL/* glfwGetPrimaryMonitor()*/, NULL);
	glfwSetWindowPos(window, WIN_X, WIN_Y);
	glfwMakeContextCurrent(window);

	//start GLEW 
	glewInit();

	//prepare
	glfwSetWindowRefreshCallback(window, refreshFunc);
	glfwSetKeyCallback(window, keyFunc);
	glClearColor(clr[0], clr[1], clr[2], clr[3]);

	//main loop
	initFunc();
	while (!glfwWindowShouldClose(window))
	{
		//draw
		drawFunc();
		//glClear(GL_COLOR_BUFFER_BIT);
		//glFinish();

		//GLFW actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//done
	glfwTerminate();
	return 0;
}
