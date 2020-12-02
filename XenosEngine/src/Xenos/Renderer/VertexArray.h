#pragma once
#include <memory>
#include "Xenos/Renderer/Buffer.h"


namespace Xenos
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)= 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& vertexBuffer)= 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();

	};
}


