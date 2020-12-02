#include "xenospch.h"
#include "Xenos/Renderer/FrameBuffer.h"
#include "Xenos/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Xenos
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XS_CORE_ASSERT(false, "RendererAPI::None is currently no supported");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return CreateRef<OpenGLFrameBuffer>(spec);
		default:

			break;
		}

		XS_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}