#pragma once

#include "KaluoEngine/Core/TimeStep.h"
#include "KaluoEngine/Renderer/OrthographicCamera.h"

#include "KaluoEngine/Events/ApplicationEvent.h"
#include "KaluoEngine/Events/MouseEvent.h"

namespace KaluoEngine {
	//2022-9-5 
	//controller class for handling window camera controller when event and updates
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

	private:
		//initialized these before the target camera getting constructed
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		OrthographicCamera m_Camera;

		//determine whether the camera can rotate
		bool m_Rotation;

		//in a second moved 1.3f unit and 180 degree
		float m_CameraTranslationSpeed = 1.3f;
		float m_CameraRotateSpeed = 180.0f;

		//properties of the camera
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
	};
}