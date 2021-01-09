#pragma once
#include <Xenos.h>
#include "Panels/SceneHeiracrchyPanel.h"
#include "Panels/InspectorPanel.h"
#include "Panels/PreferencesPanel.h"
#include "Xenos/Renderer/EditorCamera.h"
//#include "ParticleSystem.h"

namespace Xenos
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(TimeStep timeStep) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& event) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		void ApplyAction(Action action);
		void CheckShorcut(const InputMapping& map, KeyCode key, bool alt, bool control, bool shift);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:

		Ref<Shader> m_Shader;
		Ref<VertexArray> m_VertexArray;
		Ref<Texture2D> m_Texture;
		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Texture2D> m_SpriteSheet;

		Ref<Scene> m_ActiveScene;
		Entity m_CameraEntity;
	//	OrthographicCameraController m_CameraController;
		Ref<EditorCamera> m_EditorCamera;

		glm::vec3 m_Color = { 1.0f, 0.0f, 0.0f };

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		bool m_PreferenceWindowOpened = false;
		SceneHierarchyPanel m_SceneHierarchyPanel;
		InspectorPanel m_InspectorPanel;
		PreferencesPanel m_PreferencesWindow;
		
		Ref<Entity> m_SelectedEntity;
		//InputMapping m_CurrentMapping;

		int m_GizmoType= -1;
		//ParticleSystem m_ParticleSystem;
		//ParticleProps m_Particle;
	};
}

