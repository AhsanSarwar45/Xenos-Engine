#include "MenuBar.h"
#include <imgui/imgui.h>

namespace Xenos
{
	/*void MenuBar::OnImGuiRender()
	{
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
	}*/
}