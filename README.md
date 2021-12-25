# OpenglGameEngine
English | [简体中文](./README-CN.md)  
![image](https://img.shields.io/badge/Base-Opengl-blue.svg) ![image](https://img.shields.io/badge/Language-c++-orange.svg)
## Brief description
  Introductory tutorial notes on OpenGL. Learn plug-in download, environment loading, graphics rendering principle, Shader...
  You can learn from the official Opengl documentation [OpenGL Documentation](https://learnopengl.com/Getting-started/Hello-Window)

## learn
- Environment loading
 In the initial learning process, to use Opengl needs to be equipped with a suitable environment. I am currently using `VS2019 + glfw3.3 + glm + glew2.1`.
 Plug-in file download [Opengl Working environment](./opengl.zip)
 - Add `YourPath\glfw-3.3.4.bin.WIN32\include` and `YourPath\glew-2.1.0\ in `Project->Properties->C++->Linker->General->Additional library directory` include`.  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl1.png" width="400" alt="C++">
 - Add `YourPath\glfw-3.3.4.bin.WIN32\lib-vc2019` and `YourPath\glew-2.1.0\lib in `Project->Properties->Linker->General->Additional Library Directory` \Release\Win32`.  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl2.png" width="400" alt="Linker">
 - Add `opengl32.lib`, `glfw3.lib` and `glew32s.lib` in `Project->Properties->Linker->Input->Additional dependencies`.  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl3.png" width="400" alt="Linker In">  
 The environment loading is complete, if it fails, please download [Glfw DownLoad] from the official website (https://www.glfw.org/)

## content
 You can quickly check the parts you want to know through the catalog.  
 Module    |  File Link
 --------  |  ----------------
 Window    |  [Window](./Source/main.cpp)
 Camera    |  [Camera](./Source/Camera.h)
 Shader    |  [Shader](./Source/Shader.h)
 Material  |  [Material](./Source/Material.h)
 Mesh      |  [Mesh](./Source/Mesh.h)

## The realization of basic functions
 I will put some necessary and basic code that I have learned for review.
 - Initialization and window construction
 Regarding window construction, you need to define the window
 ```cpp
 /*Create window*/
 GLFWwindow* window = glfwCreateWindow(800, 600, "OpenglEngine", nullptr, nullptr);
 ```
 Then perform rendering and display. Of course, we need to use a rendering loop during the rendering process.

 ```cpp
 /*Canves window*/
 glViewport(0, 0, 800, 600);
 
 /*Rendering loop*/
 while(!glfwWindowShouldClose(window)) {

	/*Color temporary block exchange*/
	glfwSwapBuffers(window);

	/*Get user button*/
	glfwPollEvents();
 }
 ```
 For more, please see the detailed comments in the source file [Source code](./Source/main.cpp)
