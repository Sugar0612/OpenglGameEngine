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
		glfwTerminate();
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

	/*��Ⱦ��Ȧ*/
	while(!glfwWindowShouldClose(window)) {

		/*��ɫ�ݴ����齻��*/
		glfwSwapBuffers(window);

		/*��ȡ�û���ť*/
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}