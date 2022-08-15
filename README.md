# GameEngine_PersonalProject  

Start writing a simple game engine...  
Learning from the famous Hazel Engine  <https://github.com/TheCherno/Hazel>

## Daily progress

- [GameEngine_PersonalProject](#gameengine_personalproject)
	- [Daily progress](#daily-progress)
		- [[2022/8/1] (some small things)](#202281-some-small-things)
		- [[2022/8/5] (ImGui imported and event handle order)](#202285-imgui-imported-and-event-handle-order)
		- [[2022/8/6] (Imgui layer and event function construction)](#202286-imgui-layer-and-event-function-construction)
		- [[2022/8/7] (Input Polling system construction)](#202287-input-polling-system-construction)
		- [[2022/8/9] Input Polling (Key Code and Mouse Code Implement)](#202289-input-polling-key-code-and-mouse-code-implement)
		- [[2022/8/11] ImGui Window Docking and ImGui Layer changes](#2022811-imgui-window-docking-and-imgui-layer-changes)
		- [[2022/8/12] (renderer and render class structures)](#2022812-renderer-and-render-class-structures)
		- [[2022/8/13] (render context)](#2022813-render-context)
		- [[2022/8/14] some first context in the engine](#2022814-some-first-context-in-the-engine)
		- [[2022/8/15] shaders](#2022815-shaders)
		- [[2022/8/15] Rendering API Abstraction](#2022815-rendering-api-abstraction)
			- [abstract class of buffer](#abstract-class-of-buffer)
			- [for specific opengl buffer api:](#for-specific-opengl-buffer-api)
			- [Example Of Buffer Create:](#example-of-buffer-create)

### [2022/8/1] (some small things)

Entry point: starting the application from the engine and defined by the client  

EventDispatcher: check if event type matches the statictype if yes then handle the event (which defined from the event func), it is getting called at Application::Onevent function

binding the event call back in the setup of window at the application construction (SetEventCallBack)

### [2022/8/5] (ImGui imported and event handle order)

EventHandle Order (credit: <https://zhuanlan.zhihu.com/p/549038718>):  
![image](https://github.com/Zhengkaluo/GameEngine_PersonalProject/blob/main/IMG/EventHandleOrder.jpg)

### [2022/8/6] (Imgui layer and event function construction)

ImGui layer inhieritated from layer class.  
construction by Onattach function, which calles from push layer function  
Update function: get singleton app -> size update->delta time update -> newframe of imgui -> render()  

The OnEvent Function: through imgui layer on event function,　construct one dispatcher and bind all events function into the dispatcher,　it check the event type and　fall them into corresponding type function

### [2022/8/7] (Input Polling system construction)

Input Pollling system:  
as Input class is pure virtual and windows input inherited from it. it gets to implemented by different interface (in here only windows, it could be other platform...)  
at windows input class, it gets key pressed() by getting from application -> Window -> GLFWwindow to call the function glfwgetkey and check if certain key is pressed. it is the same for mouse and mouse pos  
and it can be tested by application run function and call function like (auto [x, y] = Input::GetMousePosition();) and log it to test if it is working.  

### [2022/8/9] Input Polling (Key Code and Mouse Code Implement)

Key Code Mapping:
implementing Own Engine Key code at Keycodes.h and mousebuttoncodes.h  
with that it is possbile to be independent from glfw3.h (the true key code we are using in the library) for example

```c++
void OnUpdate() override
{
	//KALUO_INFO("Example Layer Update");
	if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_TAB)) 
	{
		KALUO_TRACE("tab key is pressed! (poll)");
	}
}
```

the one above is using input polling  
the one 👇 is using input event

```c++
void OnEvent(KaluoEngine::Event& event) override
{
	//KALUO_TRACE("{0} event update", event);
	if (event.GetEventType() ==KaluoEngine::EventType::KeyPressed)
	{
		KaluoEngine::KeyPressedEvent& e =(KaluoEngine::KeyPressedEvent&)event;
		//KALUO_TRACE("key code {0}", (char)e.GetKeyCod());
		if (e.GetKeyCode() == KALUO_KEY_TAB)
		{
			KALUO_TRACE("Tab key is pressed (event)");
		}
	}
}
```

and the it is independent from glfw key code and the terminal shows this:  
![image](https://github.com/Zhengkaluo/GameEngine_PersonalProject/blob/main/IMG/Poll-Event.png)

OpenGL math GML does not need premake file because it is a header, just include their hpp and inl files

### [2022/8/11] ImGui Window Docking and ImGui Layer changes

ImGui Layer changes:  
Layer has OnImGuiRender virtual function which can be ovrrriden by any layers.  
SandBox App does not contruct imgui layer, instead Engine automatically add ImGui layer at runtime.  
Since ImGui is part of engine, so it will be centralized in the engine.  
In the application.h it contains the pointer which when applcation is constructed, it calls 👇

```c++
m_ImGuiLayer = new ImGuiLayer; 
```

and render imgui layer at the run() function and eventually this part at application::run() will be run on the render thread later on update)  

```c++
m_ImGuiLayer->Begin();
for (Layer* EachLayer : m_LayerStack)
	EachLayer->OnImGuiRender();
m_ImGuiLayer->End();
```

### [2022/8/12] (renderer and render class structures)

Two sides of render:  
Render API(API/ platform spectific. OpenGL, Vulcans...) (implement per API)(what should we build 👇):  

1. Render Constext
2. Swap Chain
3. Framebuffer
4. Vertex Buffer
5. Index Buffer
6. Shader
7. States
8. Pipelines
9. RenderPasses

Renderer (API/Platform agnostic)(use api to render what we want):  

1. 2D & 3D Renderer: Forwarded, Deferred
2. Scene Graph (Scene Manager..)
3. Sorting (decide what to render, when to render. sort thing using the same material)
4. Culling
5. Materials
6. LOD (level of details)
7. Animation
8. Cameara
9. VFX
10. PostFX (PostFx system)
11. Reflection, Ambient Occulusion...

Write Code to render a trianlge for each API ❌  
Create All primitives and create vertex buffer, index buffer and texture, shaders (Code to draw triangle is handled by Engine) and other branches into APIs  ✅

Goal Now: Start With OpenGL, when all finish go to other renderer api (cuz its easiest API xd)  
Steps (Overlaped, iterated):

1. Build Render API
2. Build Renderer

### [2022/8/13] (render context)

```c++
GLFWAPI void glfwMakeContextCurrent(GLFWwindow* handle){
	//it gets the window
	GLFWwindow* window = (_GLFWwindow*) handle;
	//with the window it can have window->context
}

```

within this function we would like to have a specific context for the window to render, and glfw does the internal job. glfwc context can be opengl, vulcan...

One window, one rendering context. context is static. should the windoswindow own the context? or other ownership. the reason of static context is the context does not need to be changed, if yes then create a new window instead.  

thoughts: we create pure virtual class graphics context for context specific class to inheirated, by that we have for now openglcontext class to creat context for glfwMakeContextCurrent()

```c++
class GraphicsContext
{
public:
	virtual void Init() = 0;
	virtual void SwapBuffers() = 0;
};

class OpenGLContext : public GraphicsContext
{
public:
	OpenGLContext(GLFWwindow* windowHandle);
	virtual void Init() override;
	virtual void SwapBuffers() override;

private:
	GLFWwindow* m_windowHandle;
};

void OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_windowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	KALUO_CORE_ASSERT(status, "Failed to initialize Glad!");
}
void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_windowHandle);
}
```

```c++
//where m_window is glfwwindow and with glfwwindow we pass it as reference into openglcontext
m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
m_Context = new OpenGLContext(m_Window);
m_Context->Init();
```

we have a private variable m_windowHandle at openglcontext class, it get uesed at reference at windowswindow->init() and create the openglcontext class. if windowswindow calls swapbuffers at onupdate() it calls openglcontext->swapbuffers() which it used glfw context handling function instead of we calling them instead windowswindow class, (and we dont have to worry about how it is managed since its the glfw lib function (for now ofc)). 

### [2022/8/14] some first context in the engine

we would try to create 1. vertex array, 2. vertex buffer, 3. index buffer.

(from 8/15 this part has a abstract class name buffer.h and openglbuffer.h is getting implemented to create all the buffer (index and vertices))

```c++
Rendering_The_Vertex{
	//Steps: Vertex Array + Vertex Buffer + Index Buffer
	//Shader, use default shader
	// generate vertex array object names in here 'm_VertexArray', and bind the name with the object
	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);
	//generate buffer object names and bind the vertex attributes target
	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	//upload data to gpu, static draw meaning we are not continuing refreshing
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//enable the first vertex attribute
	glEnableVertexAttribArray(0);
	//define an array of generic vertex attribute data, stride meaning each column of 3*3 has 3 float data (每行有三个float)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glGenBuffers(1, &m_IndexBuffer);
	//what order to draw, target: Vertex array indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	unsigned int indices[3] = { 0, 1, 2 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
}
```

### [2022/8/15] shaders

we tell gpu what to do with data we sent it, vertex shader tells what to do with the vertex data it receives specifically (points out where it in the window). pixel shader/fragement shader figures out what color should be.

OpenGL shader compile: <https://www.khronos.org/opengl/wiki/Shader_Compilation#Example>

In the engine our shader class: 

```c++
class Shader
{
public:
	//from opengl wiki we know it takes two parameters of a vertex/fragment shader
	//std::string vertexSource = // Get source code for vertex shader.
	// std::string fragmentSource = // Get source code for fragment shader.
	Shader(const std::string& vertexSource, const std::string& fragmentSource);
	~Shader();
	void Bind() const;
	void UnBind() const;
private:
	uint32_t m_RenderID;
};

void Shader::Bind() const
{
	glUseProgram(m_RenderID);
}
void Shader::UnBind() const
{
	glUseProgram(0);
}

```

in the shader construction function: we do vertex shader compile and then fragment shader compile, and if both succeed, we create a opengl program by


```c++
GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //vertex shader construction
//checking...
GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //fragment shader construction
//checking...
GLuint program = glCreateProgram(); //create programe
//checking...
```

and do the linking and check if linking fails. and after all checks succeed, we do detaches by

```c++
glDetachShader(program, vertexShader);
glDetachShader(program, fragmentShader);
```

inside application.cpp we construct two shaders: and its using varying position for color settings(fragment shader)

```c++
//source code of shader
std::string vertexSrc = R"(
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;
	//varying variable 
	out vec3 v_Position;
	void main()
	{
		v_Position = a_Position;
		gl_Position = vec4(a_Position, 1.0);	
	}
)";
std::string fragmentSrc = R"(
	#version 330 core
	
	layout(location = 0) out vec4 color;
	in vec3 v_Position;
	void main()
	{
		color = vec4(v_Position * 0.5 + 0.5, 1.0);
	}
)";
```

### [2022/8/15] Rendering API Abstraction

Goal: make the shader construction (above👆) generic. Eventually we want to have classes like VertexBuffer, IndexBuffer... so that we can simply call:

```c++
auto buffer = VertexBuffer::Create(size, vertices);
buffer.Bind();
```

selecting api, by IFDEF or something else.
shader file, if directx then... if opengl then...

From: <https://zhuanlan.zhihu.com/p/69397055>
some relations:

1. D3D: HLSL
2. OpenGL：GLSL
3. OpenGLES：ESSL
4. Metal：MSL
5. Vulkan：SPIR-V

shader api solutions:

1. 为每个 API 编写一套 Shader。简单粗暴，但维护工作量巨大。

2. 使用宏定义区分 Shader 差异。有些 Shader 的语法比较接近，可以编写一些辅助宏来抽象出 Shader 之间的差异，比如：

3. 以某一个图形 API 的 Shader 作为源，转换成目标 API Shader 源码，也就是 Source - Source 的方式，再使用目标 API 的 Shader 编译器进行编译。例如 UE4 采用的就是这种方案，UE4 用 HLSL 作为面向开发者的 统一格式，材质编辑器中生成的 Shader 也是 HLSL 格式，在转成其他 API Shader 时，采用的是在 Mesa 的 GLSL 编译器技术上自研的 HLSLCC，并且为每个图形 API 编写 Shader 后端（对应下图的绿色部分），生成对应的 Shader 源码并进行编译。UE4 Shader 跨平台编译架构如下图：

![image](https://github.com/Zhengkaluo/GameEngine_PersonalProject/blob/main/IMG/UE4_Shader_Structure.jpg)

#### abstract class of buffer

inside create function we decide which api we are using and which class type we instantiate

```c++
class VertexBuffer
{
public:
	virtual ~VertexBuffer() {}
	//virtual void SetData()
	//define interface
	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;
	//get data of vertices,  play as constructor
	static VertexBuffer* Create(float* vertices, uint32_t size);
};
class IndexBuffer
{
	virtual ~IndexBuffer() {}
	//define interface
	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;
	//get data of indices,  play as constructor
	static IndexBuffer* Create(uint32_t* indices, uint32_t size);
};
```

#### for specific opengl buffer api:

```c++
class OpenGLVertexBuffer : public VertexBuffer 
{
public:
	//parameter as VertexBuffer create function takes 
	OpenGLVertexBuffer(float* vertices, uint32_t size);
	virtual ~OpenGLVertexBuffer();
	virtual void Bind() const;
	virtual void UnBind() const;
private:
	uint32_t m_RendererID;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	//parameter as VertexBuffer create function takes 
	OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
	virtual ~OpenGLIndexBuffer();
	virtual uint32_t GetCount() const { return m_Count; }
	virtual void Bind() const;
	virtual void UnBind() const;
private:
	uint32_t m_Count;
	uint32_t m_RendererID;
};

```

and implementation of openglvertex buffer creation:

```c++
OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
	//typedef void (APIENTRYP PFNGLCREATEBUFFERSPROC)
	//(GLsizei n, GLuint *buffers)
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
```

#### Example Of Buffer Create:

(how it implmented to devided each api)

```c++
VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{
	//decide which api we are using
	//which class type we instantiate
	switch (Renderer::GetAPI())
	{
		case RendererAPI::None: 
			KALUO_CORE_ASSERT(false, "None RenderAPi is not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
	}
	KALUO_CORE_ASSERT(false, "UnKnown Renderer API!");
	return nullptr;
}
```

