#include <Xenos.h>
/*-----------ENTRY POINT--------------*/
#include "Xenos/Core/EntryPoint.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"


//class TestLayer : public Xenos::Layer
//{
//public:
//	TestLayer()
//		:Layer("Example"), m_CameraController(1280.0f/720.0f)
//	{
//
//		m_VertexArray = Xenos::VertexArray::Create();
//
//		float vertices[4 * 5] =
//		{
//			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
//			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
//			0.5f, 0.5f, 0.0f,  1.0f, 1.0f,
//			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
//			
//		};
//
//		Xenos::Ref<Xenos::VertexBuffer> vertexBuffer;
//		vertexBuffer.reset(Xenos::VertexBuffer::Create(vertices, sizeof(vertices)));
//
//		Xenos::BufferLayout layout =
//		{
//			{Xenos::ShaderDataType::Float3, "a_Position"},
//			{Xenos::ShaderDataType::Float2, "a_TexCoord"}
//		};
//
//		vertexBuffer->SetLayout(layout);
//
//		m_VertexArray->AddVertexBuffer(vertexBuffer);
//
//		uint32_t indices[6] = { 0, 1, 2,2,3,0 };
//
//		Xenos::Ref<Xenos::IndexBuffer> indexBuffer;
//		indexBuffer.reset(Xenos::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
//		m_VertexArray->SetIndexBuffer(indexBuffer); 
//
//		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
//	
//		m_Texture = Xenos::Texture2D::Create("assets/textures/test.png");
//
//		std::dynamic_pointer_cast<Xenos::OpenGLShader>(textureShader)->Bind();
//		std::dynamic_pointer_cast<Xenos::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
//	}
//
//	void OnUpdate(Xenos::TimeStep timeStep) override
//	{
//		m_CameraController.OnUpdate(timeStep);
//		Xenos::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
//		Xenos::RenderCommand::Clear();
//
//		Xenos::Renderer::BeginScene(m_CameraController.GetCamera());
//
//		auto textureShader = m_ShaderLibrary.Get("Texture");
//		m_Texture->Bind();
//		Xenos::Renderer::Submit(m_VertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
//		
//		Xenos::Renderer::EndScene();
//
//	}
//
//	virtual void OnImGuiRender() override
//	{
//	}
//
//	void OnEvent(Xenos::Event& event) override
//	{
//		m_CameraController.OnEvent(event);
//	}
//private:
//	Xenos::ShaderLibrary m_ShaderLibrary;
//
//	Xenos::Ref<Xenos::VertexArray> m_VertexArray;
//
//	Xenos::Ref<Xenos::Texture2D> m_Texture;
//
//	Xenos::OrthographicCameraController m_CameraController;
//
//	glm::vec3 m_Color = { 1.0f, 0.0f, 0.0f };
//};

class Sandbox : public Xenos::Application
{
public:
	Sandbox()
		:Application ("Sandbox")
	{
		//PushLayer(new TestLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Xenos::Application* Xenos::CreateApplication()
{
	return new Sandbox();
}
