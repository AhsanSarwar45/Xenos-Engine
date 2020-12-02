#include "KeyBindingsWindow.h"
#include "Xenos/Utility/PreferenceSerializer.h"
#include "Xenos/Input/KeyCodes.h"
#include <imgui/imgui_internal.h>

namespace Xenos
{
	void KeyBindingsWindow::Initialize()
	{
		PreferenceSerializer::DeserializeInputMapping();
   
	}
	void KeyBindingsWindow::ShowWindow()
	{
		ImGui::Begin("Preferences");
        if (PreferenceSerializer::ContextMap.empty())return;
        for (auto& context : PreferenceSerializer::ContextMap)
        {        
            if (ImGui::TreeNode(context.first.c_str()))
            {
                ImGui::Columns(2);
                ImGui::SetColumnWidth(0, 200);

                for (auto& action : context.second.actionMap)
                {             
                    ImGui::Text(action.first.c_str());
                    ImGui::NextColumn();

                    std::string binding = "";
                    if (action.second.second[1]) binding += "Ctrl + ";
                    if (action.second.second[2]) binding += "Shift + ";
                    if (action.second.second[0]) binding += "Alt + ";
                    binding += GetKeyCodeString((Key::KeyCode)action.second.first);

                    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
                    ImVec2 buttonSize = { 200, lineHeight };

                    ImVec4 normalColor(0.4f, 0.4f, 0.4f, 1.0f);

                    ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f });
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, normalColor);

                    if (ImGui::Button(binding.c_str(), buttonSize));
                    ImGui::PopStyleColor(3);
          
                    ImGui::NextColumn();
                }
                ImGui::Columns(1);
                ImGui::TreePop();
            }         
        }
        ImGui::End();
	}
}