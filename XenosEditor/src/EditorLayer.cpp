#include "EditorLayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include "imgui/imgui_toolbar.h"
#include "ImGuizmo.h"
#include <unordered_map>
#include <chrono>
#include "Xenos/Utility/PlatformUtils.h"
#include "Xenos/Scene/SceneSerializer.h"
#include "Xenos/Utility/PreferenceSerializer.h"
#include "Xenos/Input/KeyCodes.h"
#include "Panels/SpriteEditorWindow.h"
#include "Xenos/Math/Math.h"


namespace Xenos
{
	EditorLayer::EditorLayer()
		:Layer("Sandbox 2D")
	{


	}

	void EditorLayer::OnAttach()
	{
		XS_PROFILE_FUNCTION();
		
		//m_SpriteSheet = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 11 }, { 128, 128 }, { 1,2 });
		m_SpriteSheet = Xenos::Texture2D::Create("assets/textures/spritesheet.png");
		/*m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
		m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
		m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
		m_Particle.LifeTime = 1.0f;
		m_Particle.Velocity = { 0.0f, 0.0f };
		m_Particle.VelocityVariation = { 3.0f, 1.0f };
		m_Particle.Position = { 0.0f, 0.0f };*/

		//InputSettings settings = { 2.3f };
		//PreferenceSerializer::SerializeInputSettings(settings);

		PreferenceSerializer::DeserializeInputMapping();
		PreferenceSerializer::DeserializeInputSettings();

		FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(fbSpec);

		m_ActiveScene = CreateRef <Scene>();

		m_EditorCamera = CreateRef<EditorCamera>(30.0f, 1.778f, 0.1f, 1000.0f);

		m_PreferencesWindow = PreferencesPanel(m_EditorCamera);

		Entity square = m_ActiveScene->CreateEntity();
		square.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
		m_CameraEntity.AddComponent<CameraComponent>();

		m_SelectedEntity = CreateRef<Entity>();

		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				//auto& transform = GetComponent<TransformComponent>().Transform;
				//transform[3][0] = rand() % 10 - 5.0f;
			}

			void OnDestroy()
			{
			}

			void OnUpdate(TimeStep ts)
			{
				auto& translation = GetComponent<TransformComponent>().Translation;

				float speed = 5.0f;

				if (Input::IsKeyPressed(Key::A))
					translation.x -= speed * ts;
				if (Input::IsKeyPressed(Key::D))
					translation.x += speed * ts;
				if (Input::IsKeyPressed(Key::W))
					translation.y += speed * ts;
				if (Input::IsKeyPressed(Key::S))
					translation.y -= speed * ts;
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		

		m_SceneHierarchyPanel = SceneHierarchyPanel(m_ActiveScene, m_SelectedEntity);		
		m_InspectorPanel = InspectorPanel(m_SelectedEntity);		
	}

	void EditorLayer::OnDetach()
	{
		XS_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Xenos::TimeStep timeStep)
	{
		XS_PROFILE_FUNCTION();

		if(m_ViewportHovered)
			m_EditorCamera->OnUpdate(timeStep);

		Renderer2D::ResetStats();
		m_FrameBuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();

		m_ActiveScene->OnUpdateEditor(timeStep, *m_EditorCamera);

		m_FrameBuffer->Unbind();
	}


	void EditorLayer::OnImGuiRender()
	{
		XS_PROFILE_FUNCTION();
		//ImGui::ShowDemoWindow();
		auto stats = Xenos::Renderer2D::GetStats();

		static bool dockSpaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));


		ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}


		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{

				if (ImGui::MenuItem("New Scene", "Ctrl+N")) NewScene();
				if (ImGui::MenuItem("Save As Scene", "Ctrl+Shift+S")) SaveSceneAs();
				if (ImGui::MenuItem("Open Scene", "Ctrl+O")) OpenScene();

				ImGui::Separator();
			

				if (ImGui::MenuItem("Exit")) Xenos::Application::Get().CloseEditor();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::BeginMenu("Add Entity"))
				{
					if (ImGui::MenuItem("Empty Entity")) m_ActiveScene->CreateEntity();
					if (ImGui::MenuItem("Camera"))m_ActiveScene->CreateCamera();;
					if (ImGui::MenuItem("Sprite"))m_ActiveScene->CreateSprite();;
					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Tools"))
			{
				if (ImGui::MenuItem("Preferences"))
				{
					m_PreferenceWindowOpened = true;
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}



		m_SceneHierarchyPanel.ShowPanel();
		m_InspectorPanel.ShowPanel();

		ImGui::Begin("Debug");
		ImGui::Text("Renderer Stats");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetVertexCount());
		ImGui::Text("Indices: %d", stats.GetIndexCount());
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });

		ImGui::Begin(ICON_FK_CAMERA" Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvent(false);
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*) & viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{			
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_EditorCamera->SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
		
		uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1, 0 });

		if (*m_SelectedEntity)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			const glm::mat4& cameraProjection = m_EditorCamera->GetProjection();
			glm::mat4 cameraView = m_EditorCamera->GetViewMatrix();


			auto& tc = m_SelectedEntity->GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = 0.5f;

			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE) snapValue = 45.0f;

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION )m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, (snap) ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}

		ImGui::End();

		ImGui::PopStyleVar();

		ImGui::End();

		if (m_PreferenceWindowOpened)
		{
			m_PreferencesWindow.ShowPanel();
		}

	//	//ImGui::SetNextWindowPos(ImVec2(0.0f, io.DisplaySize.y), 0, ImVec2(0.0f, 1.0f));
		ImGui::Begin("Info Bar");

		ImGui::End();

		//SpriteEditorWindow::ShowWindow(m_SpriteSheet);
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_EditorCamera->OnEvent(e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(XS_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
	}

	void EditorLayer::ApplyAction(Action action)
	{
		switch (action)
		{
		case Xenos::Action::SaveAsScene:  SaveSceneAs();
			break;
		case Xenos::Action::OpenScene: OpenScene();
			break;
		case Xenos::Action::NewScene: NewScene();
			break;
		case Xenos::Action::Select: m_GizmoType = -1;
			break;
		case Xenos::Action::Translate: m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		case Xenos::Action::Rotate:  m_GizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		case Xenos::Action::Scale: m_GizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		default:
			break;
		}
	}

	void EditorLayer::CheckShorcut(const InputMapping& map, KeyCode key, bool alt, bool control, bool shift)
	{

		for (std::pair<Action, KeyAction> action : map.actionMap)
		{
			if (key == action.second.keyCode
				&& alt == action.second.alt
				&& control == action.second.ctrl
				&& shift == action.second.shift
				)
			{
				ApplyAction(action.first);
			}
		}
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;
	
		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		bool alt = Input::IsKeyPressed(Key::LeftAlt) || Input::IsKeyPressed(Key::RightAlt);

		if ( m_PreferencesWindow.IsFocused() && m_PreferencesWindow.IsWaitingForInput()
			&& e.GetKeyCode() != Key::LeftControl && e.GetKeyCode() != Key::RightControl
			&& e.GetKeyCode() != Key::LeftShift && e.GetKeyCode() != Key::RightShift
			&& e.GetKeyCode() != Key::LeftAlt && e.GetKeyCode() != Key::RightAlt
			)
		{
			m_PreferencesWindow.SetBind(e.GetKeyCode(), shift, alt, control);
			return true;
		}

		CheckShorcut(PreferenceSerializer::s_ContextMap[Context::File], e.GetKeyCode(), alt, control, shift);

		if (m_ViewportHovered)
		{
			CheckShorcut(PreferenceSerializer::s_ContextMap[Context::Viewport], e.GetKeyCode(), alt, control, shift);
			return true;
		}
	
	}


	
	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OpenScene()
	{
		std::optional<std::string> filepath = FileDialogs::OpenFile("Xenos Scene (*.xenos)\0*.xenos\0");
		if (filepath)
		{
			m_ActiveScene = CreateRef<Scene>();
			
			
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);
			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(*filepath);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::optional<std::string> filepath = FileDialogs::SaveFile("Xenos Scene (*.xenos)\0*.xenos\0");
		if (filepath)
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(*filepath);
		}
	}
}


