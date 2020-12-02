#include "xenospch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Xenos
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Xenos::ShaderDataType::Float: return GL_FLOAT;
		case Xenos::ShaderDataType::Float2: return GL_FLOAT;
		case Xenos::ShaderDataType::Float3:return GL_FLOAT;
		case Xenos::ShaderDataType::Float4:return GL_FLOAT;
		case Xenos::ShaderDataType::Mat3:return GL_FLOAT;
		case Xenos::ShaderDataType::Mat4:return GL_FLOAT;
		case Xenos::ShaderDataType::Int:return GL_INT;
		case Xenos::ShaderDataType::Int2:return GL_INT;
		case Xenos::ShaderDataType::Int3:return GL_INT;
		case Xenos::ShaderDataType::Int4:return GL_INT;
		case Xenos::ShaderDataType::Boolean:return GL_BOOL;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		XS_PROFILE_FUNCTION();
		glGenVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		XS_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		XS_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::UnBind() const
	{
		XS_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		XS_PROFILE_FUNCTION();
		XS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no Layout!");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		XS_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}