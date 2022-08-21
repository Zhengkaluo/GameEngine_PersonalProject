#include "Kaluopch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"


namespace KaluoEngine {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;


}