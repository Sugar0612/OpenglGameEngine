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
 ### 初始化与窗口的搭建
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

 ### 渲染的原理   
   原理图：  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/Shader.png" width="400" alt="Shader">  
   我尽量用我的理解来解释清楚一个.obj文件是如何加载和使用的。  
   当读入一个 .obj文件到CPU后会通过很长的距离到达GPU，此时.obj文件解析成的数字坐标还不能被识别(arr)，我们需要把他装换成可以被识别的数组坐标。  
   这些arr到达GPU后会放在VBO中，我们要将这个VBO绑定在VAO(GL_ARRARY_BUFFER)上，在通过VAO塞入到vertexShader中进行绘制顶点。  
   
   源代码告诉我们，如果只依靠 VBO + VAO 去绘制图形，那么会在代码中重复的顶点坐标，所以我们需要加入EBO 来依靠索引坐标(indices)来减少顶点坐标代码的冗余。
   下面放一张 VAO,VBO, EBO之间的关系结构图来更好的了解他们之前的作用部位与关系：  
   <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/vertex_array_objects_ebo.png" width="400" alt="vertex_array_objects_ebo">  
 
 ### Shader  
 
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

 ### Texture  

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
 ### 3D
  绘制3D立方体，我们需要利用 **glm** 文件，你可以通过 [Glm Download](./Opengl.zip)，或者通过官方下载：[GLm Official Download](https://glm.g-truc.net/0.9.9/index.html)，然后像前面配置环境一样，将glm加入到C++包括目录中。  

  如何把一张平面的2D图，把他拼成一个立方体呢？我们该怎么做？以下我想通过我的学习来用我的方法来进行说明。  
  以下我将放上从2D到3D的一个原理图：  
  <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/coordinate_systems (1).png" width="400" alt="coordinate_systems">  
  我们可以通过这个图片来去构造 **Model Matrix**， ** View Matrix **， ** Porject Matrix **我们把这三个矩阵通过Uniform塞入Vertex Shader Source中，然后乘上 ** gl_Postion **来变成3D啦！  
  - Model Matrix  
    它是用来决定这个3d立方体的状态的，包括他的位置，他的距离(translate)，他绕那个轴旋转...
  - View Matrix
    它是用来决定我们观察的位置的，一般要给 viewMat 的Z轴 -3，这样就可以让摄像机在世界中心啦！
  - project Matrix
    这个我理解的是 他是用来标准化空间的，物体的远近与透视投影都是由他来完成。  
  然后我们在通过 vertices 用 VBO + VAO来绘制， 当然如果你有相关的 indices 你就可以用EBO来绘制了。。 
  ### Z-Buffer
   我们还没有结束，以为Opengl还分不清那个是前面，那个是后面，所以我们要让他去检测 Z-Buffer，即：如果前面已经有东西渲染了那么就不要在那个像素点与渲染其他东西了。  
   ```cpp
   glEnable(GL_DEPTH_TEST);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   ```  

  <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/3D.png" width="400" alt="3D">  
  
 更多请查看源文件里面有详细的注释 [3D立体](./OpenglEngine/main.cpp)  

 ### 相机
  现在我们想通过移动鼠标 和 输入键盘操作来从不同的方位观察立方体。那么我们该怎么做呢？  
  - 如何通过鼠标移动来实现相机的移动视角？  
    其实我们完全可以通过改变 View Matrix 来从不同位置来观察立方体，但是这样是不完全的，也不是一个相机的全部功能，所以我们需要得到 相机的 Forward, Right, Up, 以及世界向量 WorldUp 在通过对于他们的计算来控制 View Martix。  
    <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/camera_axes.png" width="400" alt="camera_axes">  
    当然这些只能确定相机的视角，那么我们该怎么通过鼠标来让相机 ‘抬头’，‘转头’呢？ 我们还需要一些角度： Pitch，Yaw。 然后通过一些数学计算算出 Forward 然后在通过获取鼠标坐标改变 Ptich 和 Yaw 就间接的改变了Camera 的 Forward，  
    也就改变了相机的角度。  
    获取相机坐标：  
    ```cpp
    /* 获取游标在视窗的坐标 */
	glfwSetCursorPosCallback(window, mouse_callback);

    void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
        if (is_first) {
            prevX = xPos;
            prevY = yPos;
            is_first = false;
        }

        float dirX, dirY;
        dirX = xPos - prevX;
        dirY = yPos - prevY;
    
        prevX = xPos;
        prevY = yPos;

        camera->CameraMovment(dirX, dirY);
    }
    ```  
    Pitch与Yaw概念图：  
    <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/camera_pitch_yaw_roll.png" width="400" alt="camera_pitch_yaw_roll">  
 更多请查看源文件里面有详细的注释 [相机](./OpenglEngine/Camera.cpp)

 ### 基础光照  
  我们的立方体上面只有贴图没有自然中的最普遍的光照效果，那么我们该怎么用Opengl仿照基础光照的效果呢？  
  - 冯氏光照/漫反射光照  
    我们需要在有直射光的基础上来体现阴影，如图：  
    <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/diffuse_light.png" width="400" alt="diffuse_light">  
    我们需要两个数据，一个是 光的位置，另一个就是法向量Normal, 法向量我们可以通过 vertices 从VAO中传入，而光的位置自己定义一个通过 Uniform 传入就好，下面我们需要将 LightPos 这个位置发出的光变成向量，那么，我们就需要用 (lightPos - FragPos),
    这个 FragPos 就是光照射在物体上的位置，(FragPos = vec3(modelMat * aPos).xyz)，然后我们点乘 dot(Normal, (lightPos - FragPos)) 得到漫反射光的强度，在乘上 LightColor就得到真正的漫反射光了。  

  - 镜面反射  
    镜面反射就是当你看这个立方体，他给你反射出光源的亮点，那就是镜面反射了，如果立方体材质表面粗糙，那么这个反射的光源就是一个范围，放上原理图便于更好的理解：  
    <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/basic_lighting_specular_theory.png" width="400" alt= "dbasic_lighting_specular_theory">  
    我们已经在 漫反射中得到了 Normal 和 LightDir了，那么我们现在需要知道反射的光源向量(reflectVec) 和 眼镜的位置向量(eyeVec)，这两个都好得到，reflectVec就是 -LightDir 与 法向量的关系，而GLSL给了我们解决这个问题的函数，
    (reflectVec = reflect(-LightVec, Normal))，而 eyeVec 就是像得到 LightDir一样，(eyeVec = normalize(eyePos - FragPos))，这样我们再将 reflectVec 与 eyeVec 点乘，就可以得到镜面反射，但是镜面反射效果不是很强烈，
    可以通过加倍(pow(a, b))来增强镜面反射的效果。  
    <img src = "https://raw.githubusercontent.com/Sugar0612/OpenglGameEngine/main/image/specular.png" width="400" alt="specular">  

  - 关于法向量Normal计算  
    Normal = mat3(transpose(inverse(offsets[gl_InstanceID]))) * aNormal 这是为什么呢？  
    从OpenGL了解到，由于当物体进行不规则缩放的时候，法向量会改变，为了解决这样的问题，需要定制一个模型矩阵，所以需要这样计算。  
    详情：[关于Normal的计算](https://learnopengl-cn.readthedocs.io/zh/latest/02%20Lighting/02%20Basic%20Lighting/)  

 更多请查看源文件里面有详细的注释 [基础光照-vert](./OpenglEngine/VertexSource.vert) ， [基础光照-frag](./OpenglEngine/FragmentSource.frag)
