# GameEngine_PersonalProject  

Start writing a simple game engine...  
Learning from the famous Hazel Engine  <https://github.com/TheCherno/Hazel>

## Daily progress

- [GameEngine_PersonalProject](#gameengine_personalproject)
	- [Daily progress](#daily-progress)
		- [[2022/8/1-2-3] (some small things)](#202281-2-3-some-small-things)
		- [[2022/8/5] (ImGui imported and event handle order)](#202285-imgui-imported-and-event-handle-order)
		- [[2022/8/6] (Imgui layer and event function construction)](#202286-imgui-layer-and-event-function-construction)
		- [[2022/8/7] (Input Polling system construction)](#202287-input-polling-system-construction)
		- [[2022/8/9] Input Polling (Key Code and Mouse Code Implement)](#202289-input-polling-key-code-and-mouse-code-implement)
		- [[2022/8/11] ImGui Window Docking and ImGui Layer changes](#2022811-imgui-window-docking-and-imgui-layer-changes)
		- [[2022/8/12] (renderer and render class structures)](#2022812-renderer-and-render-class-structures)
		- [[2022/8/13] (render context)](#2022813-render-context)
		- [[2022/8/14] some first context in the engine](#2022814-some-first-context-in-the-engine)
		- [[2022/8/15] shaders](#2022815-shaders)
			- [vertex shader code example](#vertex-shader-code-example)
		- [[2022/8/15] Rendering API Abstraction](#2022815-rendering-api-abstraction)
			- [abstract class of buffer](#abstract-class-of-buffer)
			- [for specific opengl buffer api:](#for-specific-opengl-buffer-api)
			- [Example Of Buffer Create:](#example-of-buffer-create)
		- [[2022/8/16] VertexBuffer data type. For vertex buffer layouts](#2022816-vertexbuffer-data-type-for-vertex-buffer-layouts)
			- [example of vertex array genearation with layout](#example-of-vertex-array-genearation-with-layout)
			- [layout class implementation](#layout-class-implementation)
		- [[2022/8/19] Vertex Arrays](#2022819-vertex-arrays)
			- [idea of vertexarray class and implementation](#idea-of-vertexarray-class-and-implementation)
			- [example of creating vertex buffer and index buffer](#example-of-creating-vertex-buffer-and-index-buffer)
			- [example of creaeting blue shader](#example-of-creaeting-blue-shader)
		- [[2022/8/20] renderer flow](#2022820-renderer-flow)
			- [first form of renderer and rendererapi class](#first-form-of-renderer-and-rendererapi-class)
		- [[2022/8/22] Camera Planning](#2022822-camera-planning)
			- [order of equation in calculation](#order-of-equation-in-calculation)
		- [[2022/8/23] Orthographic Camera](#2022823-orthographic-camera)
			- [Projection matrix in the vertex shader for doing matrix maltiplication](#projection-matrix-in-the-vertex-shader-for-doing-matrix-maltiplication)
		- [[2022/8/24] moving some renderer codes into client, add camera movement](#2022824-moving-some-renderer-codes-into-client-add-camera-movement)
			- [old codes of renderer](#old-codes-of-renderer)
			- [moving camera inside application](#moving-camera-inside-application)
		- [[2022-8-25] time steps, delta time](#2022-8-25-time-steps-delta-time)
		- [[2022-8-28]Transform and Material](#2022-8-28transform-and-material)
			- [Transform](#transform)
			- [Material](#material)
		- [[2022-8-29] Shader Class Abstraction](#2022-8-29-shader-class-abstraction)
		- [[2022-8-30] Smart pointer, refs and some encapsulations. Textures](#2022-8-30-smart-pointer-refs-and-some-encapsulations-textures)
			- [own type of shared ptr - Engine Ref, Scope](#own-type-of-shared-ptr---engine-ref-scope)
			- [Textures](#textures)
			- [OpenGLTexture Class](#opengltexture-class)
		- [[2022-8-31] adding alpha channel, blending](#2022-8-31-adding-alpha-channel-blending)
			- [blending function into opengl](#blending-function-into-opengl)
		- [[2022-9-1] shader asset files, learn some blending](#2022-9-1-shader-asset-files-learn-some-blending)
			- [Some Blending learn](#some-blending-learn)
		- [[2022/9/2] Shader Library](#202292-shader-library)
			- [ShaderLibrary Class](#shaderlibrary-class)
		- [[2022/9/4] 2D renderer planing](#202294-2d-renderer-planing)
		- [[2022-9-5] camera controller](#2022-9-5-camera-controller)
			- [details of camera controller (orthographic)](#details-of-camera-controller-orthographic)
		- [[2022-9-6] Some Organizing and Maintenance](#2022-9-6-some-organizing-and-maintenance)
		- [[2022-9-7] SandBox 2D rendering](#2022-9-7-sandbox-2d-rendering)
			- [moving sandbox example layers stuffs into sandbox 2d layer](#moving-sandbox-example-layers-stuffs-into-sandbox-2d-layer)
		- [[2022-9-9] starting 2d rendering.](#2022-9-9-starting-2d-rendering)
		- [[2022-9-10] Setting 2D renderer Transform](#2022-9-10-setting-2d-renderer-transform)
			- [setting transfom](#setting-transfom)
		- [[2022-9-10] Setting 2D renderer texture](#2022-9-10-setting-2d-renderer-texture)
		- [[2022-9-13] single shader 2d renderer](#2022-9-13-single-shader-2d-renderer)
		- [[2022-9-15] Starting of profiling](#2022-9-15-starting-of-profiling)
			- [timer class](#timer-class)

### [2022/8/1-2-3] (some small things)

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

#### vertex shader code example

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

![image](https://github.com/Zhengkaluo/GameEngine_PersonalProject/blob/main/IMG/UE4%20_Shader_Structure.jpg)

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

### [2022/8/16] VertexBuffer data type. For vertex buffer layouts

the reason we want to have the layout settings is to get rid of the annoying hand-typed 

```c++
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
glVertexAttribPointer(0, 5, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
```

#### example of vertex array genearation with layout

and have a structure like this: and this layout is easy to be checked
and iterally checkin vertex inside the bufferlayout in opengl
GetComponentCount() is a function of BufferElement

```c++
//float 3 for position and float 4 for color in total 3 * 7
float vertices[3 * 7] = 
{
	-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
	0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
	0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
};

BufferLayout Elementlayout
{
	//takes in buffer elements initializer_list
	{ ShaderDataType::Float3, "a_Position" },
	{ ShaderDataType::Float4, "a_Color" }
}
uint32_t index = 0;
const auto& layout = m_VertexBuffer->GetLayout();
for (const auto& element : layout)
{
	//enable the first vertex attribute
	glEnableVertexAttribArray(index);
	//define an array of generic vertex attribute data, stride meaning each column of3*3has 3 float data (每行有三个float)
	//2022-8-18: conversion of ShaderDataType into gl function parameters
	glVertexAttribPointer(index, 
		element.GetComponentCount(), 
		ShaderDataTypeToOpenGLBaseType(element.Type), 
		element.Normalized ? GL_TRUE : GL_FALSE, 
		layout.GetStride(),
		(const void *)element.Offset
	);
	index++;
}
```

#### layout class implementation

the implementation of this layout construction is: 
it calculated offset and the stride of the buffer automatically preventing hand typing data

```c++
struct BufferElement
{
	std::string Name;
	ShaderDataType Type;
	uint32_t Offset;
	uint32_t Size;
	//uint32_t Count;
	bool Normalized;

	//consturctor, offset is calculated by ourselves
	BufferElement(ShaderDataType type, const std::string& name，bool normalized = false)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
	{
	}
};

class BufferLayout
{
public:
	//constructor takes in initializer_list and convert into vector, and calculate offset
	BufferLayout(const std::initializer_list<BufferElement> element)
		: m_Elements(element) 
	{
		CalculateOffsetsAndStride();
	}

	inline uint32_t GetStride() const { return m_Stride; }
	inline const std::vector<BufferElement>& GetElements() const { m_Elements; };
		
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
private:
	//calculate element offset and stride
	void CalculateOffsetsAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}
private:
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride = 0;
};
```

and also buffer class and specific OpenGLBuffer (override) is added to have and called setlayout to the vertex buffer when application.cpp has initialized a valid layout variable.

```c++
virtual void SetLayout(const BufferLayout& layout) = 0;
virtual const BufferLayout& GetLayout() const = 0;

BufferLayout m_Layout;
```

### [2022/8/19] Vertex Arrays

'pointers' to vertex buffer and index buffer. 'just a reference'
opengl has vertex array but directx does not. so we would like to achieve this in an abstract way. and we try to moved all opengl api related functions into platform opengl related class. and using abstract class like vertexarray, vertexbuffer to handling which api should do the work (of course for now is all opengl)

#### idea of vertexarray class and implementation

so the part of [example of vertex array genearation with layout](#example-of-vertex-array-genearation-with-layout)

is done in the OpenGLVertexarray class which is child class of abstract class vertexarray class. glBindVertexArray(), glGenVertexArrays(), glBindVertexArray() and handling vertex attribt part are all moved/'redealt' into vertexarray class.

```c++
class OpenGLVertexArray : public VertexArray 
{
public:
	OpenGLVertexArray();
	~OpenGLVertexArray() {}
	virtual void Bind() const override;
	virtual void UnBind() const override;
	virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
	virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

private:
	uint32_t m_RendererID;
	//mirroring all vertex buffers in the shared pointer list and index buffer
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

//implemeentation of this
void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();
	uint32_t index = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout)
	{
		//enable the first vertex attribute
		glEnableVertexAttribArray(index);
		//define an array of generic vertex attribute data, stride meaning each column of 3*3 has 3 float data (每行有三个float)
		//2022-8-18: conversion of ShaderDataType into gl function parameters
		glVertexAttribPointer(index,
			element.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.Type),
			element.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)element.Offset
		);
		index++;
	}
	m_VertexBuffers.push_back(vertexBuffer);
}
void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_RendererID);
	indexBuffer->Bind();
	m_IndexBuffer = indexBuffer;
}
```

with all this is an example of rendering a square steps:

1. creat vertices
2. create vertex buffer with vertices
3. set layout of vertex buffer
4. add vertex buffer to vertex array
5. create indices and index buffer  
6. set index buffer to the vertex array
7. create shader
8. run draw function

#### example of creating vertex buffer and index buffer 

```c++
m_SquareVA.reset(VertexArray::Create());

float SqaureVertices[3 * 4] = {
	-0.5f, -0.5f, 0.0f, 
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};
std::shared_ptr<VertexBuffer> SquareVB; 
SquareVB.reset(VertexBuffer::Create(SqaureVertices, sizeof(SqaureVertices)));
BufferLayout SquareVBlayout{
	//takes in buffer elements initializer_list
	{ ShaderDataType::Float3, "a_Position" },
};
SquareVB->SetLayout(SquareVBlayout);
m_SquareVA->AddVertexBuffer(SquareVB);
unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0};
std::shared_ptr<IndexBuffer>SquareIndexBuffer; 
SquareIndexBuffer.reset(IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) /sizeo(uint32_t))));
m_SquareVA->SetIndexBuffer(SquareIndexBuffer);
```

#### example of creaeting blue shader

```c++
//create shaders:
std::string BlueShadervertexSrc = R"(
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;
	out vec3 v_Position;
	void main()
	{
		v_Position = a_Position;
		gl_Position = vec4(a_Position, 1.0);	
	}
)";
std::string BlueShaderfragmentSrc = R"(
	#version 330 core
	
	layout(location = 0) out vec4 color;
	in vec4 v_Color;
	void main()
	{
		color = vec4(0.2, 0.3, 0.8, 1.0);
	}
)";
m_BlueShader.reset(new Shader(BlueShadervertexSrc, BlueShaderfragmentSrc));
```

and finally draw it in the run time function

```c++
//in run function():
m_BlueShader->Bind();
m_SquareVA->Bind();
glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
```

### [2022/8/20] renderer flow

what we need to render a cube:

1. renderer. vertex array, shader...
2. camera, projection matrix, view matrix (:star:)
3. position of the cube, transformation matrix. (:star:)
4. surface matrial, what is it made of?
5. environment. lights, directional light. use enviroment map, radial map...

command queue. know everything before rendering.
idealiy we want to have: (and we have it now)

```c++
//final form: Renderer::BeginScene(camera, lights, environments);
RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
RenderCommand::Clear();
Renderer::BeginScene();
m_BlueShader->Bind();
Renderer::Submit(m_SquareVA);
m_Shader->Bind();
Renderer::Submit(m_VertexArray);
Renderer::EndScene();
```

we made a renderer api class and use it to setclearcolor(), clear() and drawindexed()...

this mean the class Renderer is going to be:

#### first form of renderer and rendererapi class

```c++
class Renderer
{
public:
	static void BeginScene();//taking all scene parameter
	static void EndScene();
	static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
};

//where renderer api is being:
class RendererAPI
{
public:
	enum class API
	{
		None = 0, OpenGL = 1
	};
public:
	virtual void SetClearColor(const glm::vec4& color) = 0;
	virtual void Clear() = 0;
	virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

	inline static API GetAPI() { return s_RendererAPI; }
private:
	static API s_RendererAPI;

//and render command, it tells specific api to do the work

class RenderCommand {
public:
	inline static void SetClearColor(const glm::vec4& color) 
	{
		s_RendererAPI->SetClearColor(color);
	}
	inline static void Clear()
	{
		s_RendererAPI->Clear();
	}
	inline static void DrawIndexed(const std::shared_ptr <VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}
private:
	static RendererAPI* s_RendererAPI;
};
//inside rendercommand.cpp we set
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
};
```

render command do not do multiple things. it does not bind and draw in the same time!
this means that Renderer::Submit() it has to bind vertexarray and calls rendercommand::drawindexed. instead of drawindexed() binding the vertexarray.



and the temp openglrendererapi is being

```c++
class OpenGLRendererAPI : public RendererAPI 
{
public:
	virtual void SetClearColor(const glm::vec4& color) override;
	virtual void Clear() override;
	virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
};
```

### [2022/8/22] Camera Planning

x,y,z cooridinate and rotation. Transform.
field/degree of the view 45, 65, 90...
![image](https://github.com/Zhengkaluo/GameEngine_PersonalProject/blob/main/IMG/FOV40.jpg)
![image](https://github.com/Zhengkaluo/GameEngine_PersonalProject/blob/main/IMG/FOV90.jpg)
aspect ratio, how wide...
Look at matrix:
![image](https://github.com/Zhengkaluo/GameEngine_PersonalProject/blob/main/IMG/LookAtMatrix.png)

take camera view matrix and invert it when the camera moves, cuz the object moved the opposite direction.

#### order of equation in calculation

_projection matrix_ * _view matrix_ * _model matrix(world matrix)_ * _vertex position_

part of camera: projection and the view, also call vp matrix
part of object: model
part of mesh: vertex position

renderer: beginscene(camera), for VP matrix, when start rendering, vertex array and shader are (should be) binded, and supposingly it can be rendered.

### [2022/8/23] Orthographic Camera

#### Projection matrix in the vertex shader for doing matrix maltiplication

inside our the former code of vertex shader

[vertex shader (old)](#vertex-shader-code-example)

we added an new uniform variable of projection matrix:

```c++
std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
uniform mat4 u_ViewProjectionMatrix;
out vec3 v_Position;
out vec4 v_Color;

void main()
{
	v_Position = a_Position;
	v_Color  = a_Color;
	//calculate viewprojection * vertex position
	gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);	
}
)";
// and inside run() matrix we have to upload the projection matrix 
run(){
	...
	m_BlueShader->Bind();
	//2022-8-23 uploade uniform matrix
	m_BlueShader->UpLoadUniformMat4("u_ViewProjectionMatrix", m_Camera.GetProjectionMatrix());
	Renderer::Submit(m_SquareVA);
	m_Shader->Bind();
	m_Shader->UpLoadUniformMat4("u_ViewProjectionMatrix", m_Camera.GetProjectionMatrix());
	Renderer::Submit(m_VertexArray);
	...
}
```

inside renderer class, we are uploading the camera infomation (projectionmatrix) when begin scene. and storing the matrix in the struct scene data.

```c++
void Renderer::BeginScene(OrthographicCamera& camera)
{
	//not get projectionmatrix!!!!!!
	m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

struct SceneData 
{
	glm::mat4 ViewProjectionMatrix;
};
```

OpenGL Uniform variable:

---
**Uniform Variable in OpenGL**

A uniform is a global Shader variable declared with the "uniform" storage qualifier. These act as parameters that the user of a shader program can pass to that program. Their values are stored in a program object. 

---

so inside shader we would have to uploade the uniform matrix:

```c++
void Shader::UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	//it is based on assumption that shader is already binded
	//First Get the matrix location
	GLint Location = glGetUniformLocation(m_RenderID, name.c_str());
	//location, how many matrix, whether we should transpose, pointer to the value
	glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(matrix));
}
```

### [2022/8/24] moving some renderer codes into client, add camera movement

#### old codes of renderer

before deleting all the commands, i leave it here incase i forget :grimacing:

```c++
//Steps: Vertex Array + Vertex Buffer + Index Buffer
//Shader, use default shader
m_VertexArray.reset(VertexArray::Create());
// generate vertex array object names in here 'm_VertexArray', and bind the namewith the object
// 2022-8-19 we are going to make it abstract move it to openglvertexarray.h
/*	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);*/

float vertices[3 * 7] = {
	-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
	0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
	0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
};

//	generate buffer object names and bind the vertex attributes target
//	we dont need to genearte here code by code (so thtere are three commend outlines) 
//	since we have a openglBuffer class for generation now
//	 instead we use the unique pointer of vertex buffer and construct it
//	glGenBuffers(1, &m_VertexBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
//	//upload data to gpu, static draw meaning we are not continuing refreshing
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	m_VertexBuffer->Bind();
//	constructing buffer layout class by sending bufferelements
//	2022-8-19: and part of vertex attribt dealing function is moved toopenglvertexarray AddVertexBuffer
BufferLayout Elementlayout{
	//takes in buffer elements initializer_list
	{ ShaderDataType::Float3, "a_Position" },
	{ ShaderDataType::Float4, "a_Color "}
};
std::shared_ptr<VertexBuffer> m_VertexBuffer;
m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
m_VertexBuffer->SetLayout(Elementlayout);
m_VertexArray->AddVertexBuffer(m_VertexBuffer);
/* // 2022-8-19 we are going to make it abstract
// this is moving to openglvertexarray class AddVertexBuffer()
uint32_t index = 0;
const auto& layout = m_VertexBuffer->GetLayout();
for (const auto& element : layout)
{
	//enable the first vertex attribute
	glEnableVertexAttribArray(index);
	//define an array of generic vertex attribute data, stride meaning each column of 3*3 has 3 float data (每行有三个float)
	//2022-8-18: conversion of ShaderDataType into gl function parameters
	glVertexAttribPointer(index,
		element.GetComponentCount(),
		ShaderDataTypeToOpenGLBaseType(element.Type),
		element.Normalized ? GL_TRUE : GL_FALSE,
		layout.GetStride(),
		(const void*)element.Offset
	);
	index++;
}*/

// same as buffer, we have now a interface class of index buffer class to genearteand bind for us
// so the following three codes are commended
// glGenBuffers(1, &m_IndexBuffer);
// // what order to draw, target: Vertex array indices
// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
unsigned int indices[3] = { 0, 1, 2 };
std::shared_ptr<IndexBuffer> m_IndexBuffer;
m_IndexBuffer.reset(IndexBuffer::Create(indices, (sizeof(indices) / sizeo(uint32_t))));
m_VertexArray->SetIndexBuffer(m_IndexBuffer);
m_SquareVA.reset(VertexArray::Create());
float SqaureVertices[3 * 4] = {
	-0.75f, -0.75f, 0.0f, 
	0.75f, -0.75f, 0.0f,
	0.75f, 0.75f, 0.0f,
	-0.75f, 0.75f, 0.0f
};
std::shared_ptr<VertexBuffer> SquareVB; 
SquareVB.reset(VertexBuffer::Create(SqaureVertices, sizeof(SqaureVertices)));
BufferLayout SquareVBlayout{
	//takes in buffer elements initializer_list
	{ ShaderDataType::Float3, "a_Position" },
};
SquareVB->SetLayout(SquareVBlayout);
m_SquareVA->AddVertexBuffer(SquareVB);
unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0};
std::shared_ptr<IndexBuffer>SquareIndexBuffer; 
SquareIndexBuffer.reset(IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) /sizeof(uint32_t))));
m_SquareVA->SetIndexBuffer(SquareIndexBuffer);
//source code of shader
//2022-8-23 adding view projeciton matrix
std::string vertexSrc = R"(
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec4 a_Color;

	uniform mat4 u_ViewProjection;
	out vec3 v_Position;
	out vec4 v_Color;
	
	void main()
	{
		v_Position = a_Position;
		v_Color  = a_Color;
		gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
	}
)";
std::string fragmentSrc = R"(
	#version 330 core
	
	layout(location = 0) out vec4 color;
	in vec3 v_Position;
	in vec4 v_Color;
	void main()
	{
		color = vec4(v_Position * 0.5 + 0.5, 1.0);
		color = v_Color;
	}
)";
m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
//source code of shader
std::string BlueShadervertexSrc = R"(
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;
	out vec3 v_Position;
	
	uniform mat4 u_ViewProjection;			
	void main()
	{
		v_Position = a_Position;
		gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
	}
)";
std::string BlueShaderfragmentSrc = R"(
	#version 330 core
	
	layout(location = 0) out vec4 color;
	in vec4 v_Color;
	void main()
	{
		color = vec4(0.2, 0.3, 0.8, 1.0);
	}
)";
m_BlueShader.reset(new Shader(BlueShadervertexSrc, BlueShaderfragmentSrc));
```

```c++
//2022-8-21 using renderercommand to deal with specific actions now
//glClearColor(0.1f, 0.1f, 0.1f, 1);
//glClear(GL_COLOR_BUFFER_BIT);
RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
RenderCommand::Clear();
m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
m_Camera.SetRotation(45.0f);
Renderer::BeginScene(m_Camera);
//draw square in blue
//2022-8-21 draw elements are moving to specific api to draw!
//Renderer::Submit do the work!
//m_BlueShader->Bind();
//2022-8-23 uploade uniform matrix and moved UpLoadUniformMat4() to renderer tohandle
//m_BlueShader->UpLoadUniformMat4("u_ViewProjection", m_Camera.GetProjectionMatri());
Renderer::Submit(m_BlueShader, m_SquareVA);
//m_Shader->Bind();
//m_Shader->UpLoadUniformMat4("u_ViewProjection", m_Camera.GetProjectionMatrix());
Renderer::Submit(m_Shader, m_VertexArray);
Renderer::EndScene();
```

#### moving camera inside application

a bad way of using onevent system to dispachter movement. because it is fully dependent on client frame. one client -> one movement. so it is not smooth at all

```c++
void OnEvent(KaluoEngine::Event& event) override
{
	//KALUO_TRACE("{0} event update", event);
	//if (event.GetEventType() == KaluoEngine::EventType::KeyPressed)
	//{
	//	KaluoEngine::KeyPressedEvent& e = (KaluoEngine::KeyPressedEvent&)event;
	//	//KALUO_TRACE("key code {0}", (char)e.GetKeyCode());
	//	if (e.GetKeyCode() == KALUO_KEY_TAB)
	//	{
	//		KALUO_TRACE("Tab key is pressed (event)");
	//	}
	//}
	KaluoEngine::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KaluoEngine::KeyPressedEvent>(KALUO_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
}
bool OnKeyPressedEvent(KaluoEngine::KeyPressedEvent& event) 
{
	KALUO_INFO("{0} key is pressed!", event.GetKeyCode());
	if (event.GetKeyCode() == KALUO_KEY_LEFT)
		//moving camera to left
		m_CameraPosition.x -= m_CameraMoveSpeed;
	if (event.GetKeyCode() == KALUO_KEY_RIGHT)
		m_CameraPosition.x += m_CameraMoveSpeed;			
	if (event.GetKeyCode() == KALUO_KEY_UP)		
		m_CameraPosition.y += m_CameraMoveSpeed;		
	if (event.GetKeyCode() == KALUO_KEY_DOWN)
		m_CameraPosition.y -= m_CameraMoveSpeed;
	return false;
}
```

instead we need to use the poll system in the ondate and later bind it with delta time system
(done in 8-25)

```c++
void OnUpdate() override
{
//2022-8-24 using polling system to move the camera
if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_LEFT))
	//moving camera to left
	m_CameraPosition.x -= m_CameraMoveSpeed;
else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_RIGHT))
	m_CameraPosition.x += m_CameraMoveSpeed;
else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_UP))
	m_CameraPosition.y += m_CameraMoveSpeed;
else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_DOWN))
	m_CameraPosition.y -= m_CameraMoveSpeed;

if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_A))
	m_CameraRotation += m_CameraRotateSpeed;
else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_D))
	m_CameraRotation -= m_CameraRotateSpeed;
...
}
```

### [2022-8-25] time steps, delta time

goal: create time steps so that the camera moves the same speed no matter what frame rate

essential: how long last frame took? sec/frame. 60 fps -> Deltatime = 0.016. 30 fps -> 0.033...

OnUpdate() function will take the delta time. if we want to move from left to right in 1 sec.
60fps, 30fps should rendering in different rate. 

for example in an turning function, we would like to have it like:
Rate * BaseTurnRate * DeltaTime. as rate represent the force of the joycon.

it is now calculated as:

```c++
while (m_Running) 
{
	//2022-8-26 Delta time added
	float time = (float)glfwGetTime(); // Platform：:：GetTime
	TimeStep timestep = time - m_LastFrameTime;
	m_LastFrameTime = time;
...
}
//for on update function it takes deltatime function now
virtual void OnUpdate(TimeStep timestep) {}
//now for camera in sandebox:
void OnUpdate(KaluoEngine::TimeStep timestep) override
{
//2022-8-26 getting timesteps which calculated in application run function
KALUO_TRACE("DeltaTIme {0}, {1}ms", timestep.GetSeconds(), timestep.GetMillseconds));
//operator casting time step into a float
float DeltaTime = timestep;
//2022-8-24 using polling system to move the camera
if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_LEFT))
	//moving camera to left
	m_CameraPosition.x -= m_CameraMoveSpeed * DeltaTime;
else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_RIGHT))
	m_CameraPosition.x += m_CameraMoveSpeed * DeltaTime;
else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_UP))
	m_CameraPosition.y += m_CameraMoveSpeed * DeltaTime;
else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_DOWN))
	m_CameraPosition.y -= m_CameraMoveSpeed * DeltaTime;

if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_A))
	m_CameraRotation += m_CameraRotateSpeed * DeltaTime;
else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_D))
	m_CameraRotation -= m_CameraRotateSpeed * DeltaTime;
}
```

### [2022-8-28]Transform and Material

#### Transform

per mesh. when submiting in the renderer, it takes in as parameter for each mesh.
if 2d when do not need a a material transfrom, but in 3d we need.

and the model matrix (transofm matrix) is now added into render submit function

- [order of equation in calculation](#order-of-equation-in-calculation)

```c++
static void Submit(
	const std::shared_ptr<Shader>& shader,
	const std::shared_ptr<VertexArray>& vertexArray,
	const glm::mat4& transformMatrix = glm::mat4(1.0f)
);

//how to use submit in example
{
glm::vec3 pos(x, y, 0.0f);
glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
KaluoEngine::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
}
```

#### Material

now we have vertex position, model position (transform)
material makes shader flexible. feed data into shader and it comes out with detials of texture/color/rough-smooth.
material is a bunch of material and a shader.
so we defintely need a material class. How to define the data?

some goals:

```c++
KaluoEngine::MaterialRef material = new KaluoEngine::Material(m_FlatColorShader);
KaluoEngine::MaterialInstanceRef materialinstance = new KaluoEngine::MaterialInstance(material);

materialinstance->Set("uColor", RedColor);
materialinstance->Set("u+AlbedoMap", texture);
```

render sorting. red render with reds, green with greens... 
bind red material, render. bind green, render.

### [2022-8-29] Shader Class Abstraction

move everything from shader class into openglshader
```c++

namespace KaluoEngine {
	class OpenGLShader : public Shader
	{
	public:
		//from opengl wiki we know it takes two parameters of a vertex/fragment shader
		//std::string vertexSource = // Get source code for vertex shader.
		// std::string fragmentSource = // Get source code for fragment shader.
		OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float values);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& values);
		void UpLoadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;

	};
}
```

inside sandboxapp we could dynamically change the color pointer now

```c++
virtual void OnImGuiRender() override
{
	ImGui::Begin("Kaluo Engine Info:");
	ImGui::Text("Hello World");
	//2022-8-29 
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
```

### [2022-8-30] Smart pointer, refs and some encapsulations. Textures

in the future. have context of entire scene, before rendering. because we need sorting, coloring, for improving performance.
shader objects are held the reference, vertex array as well.
multi-threads
shared_ptr (thread safety), unique_ptr 
< https://www.cyhone.com/articles/right-way-to-use-cpp-smart-pointer/ >

#### own type of shared ptr - Engine Ref, Scope

Scope: Engine scope
Ref: Shared ptr

```c++
namespace KaluoEngine { 
	template <typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T>
	using Ref = std::shared_ptr<T>;
}
```

#### Textures

Buffer of memories. stored in the VRam
Normal mapping, lookup textures.

Goal: load image file, and render it inside engine.
Geometry: what data do we need? Texture Coordinate
Texture class: load and upload

```c++
//2022-8-30 add texture coordinate
float SqaureVertices[5 * 4] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
}
```

#### OpenGLTexture Class

it is for sure based on abstract texture class so not shown here

```c++
class OpenGLTexture2D : public Texture2D
{
public:
	OpenGLTexture2D(const std::string& path);
	virtual ~OpenGLTexture2D();
	virtual uint32_t GetWidth() const override { return m_Width; }
	virtual uint32_t GetHeight() const override { return m_Height; }
	virtual void Bind(uint32_t slot = 0) const override;
private:
	std::string m_Path;
	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_RendererID;
};

OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	: m_Path(path)
{
	int width, height, channels;
	//flip the data for opengl
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	KALUO_CORE_ASSERT(data, "Failed to load image!");
	m_Width = width;
	m_Height = height;
	//upload buffer into gpu
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//not using linear filter
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);
	//dealloacate from cpu
	stbi_image_free(data);
}
OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_RendererID);
}
void OpenGLTexture2D::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_RendererID);
}
```

and example of loading a png

```c++
//2022-8-30 TextureShader
std::string TextureShadervertexSrc = R"(
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec2 a_TextureCoord;
	uniform mat4 u_ViewProjection;			
	uniform mat4 u_Transform;
	out vec2 v_TextureCoord;
	void main()
	{
		v_TextureCoord = a_TextureCoord;
		gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
	}
)";
std::string TextureShaderFragmentSrc = R"(
	#version 330 core
	
	layout(location = 0) out vec4 color;
	in vec2 v_TextureCoord;
	uniform sampler2D u_Texture;
	void main()
	{
		//sample a texture
		color = texture(u_Texture, v_TextureCoord);
	}
)";
m_TextureShader.reset(KaluoEngine::Shader::Create(TextureShadervertexSrc, TextureShaderFragmentSrc));

m_Texture = KaluoEngine::Texture2D::Create("assets/textures/Checkerboard.png");
std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_TextureShader)->Bind();
std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

//----- and bind it when Onupdate() ----
//2022-8-30 big sqaure with texture
m_Texture->Bind();
KaluoEngine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
```

### [2022-8-31] adding alpha channel, blending

there is problem of rendering alpha channel 

```c++
//we have only GL_RGB8 meaning only rgb channel here
glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);
```

so this can only handle three channel
added if check statement to handle this

```c++
//2022-8-31 channels and decide formats
GLenum internalFormat = 0, dataFormat = 0;
if (channels == 4)
{
	internalFormat = GL_RGBA8;
	dataFormat = GL_RGBA;
}
else if (channels == 3)
{
	internalFormat = GL_RGB8;
	dataFormat = GL_RGB;
}
```

#### blending function into opengl

how opengl treats alpha. Combines color together

<https://zhuanlan.zhihu.com/p/265177867>

```c++
void OpenGLRendererAPI::Init()
{
	/*
	* Enable Blend in opgngl
	* Gamma空间下的Alpha混合公式：color = (A.rgb * A.a) + (B.rgb * (1 - A.a))
	* Linear空间下的Alpha混合公式：color = ((A.rgb ^ 2.2 * A.a) + (B.rgb ^ 2.2 * (1 - A.a))) ^（1 / 2.2)
	*/ 	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
```
and enable this by calling ``` Renderer::Init(); ```

### [2022-9-1] shader asset files, learn some blending

vertex src string, frag src string. No
create and compile in files. Yes

goal: get rid of string first 

```c++
std::string BlueShadervertexSrc = R"(
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;
	out vec3 v_Position;
	
	uniform mat4 u_ViewProjection;			
	uniform mat4 u_Transform;
	void main()
	{
		v_Position = a_Position;
		gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
	}
)";
```

and instead just calling ``` Shader::Create("assets/shader/Texture.glsl"); ```
glsl -> OpenGL Shading Language

```c++
public:
	OpenGLShader(const std::string& FilePath);
private:
	//read from glsl file
	std::string ReadFile(const std::string& filepath);
	//devide into multiple shader source codes from readfile result
	//map from shader type to each shader souce codes
	std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

//implementation
static GLenum ShaderTypeFromString(const std::string& type)
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	if (type == "fragment" || type == "pixel")
		return GL_FRAGMENT_SHADER;
	KALUO_CORE_ASSERT(false, "Unknown shader type!");
	return 0;
}
OpenGLShader::OpenGLShader(const std::string& filepath)
{
	std::string source = ReadFile(filepath);
	auto shaderSources = PreProcess(source);
	Compile(shaderSources);
}
OpenGLShader::OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource)
{
	//2022-9-1 moving all compile sources into compile function
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = VertexSource;
	sources[GL_FRAGMENT_SHADER] = FragmentSource;
	Compile(sources);
}
std::string OpenGLShader::ReadFile(const std::string& filepath)
{
	std::string result;
	//at best treat it as a virtual file system
	std::ifstream in(filepath, std::ios::in, std::ios::binary);
	if (in)
	{
		//file pointer into end of the file
		in.seekg(0, std::ios::end);
		//set result to the size of the file
		result.resize(in.tellg());
		//set back to the begin of the string
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else
	{
		KALUO_CORE_ERROR("Could not open file '{0}'", filepath);
	}
	return result;
}
std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
{
	std::unordered_map<GLenum, std::string> shaderSources;
	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);
	//finding all the type token, and copy all the context
	while (pos != std::string::npos)
	{
		//end of line
		size_t eol = source.find_first_of("\r\n", pos);
		KALUO_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
		//copy the type name
		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		KALUO_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");
		//from here find the next type token
		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		pos = source.find(typeToken, nextLinePos);
		shaderSources[ShaderTypeFromString(type)] =
			source.substr(nextLinePos,
				//untill the end of this datatype or the end of the file
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
	}
	return shaderSources;
}
void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	GLuint program = glCreateProgram();
	std::vector<GLenum> glShaderIDs(shaderSources.size());
	// convert the old compile code into a loop
	for (auto& keyValue : shaderSources)
	{
		//shader type
		GLenum shaderType = keyValue.first;
		//shader source code
		const std::string& source = keyValue.second;
		// Create an empty shader handle, meaning: generate id
		GLuint Shader = glCreateShader(shaderType);
		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* sourceCStr = source.c_str();
		glShaderSource(Shader, 1, &sourceCStr, 0);
		// Compile the vertex shader
		glCompileShader(Shader);
		//check if compile succeed
		GLint isCompiled = 0;
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);
			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);
			// We don't need the shader anymore.
			glDeleteShader(Shader);
			// Use the infoLog as you see fit.
			KALUO_CORE_ERROR("{0}", infoLog.data());
			KALUO_CORE_ASSERT(false, "shader compiled failed!");
			// In this simple program, we'll just leave
			break;
		}
		// Attach our shaders to our program
		glAttachShader(program, Shader);
		glShaderIDs.push_back(Shader);
	}
	
	m_RendererID = program;

	// Link our program
	glLinkProgram(program);
	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		// We don't need the program anymore.
		glDeleteProgram(program);
		for(auto id : glShaderIDs)
		{
			// Don't leak shaders either.
			glDeleteShader(id);
		}
		// Use the infoLog as you see fit.
		KALUO_CORE_ERROR("{0}", infoLog.data());
		KALUO_CORE_ASSERT(false, "shader program link failed!");
		// In this simple program, we'll just leave
		return;
	}
	for (auto id : glShaderIDs)
	{
		// Always detach shaders after a successful link.
		glDetachShader(program, id);
	}
	
	}
```

compile function do the vertex/fragment shader compile in a loop. so that inside the construction function we just do read file -> preprocess the unordered map -> compile all the elements

#### Some Blending learn

3 ways of control in opengl:
1. glENable(GL_BLEND) 
2. glBlendFunc(src, dest). 
   src = how src RGBA factors is computed (default GL_ONE); dest = how dest RGBA factors is computed (default GL_ZERO)
3. glBlendEquation(mode)
   mode = how we combine the src and dest colors, default: GL_FUNC_ADD
so in there the default: 1 + 0 = 1. meaning use only source value

However in here
- [blending function into opengl](#blending-function-into-opengl)
we have src = GL_SRC_ALPHA. dest = GL_ONE_MINUS_SRC_ALPHA. so if the pixel rendering from texutre is transparent: meaning alpha = 0, then dest = 1 - 0 = 1 (take the inverse of the source alpha) so this mean "use the destination color"
R = (Rsrc * 0) + (Rdest * (1 - 0)) = Rdest
G = (Gsrc * 0) + (Gdest * (1 - 0)) = Gdest
B = (Bsrc * 0) + (Bdest * (1 - 0)) = Bdest
A = (Asrc * 0) + (Adest * (1 - 0)) = Adest

### [2022/9/2] Shader Library

small minor change in the openglshader class
change glshaderids from vectors to array
so that the memory goes through to stack allocation instead of heap
and we dont have to worry about the delete becasue it is part of compile function

#### ShaderLibrary Class

the name of the shader is extracted from the file path automatically
and use the name to find and stroe the shader in the library

goal:

```c++
//2022-9-2 using shaderlirary to store and handle all shader create and load
//the name of the shader is extracted from the file path automatically
auto m_TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

//---Upper: store shader by shaderlibrary-----Lower:Get shader by lirbrary

//2022-9-2 Using ShaderLIbrary to handle shader loading (meaning no more loacl varaibles)
auto m_TextureShader = m_ShaderLibrary.Get("Texture");
```

and the structure of the class:

```c++
class ShaderLibrary
{
public:
	//the const refference. because it only get copied when we go in to unordered_map
	void Add(const Ref<Shader>& shader);
	void Add(const std::string& name, const Ref<Shader>& shader);
	Ref<Shader> Load(const std::string& filePath); // assets/texture.glsl
	Ref<Shader> Load(const std::string& name, const std::string& filePath);
	Ref<Shader> Get(const std::string& name);
	bool Exists(const std::string& name) const;
private:
	std::unordered_map<std::string, Ref<Shader>> m_Shaders;
};

//implementation
void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
{
	//auto& name = shader->GetName();
	KALUO_CORE_ASSERT(!Exists(name), "shaders already exist!");
	m_Shaders[name] = shader;
}
void ShaderLibrary::Add(const Ref<Shader>& shader)
{
	auto& name = shader->GetName();
	KALUO_CORE_ASSERT(!Exists(name), "shaders already exist!");
	Add(name, shader);
}
Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
{
	//create -> add to m_shaders -> return
	auto shader = Shader::Create(filePath);
	Add(shader);
	return shader;
}
Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
{
	//create -> add to m_shaders -> return
	auto shader = Shader::Create(filePath);
	Add(name, shader);
	return shader;
}
Ref<Shader> ShaderLibrary::Get(const std::string& name)
{
	//
	KALUO_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "shaders not found!");
	
	return m_Shaders[name];
}
bool ShaderLibrary::Exists(const std::string& name) const
{
	return m_Shaders.find(name) != m_Shaders.end();
}
```

the way shader class extract the name of file

```c++
//2022-9-2 extract name of file and give it to shader class
// Example: assets/shaders/Texture.glsl
// so we are using the string after last slash and use it as name
auto LastSlash = filepath.find_last_of("/\\");
LastSlash = LastSlash == std::string::npos ? 0 : LastSlash + 1;
auto LastDot = filepath.rfind('.');
//determine the index if no last dot found
auto Count = LastDot == std::string::npos ? filepath.size() - LastSlash : LastDot -LastSlash;
m_Name = filepath.substr(LastSlash, Count);
```

### [2022/9/4] 2D renderer planing

differences bettwen our renderer and 2D renderer
2D does not nesscesary need shader submit, vertex array submit, view projection matrix.
2D does not worry about different shaders.

if we handle all inside a renderer class api, it is easy to cause confusion

```c++
KaluoEngine::Renderer::BeginScene(m_Camera);
KaluoEngine::Renderer::BeginScene2D(m_Camera)
KaluoEngine::Renderer::DrawQuad(m_Scene); // draw in 2d?
KaluoEngine::Renderer::DrawRecTangle(m_Scene); // or 3D?
```

so goal: ``` KaluoEngine::Renderer2D::BeginScene(m_Scene2D); ```
in beginscene handling with specific camera
drawthings(parameters), position, size, color/texture...

what could be a thing: a lot of 2D quads on the screen at one time, batching handling all quads. if draw-call each quads once, the framerate will be terrible. what we actaully do is batch all quads into one geometry. vertex buffers form into big vertex buffers.

so we want to have a batch renderer. Texture atlas system, 

For animate sprite (animation): use delta into nearest key frame and play next frame.

For UI: layout system. for each resolution still in correct position. 

### [2022-9-5] camera controller

wrapper of camera class

controller is not near to renderer but to the user interaction. and it malnipulates these paroperties in the camera class

```c++
private:
glm::mat4 m_ProjectionMatrix;
glm::mat4 m_ViewMatrix;
glm::mat4 m_ViewProjectionMatrix;
```
#### details of camera controller (orthographic)

it binds onupdate, onevent and calculates the zoom level and aspectratio depends on the values

```c++
class OrthographicCameraController
{
public:
	// aspectratio * 2 units
	// zoom level of 1.0f
	OrthographicCameraController(float aspectRatio, bool rotation = false); 

	void SetPosition(float left, float right, float bottom, float top);
	void OnEvent(Event& e);
	void OnUpdate(TimeStep DeltaTime);
	OrthographicCamera& GetCamera() { return m_Camera; }
	const OrthographicCamera& GetCamera() const{ return m_Camera; }
private:
	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnWindowResized(WindowResizeEvent& e);
}

OrthographicCameraController::OrthographicCameraController(float apspectRatio, bool rotation)
	: m_AspectRatio(apspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
{
}
void OrthographicCameraController::OnUpdate(TimeStep Deltatime)
{
	//2022-8-24 using polling system to move the camera
	if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_A))
		m_CameraPosition.x -= m_CameraTranslationSpeed * Deltatime;
	else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_D))
		m_CameraPosition.x += m_CameraTranslationSpeed * Deltatime;
	if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_W))
		m_CameraPosition.y += m_CameraTranslationSpeed * Deltatime;
	else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_S))
		m_CameraPosition.y -= m_CameraTranslationSpeed * Deltatime;
	if (m_Rotation)
	{
		if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_Q))
			m_CameraRotation += m_CameraRotateSpeed * Deltatime;
		else if (KaluoEngine::Input::IsKeyPressed(KALUO_KEY_E))
			m_CameraRotation -= m_CameraRotateSpeed * Deltatime;
		m_Camera.SetRotation(m_CameraRotation);
	}
	
	m_Camera.SetPosition(m_CameraPosition);
	
	//the higher zoom level is the slower the move speed
	m_CameraTranslationSpeed = m_ZoomLevel;
}
void OrthographicCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(KALUO_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(KALUO_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}
bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
 	m_ZoomLevel -= e.GetYOffset() * 0.2f;
	
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	//reset the view projection matrix and m_ProjectionMatrix
	m_Camera.SetPosition(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{
	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	//reset the view projection matrix and m_ProjectionMatrix
	m_Camera.SetPosition(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}
```

### [2022-9-6] Some Organizing and Maintenance 

supporting different platforms, rename the batch file moved to scrips folder.
For now only generate project batfile, later will be build and more file.

### [2022-9-7] SandBox 2D rendering 

#### moving sandbox example layers stuffs into sandbox 2d layer

incase i forgot some comments, i copied some codes here :sweat_smile:

```c++

ExampleLayer()
	: Layer("Example Layer"), m_CameraController(1280.0f / 720.f)
{
	//Steps: Vertex Array + Vertex Buffer + Index Buffer
	//Shader, use default shader
	m_VertexArray.reset(KaluoEngine::VertexArray::Create());

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	KaluoEngine::BufferLayout Elementlayout{
		//takes in buffer elements initializer_list
		{ KaluoEngine::ShaderDataType::Float3, "a_Position" },
		{ KaluoEngine::ShaderDataType::Float4, "a_Color "}
	};
	KaluoEngine::Ref<KaluoEngine::VertexBuffer> m_VertexBuffer;
	m_VertexBuffer.reset(KaluoEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
	m_VertexBuffer->SetLayout(Elementlayout);
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	unsigned int indices[3] = { 0, 1, 2 };
	KaluoEngine::Ref<KaluoEngine::IndexBuffer> m_IndexBuffer;
	m_IndexBuffer.reset(KaluoEngine::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	m_SquareVA.reset(KaluoEngine::VertexArray::Create());

	//2022-8-30 add texture coordinate
	//button left->button right->up right->up left
	float SqaureVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};

	KaluoEngine::Ref<KaluoEngine::VertexBuffer> SquareVB;
	SquareVB.reset(KaluoEngine::VertexBuffer::Create(SqaureVertices, sizeof(SqaureVertices)));
	KaluoEngine::BufferLayout SquareVBlayout{
		//takes in buffer elements initializer_list
		{ KaluoEngine::ShaderDataType::Float3, "a_Position" },
		{ KaluoEngine::ShaderDataType::Float2, "a_TextureCoord"},
	};
	SquareVB->SetLayout(SquareVBlayout);
	m_SquareVA->AddVertexBuffer(SquareVB);

	unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	KaluoEngine::Ref<KaluoEngine::IndexBuffer>SquareIndexBuffer;
	SquareIndexBuffer.reset(KaluoEngine::IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
	m_SquareVA->SetIndexBuffer(SquareIndexBuffer);

	std::string vertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec3 v_Position;
		out vec4 v_Color;
		
		void main()
		{
			v_Position = a_Position;
			v_Color  = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
		}
	)";

	std::string fragmentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 color;
		in vec3 v_Position;
		in vec4 v_Color;

		void main()
		{
			color = vec4(v_Position * 0.5 + 0.5, 1.0);
			color = v_Color;

		}
	)";
	//2022-8-29 change to abstract class creation
	m_Shader = (KaluoEngine::Shader::Create("VertexPos Color shader", vertexSrc, fragmentSrc));

	//Shader::Create("assets/shader/Texture.glsl");

	//source code of shader
	std::string BlueShadervertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		out vec3 v_Position;
		
		uniform mat4 u_ViewProjection;			
		uniform mat4 u_Transform;

		void main()
		{
			v_Position = a_Position;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
		}
	)";

	std::string FlatColorShaderFragmentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 color;
		in vec4 v_Color;

		uniform vec3 u_Color;

		void main()
		{
			color =vec4(u_Color, 1.0f);
		}
	)";
	//2022-8-29 Triangle change to abstract class creation
	m_FlatColorShader = KaluoEngine::Shader::Create("Flat color shader", BlueShadervertexSrc, FlatColorShaderFragmentSrc);
	
	//2022-8-30 TextureShader
	//2022-9-1 moving the texture.glsl to handle shader create
	//2022-9-2 using shaderlirary to store and handle all shader create and load
	auto m_TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
	
	m_Texture = KaluoEngine::Texture2D::Create("assets/textures/Checkerboard.png");
	//2022-8-31 testing alpha channel rendering
	m_LogoTexture = KaluoEngine::Texture2D::Create("assets/textures/ChernoLogo.png");

	std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_TextureShader)->Bind();
	std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
}

void OnUpdate(KaluoEngine::TimeStep timestep) override
{
	//operator casting time step into a float
	//KALUO_TRACE("DeltaTIme {0}, {1}ms", timestep.GetSeconds(), timestep.GetMillseconds());

	//render stuffs
	KaluoEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	KaluoEngine::RenderCommand::Clear();

	//2022-9-5 move all camera handling into camera controller class
	/*m_Camera.SetPosition(m_CameraPosition);
	m_Camera.SetRotation(m_CameraRotation);*/

	KaluoEngine::Renderer::BeginScene(m_CameraController.GetCamera());
	//2022-9-4 2Drenderer class planning
	//KaluoEngine::Renderer2D::BeginScene2D(m_Camera);
	//KaluoEngine::Renderer2D::DrawCircle(...);


	//2022-8-28 create a transfom matrix based on vec3 squareposition 
	//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SqaurePosition);
	//10% scale matrix
	static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	//some goals of material system
	/*
	KaluoEngine::MaterialRef material = new KaluoEngine::Material(m_FlatColorShader);
	KaluoEngine::MaterialInstanceRef materialinstance = new KaluoEngine::MaterialInstance(material);

	materialinstance->Set("uColor", RedColor);
	materialinstance->Set("u+AlbedoMap", texture);
	*/

	//2022-8-29 temporary cast the shader into openglshader and bind it
	std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<KaluoEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

	//render 25 different small sqaure for testing tranform matrix
	for (int y = 0; y < 20; y++) 
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			KaluoEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}
	//2022-9-2 Using ShaderLIbrary to handle shader loading (meaning no more loacl varaibles)
	auto m_TextureShader = m_ShaderLibrary.Get("Texture");

	//2022-8-30 big sqaure with texture
	m_Texture->Bind();
	KaluoEngine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	//2022-8-31 adding alpha channel into the rendering 
	m_LogoTexture->Bind();
	KaluoEngine::Renderer::Submit(m_TextureShader, m_SquareVA, 
		glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	// Triangle
	//KaluoEngine::Renderer::Submit(m_Shader, m_VertexArray);

	KaluoEngine::Renderer::EndScene();
}
```

When having this error :

![image](https://github.com/Zhengkaluo/GameEngine_PersonalProject/blob/main/IMG/Trciky%20Errors.png)

when we go to kaluoengine header, it contains entry point and entry point contains a main function, so we do not include entiry point at our engine file
```
//---Entry point------

#include "KaluoEngine/Core/EntryPoint.h"

//------


//entry point
#ifdef KALUO_PLATFORM_WINDOWS

//create engine application 

extern KaluoEngine::Application* KaluoEngine::CreateApplication();

int main(int argc, char** argv)
{
.....
}
#endif
```

### [2022-9-9] starting 2d rendering. 

some plans: profiling and memory tracking. custom memoory allocation

rendering in general should be static and we dont want multiple renderer2D at once.

for now positive z value go towards the camera and negative is away of camera

inside the renderer2d class we would like to customize the storage of 2d data

```c++
struct Renderer2DStorage
{
	Ref<VertexArray> QuadVertexArray;
	Ref<Shader> FlatColorShader;
};
```

in Init function() it has testing data

```c++
void Renderer2D::Init()
{
	s_Data = new Renderer2DStorage();
	//using 2d storage to store the vertex array
	s_Data->QuadVertexArray = (VertexArray::Create());
	//2022-9-9 these datas are all for testing this api
	float SqaureVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	Ref<VertexBuffer> SquareVB;
	SquareVB.reset(VertexBuffer::Create(SqaureVertices, sizeof(SqaureVertices)));
	BufferLayout SquareVBlayout{
		//takes in buffer elements initializer_list
		{ ShaderDataType::Float3, "a_Position" }
	};
	SquareVB->SetLayout(SquareVBlayout);
	s_Data->QuadVertexArray->AddVertexBuffer(SquareVB);
	unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Ref<IndexBuffer>SquareIndexBuffer;
	SquareIndexBuffer.reset(IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
	s_Data->QuadVertexArray->SetIndexBuffer(SquareIndexBuffer);
	s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
}
```

### [2022-9-10] Setting 2D renderer Transform

Setting Individual uniform transfom matrix

Set vs Upload. different. Set is depends on numbers of factors whereas upload matrix in here is purely opengl concept

#### setting transfom

Position = viewprojectionmatrix * transofm * position
transfom handle as translation and scale

```c++
void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
//...
//2022-9-10 handling transform matrix as position and scale
glm::mat4 transfom = glm::translate(glm::mat4(1.0f), position) * /* rotation can be added here*/
	glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
(s_Data->FlatColorShader)->SetMat4("u_Transform", transfom);
//...
}
```

### [2022-9-10] Setting 2D renderer texture

easy work today 

```c++
void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
{
	(s_Data->TextureShader)->SetFloat4("u_Color", glm::vec4(1.0f));
	(s_Data->TextureShader)->Bind();
	
	//instead of setting color, we set texture
	texture->Bind();
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	s_Data->TextureShader->SetMat4("u_Transform", transform);
	s_Data->QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	//texture->UnBind();
}
```

### [2022-9-13] single shader 2d renderer

set a default texture bound.
extend texture api for creating texture from code (meaning craeting a entire texture by one vec4)

m_DataFormat and m_internalFormat are made global instead of local like before

```c++
//constructor of a simple entire colro texture
OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
	: m_Width(width), m_Height(height)
{
	//GLenum internalFormat = GL_RGBA8, dataFormat = GL_RGBA;
	m_InternalFormat = GL_RGBA8;
	m_DataFormat = GL_RGBA;
	//upload buffer into gpu
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//not using linear filter
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

//set entire texutre (pure color)
void OpenGLTexture2D::SetData(void* data, uint32_t size)
{
	//either 4 or 3 depends on the dataformat
	uint32_t BytePerChannel = m_DataFormat == GL_RGBA ? 4 : 3;
	KALUO_CORE_ASSERT(size == m_Width * m_Height * BytePerChannel, "Data must be entire texture!");
	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
}
```

### [2022-9-15] Starting of profiling

drag some numbers out and later visualized them

#### timer class

>> __LINE__ __LINE__ is a preprocessor macro that expands to current line number in the source file, as an integer. __LINE__ is useful when generating log statements, error messages intended for programmers, when throwing exceptions, or when writing debugging code

```c++
//type of lambda
template<typename Fn>
class Timer
{
public:
	//using const char* as static string instead of string type
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Stopped(false), m_Func(func)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto EndTimePoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimePoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		
		//call back the lamda function, in here is pushing back the result to the profile result
		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
	bool m_Stopped;

	Fn m_Func;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })
```

how to visualized the data:
```c++
void SandBox2D::OnImGuiRender()
{
	ImGui::Begin("Kaluo Engine Info:");
	ImGui::Text("Hello World");
	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "  %.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}
```

example of using

```c++
//2022-9-15 profiling using timer
PROFILE_SCOPE("SandBox2D::OnUpdate");
//2022-9-5 all camera stuffs move into camera controller
{
	PROFILE_SCOPE("CameraController.Onupdate");
	m_CameraController.OnUpdate(timestep);
}
{
	PROFILE_SCOPE("Render Preparation");
	//render stuffs
	KaluoEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	KaluoEngine::RenderCommand::Clear();
}
```