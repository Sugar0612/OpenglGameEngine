#define GLEW_STATIC  //告诉编译器 使用 glew32s.lib

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "main.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Material.h"
#include "LightDir.h"
#include "lightPoint.h"
#include "LightSpot.h"


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

	/* Create Camera */
	camera = new Camera(glm::vec3(0.f, 0.f, 3.f), 15.0f, 180.f, glm::vec3(0.f, 1.f, 0.f));

	/*设置为主窗口*/
	glfwMakeContextCurrent(window);

	/* 关闭游标显示 */
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* 获取游标在视窗的坐标 */
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


	/* Create Shader. */
	shader = new Shader("./VertexSource.vert", "./FragmentSource.frag");

	/* Create Texture. */
	texture_container2 = new Texture("./image/container2.png", "PNG", GL_TEXTURE2);
	container_specular = new Texture("./image/container2_specular.png", "PNG", GL_TEXTURE3);

	/* Create Material. */
	material = new Material(glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f), 128.0f);

	/* Create Light Direction. */
	//lightDir = new LightDir(glm::vec3(10.f, 10.f, -5.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(glm::radians(45.0f), 0.f, 0.f));

	/* Create Light Point. */
	//lightPtr = new LightPoint(glm::vec3(1.f, 1.f, -1.f), glm::vec3(2.f, 2.f, 2.f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.f));

	/* Create Light of Spot. */
	lightSpot = new LightSpot(glm::vec3(0.f, 2.f, 0.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(glm::radians(90.f), 0, 0));
	
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	/* 打开VertexShader中的0号档口 */
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 3d
	//viewMat = glm::translate(viewMat, glm::vec3(0.f, 0.f, -3.f));
	projMat = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.f);

	/*渲染回圈*/
	while(!glfwWindowShouldClose(window)) {

		/* 颜色清屏 */
		glClearColor(0.f, 0.f, 0.f, 1.f);

		/* Z-buffer */
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* 灌输Texture */
		texture_container2->BindTexture();
		container_specular->BindTexture();

		/* 将VAO绑定在vertex上 */
		glBindVertexArray(VAO);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/* 因为一个模型就是由一个一个的三角形构成的，
		那么让我们来画一个类型为三角形的图形*/

		/* 改变相机视角 */
		viewMat = camera->GetViewMatrix();

		/* Crate arrary of matrix model. */
		/*for (int i = 0; i < 10; ++i) {
			glm::mat4 modelMat = glm::mat4();
			modelMat = glm::translate(modelMat, cubePositions[i]);
			modelMat = glm::rotate(modelMat, (float)glfwGetTime() * 0 * glm::radians(50.0f), glm::vec3(1.f, 1.f, 0.f));
			modelarr[i] = modelMat;
		}*/

		
		for (int i = 0; i < 10; ++i) {

			/* 使用ShaderProgram */
			shader->use();

			/* 将Texture载入的图片插入到VAO的接口中 */
			texture_container2->Texshader->TextureSetUniform(2, "material.diffuse");
			container_specular->Texshader->TextureSetUniform(3, "material.specular");

			glm::mat4 modelMat = glm::mat4();
			modelMat = glm::translate(modelMat, cubePositions[i]);
			modelMat = glm::rotate(modelMat, (float)glfwGetTime() * 0 * glm::radians(50.0f), glm::vec3(1.f, 1.f, 0.f));

			/* 3D */
			//shader->UniformMat(("offsets[" + to_string(i) + "]").c_str(), modelarr[i]);
			shader->UniformMat("modelMat", modelMat);
			shader->UniformMat("viewMat", viewMat);
			shader->UniformMat("projMat", projMat);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		/* Light's Color */
		shader->SetUniform3f("ambientColor", 0.1f, 0.1f, 0.1f);
		shader->SetUniform3f("objColor", 1.f, 1.f, 1.f);
		shader->SetUniform3f_vec("lightPos", lightSpot->position);
		shader->SetUniform3f_vec("lightColor", lightSpot->color);
		shader->SetUniform3f_vec("lightDir", lightSpot->direction);
		shader->SetUniform1f("lightSpot.cosPhy", lightSpot->cosPhy);

		//shader->SetUniform1f("lightPtr.constant", lightPtr->constant);
		//shader->SetUniform1f("lightPtr.linear", lightPtr->linear);
		//shader->SetUniform1f("lightPtr.quadratic", lightPtr->quadratic);
		shader->SetUniform3f_vec("eyePos", camera->Postion);

		/* 材质 */
		material->shader->SetUniform3f_vec("material.ambient", material->ambient);
		shader->SetUniform3f_vec("material.diffuse", material->diffuse);
		material->shader->SetUniform3f_vec("material.specular", material->specular);
		material->shader->SetUniform1f("material.shininess", material->shininess);

		/* 这里我们只需要执行一次 glDrawArrays就可以一次性加载成百上千的模型啦~ */
		//glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 10);

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

		camera->UpdataCameraPos();
	}


	glfwTerminate();
	return 0;
}