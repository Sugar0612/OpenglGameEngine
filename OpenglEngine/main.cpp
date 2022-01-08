#define GLEW_STATIC  //告诉编译器 使用 glew32s.lib

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "main.h"
#include "Shader.h"
#include "Texture.h"

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
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenglEngine", nullptr, nullptr);
	
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

	/* Create Shader */
	shader = new Shader("./VertexSource.txt", "./FragmentSource.txt");

	/* Create Texture */
	texture_Box = new Texture("./image/container.jpg", "JPG", GL_TEXTURE0);
	texture_Face = new Texture("./image/awesomeface.png", "PNG", GL_TEXTURE1);


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

	/* 创建EBO的过程与VBO大致相似 */
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/* 告诉GPU中的 VertexShader 如何分辨数组中的数据(多少长度是一个点的坐标)VBO */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	/* 打开VertexShader中的0号档口 */
	glEnableVertexAttribArray(0);
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);*/
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);

	// 3d
	viewMat = glm::translate(viewMat, glm::vec3(0.f, 0.f, -3.f));
	projMat = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.f);

	/*渲染回圈*/
	while(!glfwWindowShouldClose(window)) {
		/* 颜色清屏 */
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);

		/* Z-buffer */
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* 灌输Texture */
		texture_Box->BindTexture();
		texture_Face->BindTexture();

		/* 将VAO绑定在vertex上 */
		glBindVertexArray(VAO);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/* 因为一个模型就是由一个一个的三角形构成的，
		那么让我们来画一个类型为三角形的图形*/

		for (int i = 0; i < 10; ++i) {

			glm::mat4 modelMat = glm::mat4();
			modelMat = glm::translate(modelMat, cubePositions[i]);
			modelMat = glm::rotate(modelMat, (float)glfwGetTime() * (i + 1) * glm::radians(50.0f), glm::vec3(1.f, 1.f, 0.f));

			/* 使用ShaderProgram */
			shader->use();

			/* 将Texture载入的图片插入到VAO的接口中 */
			texture_Box->SetUniform(shader->shaderProgram, 0, "aTexture");
			texture_Face->SetUniform(shader->shaderProgram, 1, "aFace");

			/* 3D */
			shader->UniformMat("modelMat", modelMat);
			shader->UniformMat("viewMat", viewMat);
			shader->UniformMat("projMat", projMat);

			/* 当没有给indics的时候 就用 VBO的glDrawArrays画吧 */
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		///* 找到uniform在 Shader中的位置 */
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
		///* 塞入对应位置的ve4 */
		//glUniform4f(vertexColorLocation, 0.f, dynamicColor, 0.f, 1.f);

		ProcessInput(window);
		/*颜色暂存区块交换*/
		glfwSwapBuffers(window);
		/*获取用户按钮*/
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}