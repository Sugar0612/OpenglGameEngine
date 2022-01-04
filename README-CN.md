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
 Texture   |  [Texture](./OpenglEngine/Texture.h)
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
   
   源代码告诉我们，如果只依靠 VBO + VAO 去绘制图形，那么会在代码中重复的顶点坐标，所以我们需要加入EBO 来依靠索引坐标(indices)来减少顶点坐标代码的冗余。
   下面放一张 VAO,VBO, EBO之间的关系结构图来更好的了解他们之前的作用部位与关系：  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/vertex_array_objects_ebo.png" width="400" alt="vertex_array_objects_ebo">  
 
 - Shader  
 
   将VAO塞入VertexShader中我们也要去操作 vertexShader 与 fragmentShader，所以我们也要在代码中写vertexShaderSource 与 fragmentShaderSource的代码来告诉GPU如何去描绘这些顶点。  
   首先我们要创建VertexShader 与 fragmentShader，然后将Source塞入到里面，在将VertexShader 与 fragmentShader贴到 shaderProgram上，然后shaderProgram连接到Shader，这样Shader就可以读入 Source中的代码了！   
   连接上之后，在渲染回圈中使用连接上的 shaderProgram，接着将VAO绑定在 Vertex Shader上，利用VAO中的顶点数组绘制顶点，然后再往后的Shader中绘制图形。  
   - Uniform  
   Uniform 不通过VAO来传递 Vertex，那是直接偷偷塞进Vertex中，我们需要在Cpp中去寻找Uniform的位置，然后传递数值。例如：  
   ```cpp
   timeValue = glfwGetTime();
   dynamicColor = (sin(timeValue) * 0.5f) + 0.5f;
   /* 找到uniform在 Shader中的位置 */
   int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
   /* 塞入对应位置的ve4 */
   glUniform4f(vertexColorLocation, 0.f, dynamicColor, 0.f, 1.f);
   ```  
   然后再在Shader操作这些用Uniform定义的变量。  
   更多请查看源文件里面有详细的注释[渲染原理](./OpenglEngine/main.cpp)  

- Texture  

  如何将图片通过 **Shader** 加载在窗口中？我们可以通过 **Texture** 传递给VAO来实现。  
  ### 原理  
  这里还是重点讲一讲原理，首先就是创建texture，方式和VAO VBO的创建方式一样，没有什么区别都是使用对应的API进行创建和类型的绑定，然后我们就可以使用 **stbi_load** 函数来载入图片，在进行填充和生成Mipmap。下面是代码，这样更加有助于理解。  
  ```cpp
  glGenTextures(1, &texBuffer);
  glBindTexture(GL_TEXTURE_2D, texBuffer);
  data = stbi_load(_filename, &width, &height, &Channel, 0);

  /* 翻转图片 */
  stbi_set_flip_vertically_on_load(true);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  /* Open Mipmap */
  glGenerateMipmap(GL_TEXTURE_2D);
  ```

  然后就是 Texture将加载的图片放到VAO中去，VAO中为Texture准备了8个接口让Texture插入图片，不同的Texture将不同的图片插入不同的接口中，就可以实现图片的叠加。  
  至于如何实现选择不同接口Texture的插入，请查看源代码有注释的 [Texture插入](./OpenglEngine/main.cpp)，下面是Texture功能的展示：    
  <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/Texture.png" width="400" alt="Texture">  
  
 更多请查看源文件里面有详细的注释[纹理](./OpenglEngine/Texture.cpp)
