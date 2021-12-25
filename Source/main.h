#pragma once
#ifndef MAIN_H
#define MAIN_H

/* glfw °´¼üÏìÓ¦ */
void ProcessInput(class GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}


#endif // !MAIN_H
