#include "Kaluopch.h"
#include "OrthographicCameraController.h"

#include "KaluoEngine/Core/Input.h"
#include "KaluoEngine/Core/KeyCodes.h"

namespace KaluoEngine {
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
}