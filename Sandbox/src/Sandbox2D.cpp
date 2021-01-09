#include "Sandbox2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <chrono>


Sandbox2D::Sandbox2D()
	:Layer("Sandbox 2D"), m_CameraController(1280.0f / 720.0f)
{


}

void Sandbox2D::OnAttach()
{
	XS_PROFILE_FUNCTION();
	m_Texture = Xenos::Texture2D::Create("assets/textures/test.png");
	m_SpriteSheet = Xenos::Texture2D::Create("assets/textures/spritesheet.png");
	m_GrassTexture = Xenos::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 11 }, { 128, 128 }, {1,2});

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

}

void Sandbox2D::OnDetach()
{
	XS_PROFILE_FUNCTION(); 
}

void Sandbox2D::OnUpdate(Xenos::TimeStep timeStep)
{
	XS_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(timeStep);

	Xenos::Renderer2D::ResetStats();
	Xenos::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Xenos::RenderCommand::Clear();

	Xenos::Renderer2D::BeginScene(m_CameraController.GetCamera());

	/*for (float y = -5.0f; y < 5.0f; y += 1.0f)
	{
		for (float x = -5.0f; x < 5.0f; x += 1.0f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f , (y + 5.0f) / 10.0f, 0.4f,  1.0f };
			Xenos::Renderer2D::DrawQuad({ x, y , 0.0f }, { 0.8f, 0.8f }, glm::vec4{ 1.0f });
		}
	}
	Xenos::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.2f, 1.0f });
	Xenos::Renderer2D::DrawQuad({ 2.0f, 1.5f }, { 2.0f, 1.0f }, { 0.2f, 0.8f, 0.2f, 1.0f });
	Xenos::Renderer2D::DrawQuad({ 2.0f, 3.0f,1.0f }, { 0.8f, 0.8f }, m_Texture);
	Xenos::Renderer2D::DrawQuad({ 0.0f, 2.0f }, { 0.8f, 0.8f }, m_Texture, 5);
	Xenos::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(45.0f), m_Texture, 2);*/
	Xenos::Renderer2D::DrawQuad({ 0.0f, 0.0f,0.0f }, {1.0f,2.0f }, m_GrassTexture);

	Xenos::Renderer2D::EndScene();

	if (Xenos::Input::IsMouseButtonPressed(XS_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Xenos::Input::GetMousePosition();
		auto width = Xenos::Application::Get().GetWindow().GetWidth();
		auto height = Xenos::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(timeStep);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

}


void Sandbox2D::OnImGuiRender()
{
	XS_PROFILE_FUNCTION();

	auto stats = Xenos::Renderer2D::GetStats();

	ImGui::Begin("Debug");
	ImGui::Text("Renderer Stats");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetVertexCount());
	ImGui::Text("Indices: %d", stats.GetIndexCount());

	ImGui::End();

}

void Sandbox2D::OnEvent(Xenos::Event& event)
{
	m_CameraController.OnEvent(event);
}
