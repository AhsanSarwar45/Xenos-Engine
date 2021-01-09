#pragma once
#include <Xenos.h>
#include "ParticleSystem.h"

class Sandbox2D : public Xenos::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Xenos::TimeStep timeStep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Xenos::Event& event) override;
private:

	Xenos::Ref<Xenos::Shader> m_Shader;
	Xenos::Ref<Xenos::VertexArray> m_VertexArray;
	Xenos::Ref<Xenos::Texture2D> m_Texture;
	Xenos::Ref<Xenos::Texture2D> m_SpriteSheet;
	Xenos::Ref<Xenos::SubTexture2D> m_GrassTexture;
	Xenos::Ref<Xenos::SubTexture2D> m_BushTexture;
	Xenos::Ref<Xenos::FrameBuffer> m_FrameBuffer;
	Xenos::OrthographicCameraController m_CameraController;

	glm::vec3 m_Color = { 1.0f, 0.0f, 0.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};
