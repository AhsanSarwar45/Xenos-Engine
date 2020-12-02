#include "xenospch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Xenos
{
	void VertexBuffer::Bind() const
	{
	}
	void VertexBuffer::UnBind() const
	{
	}
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XS_CORE_ASSERT(false, "RendererAPI::None is currently no supported");
			return nullptr;
		case RendererAPI::API::OpenGL:

 			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		default:

			break;
		}

		XS_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XS_CORE_ASSERT(false, "RendererAPI::None is currently no supported");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return CreateRef<OpenGLVertexBuffer>(size);
		default:

			break;
		}

		XS_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
	void IndexBuffer::Bind() const
	{
	}
	void IndexBuffer::UnBind() const
	{
	}
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XS_CORE_ASSERT(false, "RendererAPI::None is currently no supported");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return CreateRef<OpenGLIndexBuffer>(indices, count);
		default:

			break;
		}

		XS_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}