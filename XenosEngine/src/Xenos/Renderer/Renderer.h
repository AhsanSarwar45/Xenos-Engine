#pragma once
#include <glm/glm.hpp>
#include "RenderCommand.h"
#include "Shader.h"
#include "Camera.h"


namespace Xenos
{
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewPrjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
	
}