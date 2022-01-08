#define GLEW_STATIC  //���߱����� ʹ�� glew32s.lib

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "main.h"
#include "Shader.h"
#include "Texture.h"

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
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenglEngine", nullptr, nullptr);
	
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

	/* Create Shader */
	shader = new Shader("./VertexSource.txt", "./FragmentSource.txt");

	/* Create Texture */
	texture_Box = new Texture("./image/container.jpg", "JPG", GL_TEXTURE0);
	texture_Face = new Texture("./image/awesomeface.png", "PNG", GL_TEXTURE1);


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

	/* ����GPU�е� VertexShader ��ηֱ������е�����(���ٳ�����һ���������)VBO */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	/* ��VertexShader�е�0�ŵ��� */
	glEnableVertexAttribArray(0);
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);*/
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);

	// 3d
	viewMat = glm::translate(viewMat, glm::vec3(0.f, 0.f, -3.f));
	projMat = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.f);

	/*��Ⱦ��Ȧ*/
	while(!glfwWindowShouldClose(window)) {
		/* ��ɫ���� */
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);

		/* Z-buffer */
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* ����Texture */
		texture_Box->BindTexture();
		texture_Face->BindTexture();

		/* ��VAO����vertex�� */
		glBindVertexArray(VAO);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/* ��Ϊһ��ģ�;�����һ��һ���������ι��ɵģ�
		��ô����������һ������Ϊ�����ε�ͼ��*/

		for (int i = 0; i < 10; ++i) {

			glm::mat4 modelMat = glm::mat4();
			modelMat = glm::translate(modelMat, cubePositions[i]);
			modelMat = glm::rotate(modelMat, (float)glfwGetTime() * (i + 1) * glm::radians(50.0f), glm::vec3(1.f, 1.f, 0.f));

			/* ʹ��ShaderProgram */
			shader->use();

			/* ��Texture�����ͼƬ���뵽VAO�Ľӿ��� */
			texture_Box->SetUniform(shader->shaderProgram, 0, "aTexture");
			texture_Face->SetUniform(shader->shaderProgram, 1, "aFace");

			/* 3D */
			shader->UniformMat("modelMat", modelMat);
			shader->UniformMat("viewMat", viewMat);
			shader->UniformMat("projMat", projMat);

			/* ��û�и�indics��ʱ�� ���� VBO��glDrawArrays���� */
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		///* �ҵ�uniform�� Shader�е�λ�� */
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
		///* �����Ӧλ�õ�ve4 */
		//glUniform4f(vertexColorLocation, 0.f, dynamicColor, 0.f, 1.f);

		ProcessInput(window);
		/*��ɫ�ݴ����齻��*/
		glfwSwapBuffers(window);
		/*��ȡ�û���ť*/
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}