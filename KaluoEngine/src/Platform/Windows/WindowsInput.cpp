#include "Kaluopch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "KaluoEngine/Core/Application.h"

namespace KaluoEngine {

	//for creating an input instace
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int KeyCode)
	{
		//glfw get key is the essensial of getting key code
		//from application -> Window -> GLFWwindow
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		//represent state of the key return, press = 1, release = 0
		auto state =  glfwGetKey(window, KeyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		//glfw get key is the essensial of getting key code
		//from application -> Window -> GLFWwindow
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		//represent state of the key return, press = 1, release = 0
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return{ (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		/*GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);*/
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		/*GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);*/

		auto [x, y] = GetMousePositionImpl();

		return y;
	}
}