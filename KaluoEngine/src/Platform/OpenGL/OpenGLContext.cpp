#include "Kaluopch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>
namespace KaluoEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: m_windowHandle(windowHandle)
	{
		KALUO_CORE_ASSERT(windowHandle, "window handle is null!");
	}

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
}