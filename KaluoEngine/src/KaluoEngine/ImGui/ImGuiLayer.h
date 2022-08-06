#pragma once

#include "KaluoEngine/Layer.h"
#include "KaluoEngine/Events/Event.h"
#include "KaluoEngine/Events/MouseEvent.h"
#include "KaluoEngine/Events/KeyEvent.h"
#include "KaluoEngine/Events/ApplicationEvent.h"

namespace KaluoEngine {

	class KALUO_API ImGuiLayer : public Layer
	{
	public:

		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& event);

	public:
		//call back functions
		//void WindowFocusCallback(GLFWwindow* window, int focused);
		//void OnMousePressedEvent(MouseButtonEvent& event);
	
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);

		bool OnKeyTypedEvent(KeyTypedEvent& event);

		//bool OnMouseButtonEvent(MouseButtonEvent& event);
		bool OnWindowResizedEvent(WindowResizeEvent& event);
		
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
	
		

	private:
		float m_Time = 0.0f;
	};






}
