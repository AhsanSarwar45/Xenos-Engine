#include "xenospch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Xenos
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
