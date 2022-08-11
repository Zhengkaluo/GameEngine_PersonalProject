# GameEngine_PersonalProject  
Start writing a simple game engine...  
Learning from the famous Hazel Engine  

Entry point: starting the application from the engine and defined by the client  

EventDispatcher: check if event type matches the statictype if yes then handle the event (which defined from the event func), it is getting called at Application::Onevent function

binding the event call back in the setup of window at the application construction (SetEventCallBack)

EventHandle Order (credit: https://zhuanlan.zhihu.com/p/549038718):  
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
```
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
```
	void OnEvent(KaluoEngine::Event& event) override
	{
		//KALUO_TRACE("{0} event update", event);
		if (event.GetEventType() == KaluoEngine::EventType::KeyPressed)
		{
			KaluoEngine::KeyPressedEvent& e = (KaluoEngine::KeyPressedEvent&)event;
			//KALUO_TRACE("key code {0}", (char)e.GetKeyCode());
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
``` 
m_ImGuiLayer = new ImGuiLayer; 
```
and render imgui layer at the run() function and eventually this part at application::run() will be run on the render thread later on update) 
```
	m_ImGuiLayer->Begin();
	for (Layer* EachLayer : m_LayerStack)
		EachLayer->OnImGuiRender();
	m_ImGuiLayer->End();
```

