#include <Xenos.h>
#include "../UI Utilities/UIUtils.h"
#include "PreferencesPanel.h"
#include "Xenos/Utility/PreferenceSerializer.h"
#include "Xenos/Input/KeyCodes.h"
#include "imgui/imgui.h"
#include <imgui/imgui_internal.h>


namespace Xenos
{

    bool PreferencesPanel::IsWaitingForInput() const
    {
        return m_Changing;
    }
    void PreferencesPanel::SetBind(KeyCode key, bool shift, bool alt, bool ctrl)
    {
        PreferenceSerializer::s_ContextMap[m_Context].actionMap[m_Action].keyCode = key;
        PreferenceSerializer::s_ContextMap[m_Context].actionMap[m_Action].alt = alt;
        PreferenceSerializer::s_ContextMap[m_Context].actionMap[m_Action].shift = shift;
        PreferenceSerializer::s_ContextMap[m_Context].actionMap[m_Action].ctrl = ctrl;

        PreferenceSerializer::SerializeInputMapping();

        m_Changing = false;
    }
    bool PreferencesPanel::IsFocused() const
    {
        return m_IsFocused;
    }
    bool PreferencesPanel::IsHovered() const
    {
        return m_IsHovered;
    }
   
    PreferencesPanel::PreferencesPanel(const Ref<EditorCamera>& camera)
    {
        m_EditorCamera = camera;
    }

    void PreferencesPanel::ShowPanel()  
	{
		ImGui::Begin("Preferences");
        m_IsFocused = ImGui::IsWindowFocused();
        m_IsHovered = ImGui::IsWindowHovered();
        ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeight() - 6));
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("Input"))
            {
                ImGui::Dummy(ImVec2(0.0f, 10.0f));
                ImGui::DrawFloatControl("Viewport Rotation Speed", PreferenceSerializer::s_InputSettings.viewportRotationSpeed, 200.0f);
                ImGui::DrawFloatControl("Max Zoom Speed", PreferenceSerializer::s_InputSettings.maxZoomSpeed, 200.0f);
   
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Key Bindings"))
            {
                if (!PreferenceSerializer::s_ContextMap.empty())
                {
                    for (auto& context : PreferenceSerializer::s_ContextMap)
                    {
  
                        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
                        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
                        bool open = ImGui::TreeNodeEx(std::string(GetContextString((Context)context.first)).c_str(), treeNodeFlags);
                        ImGui::PopStyleVar();
                        if (open)
                        {
                            ImGui::Columns(2);
                            ImGui::SetColumnWidth(0, 200);

                            for (auto& action : context.second.actionMap)
                            {
                                ImGui::Text(std::string(GetActionString((Action)action.first)).c_str());
                                ImGui::NextColumn();

                                std::string binding = "";

                                if (m_Context == context.first && m_Action == action.first && m_Changing)
                                {
                                    binding = "Enter new binding...";

                                    if (Input::IsMouseButtonPressed(Mouse::Button0))
                                        m_Changing = false;

                                }
                                else
                                {
                                    if (action.second.ctrl) binding += "Ctrl + ";
                                    if (action.second.shift) binding += "Shift + ";
                                    if (action.second.alt) binding += "Alt + ";
                                    binding += GetKeyCodeString((Key::KeyCode)action.second.keyCode);
                                }


                                float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
                                ImVec2 buttonSize = { 200, lineHeight };

                                ImVec4 normalColor(0.4f, 0.4f, 0.4f, 1.0f);

                                ImGui::PushStyleColor(ImGuiCol_Button, normalColor);
                                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f });
                                ImGui::PushStyleColor(ImGuiCol_ButtonActive, normalColor);

                                if (ImGui::Button(binding.c_str(), buttonSize))
                                {
                                    m_Changing = !m_Changing;
                                    m_Context = context.first;
                                    m_Action = action.first;
                                }

                                ImGui::PopStyleColor(3);

                                ImGui::NextColumn();
                            }
                            ImGui::Columns(1);
                            ImGui::TreePop();
                        }
                    }
                }
               
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Cucumber"))
            {
                ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::EndChild();
        if (ImGui::Button(ICON_FK_BARS, ImVec2(22, 22)))
        {

        }
        ImGui::SameLine(32, 5);
        if(ImGui::Button("Save Preferences"))
        {
            PreferenceSerializer::SerializeInputSettings();
            m_EditorCamera->UpdateSettings();
        }
       
        ImGui::End();
	}

}