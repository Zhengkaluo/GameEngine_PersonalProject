#include "Kaluopch.h"
//#include "KaluoEngine/Log.h"
#include "WindowsWindow.h"

#include "KaluoEngine/Events/ApplicationEvent.h"
#include "KaluoEngine/Events/KeyEvent.h"
#include "KaluoEngine/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

//glad is opengl specific so it moves to openglcontext.h and not here anymore
//#include <Glad/glad.h>

namespace KaluoEngine {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) 
	{
		KALUO_CORE_ERROR("GLFW ERROR ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		KALUO_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);


		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			KALUO_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		//create glfw window
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//typedef void (* GLFWwindowsizefun)(GLFWwindow* window, int width, int height);
		//Set GLFW CallBack
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			//cast to window data pointer
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			//dispatcher close event
			WindowCloseEvent event;
			data.EventCallback(event);
		});


		// @brief The function pointer type for keyboard key callbacks.
		//typedef void (* GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{

					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		//typedef void (* GLFWcharfun)(GLFWwindow* window, unsigned int codepoint);
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);
		});
		//typedef void (* GLFWmousebuttonfun)(GLFWwindow* window, int button, int action, int mods);
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});
		//typedef void (* GLFWscrollfun)(GLFWwindow* window, double xoffset, double yoffset);
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});


		
		//GLFWAPI GLFWcursorposfun glfwSetCursorPosCallback(GLFWwindow * handle,
		//		GLFWcursorposfun cbfun)
		//typedef void (* GLFWcursorposfun)(GLFWwindow* window, double xpos, double ypos);
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			MouseMovedEvent event((float)xpos, (float)ypos);
			data.EventCallback(event);
		});
		
	}

	void WindowsWindow::Shutdown()
	{
		//close window
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}