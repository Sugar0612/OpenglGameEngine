#define GLEW_STATIC  //告诉编译器 使用 glew32s.lib

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "main.h"

using namespace::std;


int main() {
	
	/*初始化函数库*/
	glfwInit();
	/*主版本号*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	/*次版本号*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/*提示为可编程化流水线*/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*Create window*/
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenglEngine", nullptr, nullptr);
	
	/*Create Window Failed*/
	if (window == nullptr) {
		cout << "Create glfw Window is failed!" << endl;

		/*Stop Run*/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        		return -1;
	}

	/*设置为主窗口*/
	glfwMakeContextCurrent(window);

	/*Init Glew*/

	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		cout << "Init glew failed" << endl;
		
		glfwTerminate();
		return -1;
	}

	/*Canves window*/
	glViewport(0, 0, 800, 600);

	/* 创建一个放Vertex的数组 */
	glGenVertexArrays(1, &VAO);
	/* 将这个VAO塞到Vertex Shader中 */
	glBindVertexArray(VAO);

	/* 创建一个VBO */
	glGenBuffers(1, &VBO);
	/* 绑定VBO在VAO上面 */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* 把 .obj文件生成的顶点，从CPU塞到GPU中的VBO中去 */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* 创建一个vertexShader */
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/* 填充vertexShader */
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	/* 编译vertexShader */
	glCompileShader(vertexShader);

	/* fragmentShader的创建，填充与编译过程同vertexShader一样 */
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	/* 创建一个shaderProgram用来编译Shader */
	shaderProgram = glCreateProgram();
	/* 将vertexShader 与 fragmentShader组装在shaderProgram上... */
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	/* ...这样才能将SaderSource中的代码运行起来 */

	/* 连接到Shader中去 */
	glLinkProgram(shaderProgram);

	/* 告诉GPU中的 VertexShader 如何分辨数组中的数据(多少长度是一个点的坐标) */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	/* 打开VertexShader中的0号档口 */
	glEnableVertexAttribArray(0);

	/*渲染回圈*/
	while(!glfwWindowShouldClose(window)) {
		/* 颜色清屏 */
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* 使用ShaderProgram */
		glUseProgram(shaderProgram);
		/* 将VAO绑定在vertex上 */
		glBindVertexArray(VAO);
		/* 因为一个模型就是由一个一个的三角形构成的，
		那么让我们来画一个类型为三角形的图形 */
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ProcessInput(window);

		/*颜色暂存区块交换*/
		glfwSwapBuffers(window);

		/*获取用户按钮*/
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}