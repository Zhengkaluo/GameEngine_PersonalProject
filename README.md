# GameEngine_PersonalProject  

Start writing a simple game engine...  
Learning from the famous Hazel Engine  

Entry point: starting the application from the engine and defined by the client  

EventDispatcher: check if event type matches the statictype if yes then handle the event (which defined from the event func), it is getting called at Application::Onevent function

binding the event call back in the setup of window at the application construction (SetEventCallBack)

EventHandle Order (credit: <https://zhuanlan.zhihu.com/p/549038718>):  
![image](https://github.com/Zhengkaluo/GameEngine_PersonalProject/blob/main/IMG/EventHandleOrder.jpg)

ImGui layer inhieritated from layer class.  
construction by Onattach function, which calles from push layer function  
Update function: get singleton app -> size update->delta time update -> newframe of imgui -> render()  

The OnEvent Function: through imgui layer on event function,　construct one dispatcher and bind all events function into the dispatcher,　it check the event type and　fall them into corresponding type function

Input Pollling system:  
as Input class is pure virtual and windows input inherited from it. it gets to implemented by different interface (in here only windows, it could be other platform...)  
at windows input class, it gets key pressed() by getting from application -> Window -> GLFWwindow to call the function glfwgetkey and check if certain key is pressed. it is the same for mouse and mouse pos  
and it can be tested by application run function and call function like (auto [x, y] = Input::GetMousePosition();) and log it to test if it is working.  

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

## 2022/8/13:(render context)

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
