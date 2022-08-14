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

		//check what gpu we are using:
		KALUO_CORE_INFO("OpenGL vendor: {0}", glGetString(GL_VENDOR));
		KALUO_CORE_INFO("OpenGL renderer: {0}", glGetString(GL_RENDERER));
		KALUO_CORE_INFO("OpenGL version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}