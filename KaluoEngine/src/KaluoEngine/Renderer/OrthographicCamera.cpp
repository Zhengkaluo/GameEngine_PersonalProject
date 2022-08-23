#include "Kaluopch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>
namespace KaluoEngine{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}
	
	void OrthographicCamera::RecalculateViewMatrix()
	{
		//get the translation matrix and roation matrix
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		//invert it
		m_ViewMatrix = glm::inverse(transform);

		//set projection view matrix in opengl order
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
