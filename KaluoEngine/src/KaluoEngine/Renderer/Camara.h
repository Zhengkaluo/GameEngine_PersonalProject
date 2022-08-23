#pragma once
#include <glm/glm.hpp>

namespace KaluoEngine{

	class Camera {
	public:
		Camera();
		~Camera();

	private:
		glm::vec4 m_Position;
		glm::vec4 m_Rotation;

		//projection matrix
		//perspective camera, orthographic camera
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		
		//define up vector for right vector
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);   
	};

	
}