#include "xenospch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Xenos
{

	Ref<VertexArray> VertexArray::Create()
	{

		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XS_CORE_ASSERT(false, "RendererAPI::None is currently no supported");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return std::make_shared<OpenGLVertexArray>();
		default:

			break;
		}

		XS_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}