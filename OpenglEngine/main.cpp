#define GLEW_STATIC  //���߱����� ʹ�� glew32s.lib

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "main.h"

using namespace::std;


int main() {
	
	/*��ʼ��������*/
	glfwInit();
	/*���汾��*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	/*�ΰ汾��*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/*��ʾΪ�ɱ�̻���ˮ��*/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*Create window*/
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenglEngine", nullptr, nullptr);
	
	/*Create Window Failed*/
	if (window == nullptr) {
		cout << "Create glfw Window is failed!" << endl;

		/*Stop Run*/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        		return -1;
	}

	/*����Ϊ������*/
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

	/* ����һ����Vertex������ */
	glGenVertexArrays(1, &VAO);
	/* �����VAO����Vertex Shader�� */
	glBindVertexArray(VAO);

	/* ����һ��VBO */
	glGenBuffers(1, &VBO);
	/* ��VBO��VAO���� */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/* �� .obj�ļ����ɵĶ��㣬��CPU����GPU�е�VBO��ȥ */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* ����EBO�Ĺ�����VBO�������� */
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/* ����һ��vertexShader */
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/* ���vertexShader */
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	/* ����vertexShader */
	glCompileShader(vertexShader);

	/* fragmentShader�Ĵ����������������ͬvertexShaderһ�� */
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	/* ����һ��shaderProgram��������Shader */
	shaderProgram = glCreateProgram();
	/* ��vertexShader �� fragmentShader��װ��shaderProgram��... */
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	/* ...�������ܽ�SaderSource�еĴ����������� */

	/* ���ӵ�Shader��ȥ */
	glLinkProgram(shaderProgram);

	/* ����GPU�е� VertexShader ��ηֱ������е�����(���ٳ�����һ���������)VBO */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	/* ��VertexShader�е�0�ŵ��� */
	glEnableVertexAttribArray(0);

	/* ����GPU�е� VertexShader ��ηֱ������е�����(���ٳ�����һ���������)VBO */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
	/* ��VertexShader�е�0�ŵ��� */
	glEnableVertexAttribArray(1);

	/*��Ⱦ��Ȧ*/
	while(!glfwWindowShouldClose(window)) {
		/* ��ɫ���� */
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* ��VAO����vertex�� */
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/* ��Ϊһ��ģ�;�����һ��һ���������ι��ɵģ�
		��ô����������һ������Ϊ�����ε�ͼ��*/

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		
		timeValue = glfwGetTime();
		dynamicColor = (sin(timeValue) * 0.5f) + 0.5f;
		/* �ҵ�uniform�� Shader�е�λ�� */
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
		/* �����Ӧλ�õ�ve4 */
		glUniform4f(vertexColorLocation, 0.f, dynamicColor, 0.f, 1.f);

		/* ʹ��ShaderProgram */
		glUseProgram(shaderProgram);

		ProcessInput(window);
		/*��ɫ�ݴ����齻��*/
		glfwSwapBuffers(window);
		/*��ȡ�û���ť*/
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}