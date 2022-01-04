#pragma once
#ifndef MAIN_H
#define MAIN_H

/* glfw °´¼üÏìÓ¦ */
void ProcessInput(class GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

float vertices[] = {
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {
	0, 2, 1,
	0, 3, 2
};

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;


float timeValue;
float dynamicColor;


class Shader* shader;
class Texture* texture_Box;
class Texture* texture_Face;
#endif // !MAIN_H
