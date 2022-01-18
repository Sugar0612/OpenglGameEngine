#define GLEW_STATIC  //���߱����� ʹ�� glew32s.lib

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "main.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Material.h"

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

	/* Create Camera */
	camera = new Camera(glm::vec3(0.f, 0.f, 3.f), 15.0f, 180.f, glm::vec3(0.f, 1.f, 0.f));

	/*����Ϊ������*/
	glfwMakeContextCurrent(window);

	/* �ر��α���ʾ */
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* ��ȡ�α����Ӵ������� */
	glfwSetCursorPosCallback(window, mouse_callback);

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
	shader = new Shader("./VertexSource.vert", "./FragmentSource.frag");

	/* Create Texture */
	texture_container2 = new Texture("./image/container2.png", "PNG", GL_TEXTURE2);
	container_specular = new Texture("./image/container2_specular.png", "PNG", GL_TEXTURE3);

	/* Create Material */
	material = new Material(glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f), 128.0f);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	/* ��VertexShader�е�0�ŵ��� */
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 3d
	//viewMat = glm::translate(viewMat, glm::vec3(0.f, 0.f, -3.f));
	projMat = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.f);

	/*��Ⱦ��Ȧ*/
	while(!glfwWindowShouldClose(window)) {

		/* ��ɫ���� */
		glClearColor(0.f, 0.f, 0.f, 1.f);

		/* Z-buffer */
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* ����Texture */
		texture_container2->BindTexture();
		container_specular->BindTexture();

		/* ��VAO����vertex�� */
		glBindVertexArray(VAO);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/* ��Ϊһ��ģ�;�����һ��һ���������ι��ɵģ�
		��ô����������һ������Ϊ�����ε�ͼ��*/

		/* �ı�����ӽ� */
		viewMat = camera->GetViewMatrix();

		/* Crate arrary of matrix model. */
		for (int i = 0; i < 10; ++i) {
			glm::mat4 modelMat = glm::mat4();
			modelMat = glm::translate(modelMat, cubePositions[i]);
			modelMat = glm::rotate(modelMat, (float)glfwGetTime() * 0 * glm::radians(50.0f), glm::vec3(1.f, 1.f, 0.f));
			modelarr[i] = modelMat;
		}

		
		for (int i = 0; i < 10; ++i) {

			/* ʹ��ShaderProgram */
			shader->use();

			/* ��Texture�����ͼƬ���뵽VAO�Ľӿ��� */
			texture_container2->Texshader->TextureSetUniform(2, "material.diffuse");
			container_specular->Texshader->TextureSetUniform(3, "material.specular");

			/* 3D */
			shader->UniformMat(("offsets[" + to_string(i) + "]").c_str(), modelarr[i]);
			shader->UniformMat("viewMat", viewMat);
			shader->UniformMat("projMat", projMat);

			//glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		/* Light's Color */
		shader->SetUniform3f("ambientColor", 0.05f, 0.05f, 0.05f);
		shader->SetUniform3f("objColor", 1.f, 1.f, 1.f);
		shader->SetUniform3f("lightPos", 10.f, 10.f, 5.f);
		shader->SetUniform3f("lightColor", 1.f, 1.f, 1.f);
		//shader->SetUniform3f("FragPos");
		shader->SetUniform3f("eyePos", camera->Postion.x, camera->Postion.y, camera->Postion.z);

		/* ���� */
		material->shader->SetUniform3f_vec("material.ambient", material->ambient);
		//shader->SetUniform3f_vec("material.diffuse", material->diffuse);
		material->shader->SetUniform3f_vec("material.specular", material->specular);
		material->shader->SetUniform1f("material.shininess", material->shininess);

		/* ��������ֻ��Ҫִ��һ�� glDrawArrays�Ϳ���һ���Լ��سɰ���ǧ��ģ����~ */
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 10);

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

		camera->UpdataCameraPos();
	}


	glfwTerminate();
	return 0;
}