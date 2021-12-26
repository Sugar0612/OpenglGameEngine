# OpenglGameEngine
English | [简体中文](./README-CN.md)  
![image](https://img.shields.io/badge/Base-Opengl-blue.svg) ![image](https://img.shields.io/badge/Language-c++-orange.svg)
## Brief description
  Introductory tutorial notes on OpenGL. Learn plug-in download, environment loading, graphics rendering principle, Shader...
  You can learn from the official Opengl documentation [OpenGL Documentation](https://learnopengl.com/Getting-started/Hello-Window)

## learn
- Environment loading
 In the initial learning process, to use Opengl needs to be equipped with a suitable environment. I am currently using `VS2019 + glfw3.3 + glm + glew2.1`.
 Plug-in file download [Opengl Working environment](./Opengl.zip)
 - Add `YourPath\glfw-3.3.4.bin.WIN32\include` and `YourPath\glew-2.1.0\include` in `Project->Properties->C++->Linker->General->Additional library directory`.  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl1.png" width="400" alt="C++">
 - Add `YourPath\glfw-3.3.4.bin.WIN32\lib-vc2019` and `YourPath\glew-2.1.0\lib\Release\Win32` in `Project->Properties->Linker->General->Additional Library Directory`.  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl2.png" width="400" alt="Linker">
 - Add `opengl32.lib`, `glfw3.lib` and `glew32s.lib` in `Project->Properties->Linker->Input->Additional dependencies`.  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl3.png" width="400" alt="Linker In">  
 The environment loading is complete, if it fails, please download [Glfw DownLoad] from the official website (https://www.glfw.org/)

## content
 You can quickly check the parts you want to know through the catalog.  
 Module    |  File Link
 --------  |  ----------------
 Window    |  [Window](./OpenglEngine/main.cpp)
 Camera    |  [Camera](./OpenglEngine/Camera.h)
 Shader    |  [Shader](./OpenglEngine/Shader.h)
 Material  |  [Material](./OpenglEngine/Material.h)
 Mesh      |  [Mesh](./OpenglEngine/Mesh.h)

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
 For more, please see the detailed comments in the source file [Create Window](./OpenglEngine/main.cpp)  

 - Principle of rendering
 the schematic：  
 <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/Shader.png" width="400" alt="Shader"> 
 I try to use my understanding to explain clearly how an .obj file is loaded and used.  
 When an .obj file is read to the CPU, it will reach the GPU through a long distance. At this time, the digital coordinates parsed by the .obj file cannot be recognized (arr), we need to install it to an array coordinate that can be recognized.  
 These arrs will be placed in the VBO after they reach the GPU. We need to bind this VBO to the VAO (GL_ARRARY_BUFFER), and plug it into the vertexShader through the VAO to draw the vertices.  
 - Shader
 Putting VAO into VertexShader we also need to operate vertexShader and fragmentShader, so we also need to write vertexShaderSource and fragmentShaderSource code in the code to tell the GPU how to draw these vertices.  
 First, we need to create VertexShader and fragmentShader, then insert the Source into it, paste the VertexShader and fragmentShader onto the shaderProgram, and then connect the shaderProgram to the Shader, so that the Shader can read the code in the Source!  
 After connecting, use the connected shaderProgram in the rendering loop, then bind the VAO to the Vertex Shader, use the vertex array in the VAO to draw the vertices, and then draw the graphics in the subsequent Shader.   

 For more, please see the detailed comments in the source file [Render principle](./OpenglEngine/main.cpp)
