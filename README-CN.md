# OpenglGameEngine
�������� | [English](./README.md)  
![image](https://img.shields.io/badge/Base-Opengl-blue.svg)   ![image](https://img.shields.io/badge/Language-c++-orange.svg)
## ����
  ����OpenGL�����Ž̳̱ʼǡ�ѧϰ������أ��������أ�ͼ����Ⱦԭ��Shader...   
  �����ͨ��Opengl�ٷ��ĵ���ѧϰ [OpenGL Documentation](https://learnopengl.com/Getting-started/Hello-Window)

## ѧϰ
- ��������
 ���ѧϰ�����У�Ҫʹ��Opengl��Ҫ���غ��ʵĻ�����Ŀǰ����ʹ�õ��� `VS2019 + glfw3.3 + glm + glew2.1`��  
 ����ļ�����[Opengl Working environment](./opengl.zip)  
 - ��`��Ŀ->����->C++->������->����->���ӿ�Ŀ¼`�м��� `YourPath\glfw-3.3.4.bin.WIN32\include` �� `YourPath\glew-2.1.0\include`��  
   ![C++](https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl1.png)
 - ��`��Ŀ->����->������->����->���ӿ�Ŀ¼`�м��� `YourPath\glfw-3.3.4.bin.WIN32\lib-vc2019` �� `YourPath\glew-2.1.0\lib\Release\Win32`��  
   ![Linker](https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl2.png)
 - ��`��Ŀ->����->������->����->����������`�м��� `opengl32.lib`, `glfw3.lib` �� `glew32s.lib`��  
   ![Linker in](https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl3.png)
 ����������ɣ����ʧ�������й�������[Glfw DownLoad](https://www.glfw.org/)
 
## ����
 ������ͨ��Ŀ¼���ٲ鿴�����˽�Ĳ��֡�
 Module    |  File Link
 --------  |  ----------------
 Window    |  [Window](./Source/main.cpp)
 Camera    |  [Camera](./Source/Camera.h)
 Shader    |  [Shader](./Source/Shader.h)
 Material  |  [Material](./Source/Material.h)
 Mesh      |  [Mesh](./Source/Mesh.h)

## �������ܵ�ʵ��
 �һ��һЩ��ѧϰ���ı�Ҫ�һ����Ĵ��������عˡ�
 - ��ʼ���봰�ڵĴ
 ���ڴ��ڴ����Ҫ���崰��
 ```cpp
 /*Create window*/
 GLFWwindow* window = glfwCreateWindow(800, 600, "OpenglEngine", nullptr, nullptr);
 ```
 Ȼ�������Ⱦ��ʾ, ��Ȼ����Ⱦ�Ĺ�����������Ҫʹ����Ⱦ��Ȧ��
 ```cpp
 /*Canves window*/
 glViewport(0, 0, 800, 600);
 
 /*��Ⱦ��Ȧ*/
 while(!glfwWindowShouldClose(window)) {

	/*��ɫ�ݴ����齻��*/
	glfwSwapBuffers(window);

	/*��ȡ�û���ť*/
	glfwPollEvents();
 }
 ```
 ������鿴Դ�ļ���������ϸ��ע��[Source code](./Source/main.cpp)