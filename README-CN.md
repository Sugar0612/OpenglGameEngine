# OpenglGameEngine
简体中文 | [English](./README.md)  
![image](https://img.shields.io/badge/Base-Opengl-blue.svg)   ![image](https://img.shields.io/badge/Language-c++-orange.svg)
## 简述
  关于OpenGL的入门教程笔记。学习插件下载，环境搭载，图形渲染原理，Shader...   
  你可以通过Opengl官方文档来学习 [OpenGL 文档](https://learnopengl.com/Getting-started/Hello-Window)

## 学习
- 环境搭载
 最初学习过程中，要使用Opengl需要搭载合适的环境。目前本人使用的是 `VS2019 + glfw3.3 + glm + glew2.1`。  
 插件文件下载[Opengl Working environment](./Opengl.zip)  
 - 在`项目->属性->C++->链接器->常规->附加库目录`中加入 `YourPath\glfw-3.3.4.bin.WIN32\include` 和 `YourPath\glew-2.1.0\include`。  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl1.png" width="400" alt="C++">
 - 在`项目->属性->链接器->常规->附加库目录`中加入 `YourPath\glfw-3.3.4.bin.WIN32\lib-vc2019` 和 `YourPath\glew-2.1.0\lib\Release\Win32`。  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl2.png" width="400" alt="Linker">
 - 在`项目->属性->链接器->输入->附加依赖项`中加入 `opengl32.lib`, `glfw3.lib` 和 `glew32s.lib`。  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/opengl3.png" width="400" alt="Linker In">  
 环境搭载完成，如果失败请自行官网下载[Glfw 下载](https://www.glfw.org/)
 
## 内容
 您可以通过目录快速查看您想了解的部分。
 Module    |  File Link
 --------  |  ----------------
 Window    |  [Window](./OpenglEngine/main.cpp)
 Camera    |  [Camera](./OpenglEngine/Camera.h)
 Shader    |  [Shader](./OpenglEngine/Shader.h)
 Material  |  [Material](./OpenglEngine/Material.h)
 Mesh      |  [Mesh](./OpenglEngine/Mesh.h)

## 基本功能的实现
 我会放一些我学习到的必要且基础的代码用来回顾。
 - 初始化与窗口的搭建
 关于窗口搭建，需要定义窗口
 ```cpp
 /*Create window*/
 GLFWwindow* window = glfwCreateWindow(800, 600, "OpenglEngine", nullptr, nullptr);
 ```
 然后进行渲染显示, 当然在渲染的过程中我们需要使用渲染回圈。
 ```cpp
 /*Canves window*/
 glViewport(0, 0, 800, 600);
 
 /*渲染回圈*/
 while(!glfwWindowShouldClose(window)) {

	/*颜色暂存区块交换*/
	glfwSwapBuffers(window);

	/*获取用户按钮*/
	glfwPollEvents();
 }
 ```
 更多请查看源文件里面有详细的注释[创建窗口](./OpenglEngine/main.cpp)

 - 渲染的原理   
   原理图：  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/Shader.png" width="400" alt="Shader">  
   我尽量用我的理解来解释清楚一个.obj文件是如何加载和使用的。  
   当读入一个 .obj文件到CPU后会通过很长的距离到达GPU，此时.obj文件解析成的数字坐标还不能被识别(arr)，我们需要把他装换成可以被识别的数组坐标。  
   这些arr到达GPU后会放在VBO中，我们要将这个VBO绑定在VAO(GL_ARRARY_BUFFER)上，在通过VAO塞入到vertexShader中进行绘制顶点。  
 
 - Shader  
 
   将VAO塞入VertexShader中我们也要去操作 vertexShader 与 fragmentShader，所以我们也要在代码中写vertexShaderSource 与 fragmentShaderSource的代码来告诉GPU如何去描绘这些顶点。  
   首先我们要创建VertexShader 与 fragmentShader，然后将Source塞入到里面，在将VertexShader 与 fragmentShader贴到 shaderProgram上，然后shaderProgram连接到Shader，这样Shader就可以读入 Source中的代码了！   
   连接上之后，在渲染回圈中使用连接上的 shaderProgram，接着将VAO绑定在 Vertex Shader上，利用VAO中的顶点数组绘制顶点，然后再往后的Shader中绘制图形。  

 更多请查看源文件里面有详细的注释[渲染原理](./OpenglEngine/main.cpp)
