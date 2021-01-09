#include "SceneHeiracrchyPanel.h"
#include "Xenos/Scene/Components.h"
#include <imgui/imgui.h>


#include <cstring>


namespace Xenos
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context, Ref<Entity> selectedEntity)
	{
		SetContext(context);
		m_SelectedEntity = selectedEntity;
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;

	}

	Entity SceneHierarchyPanel::GetSelectedEntity() const
	{
		return *m_SelectedEntity;
	}

	void SceneHierarchyPanel::ShowPanel()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 200.0f;

		ImGui::Begin(ICON_FK_LIST_ALT " Scene Hierarchy");

		m_Context->m_Registry.each([&](auto entityID)
			{
				Entity entity{ entityID , m_Context.get() };
				DrawEntityNode(entity);
			});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			*m_SelectedEntity = {};

		// Right-click on blank space
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity")) m_Context->CreateEntity("Empty Entity");
				
			if (ImGui::MenuItem("Create Camera")) m_Context->CreateCamera("Camera");

			if (ImGui::MenuItem("Create Sprite")) m_Context->CreateSprite("Sprite");
			ImGui::EndPopup();
		}

		ImGui::End();

		//style.WindowMinSize.x = 370.0f;

		
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((*m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			*m_SelectedEntity = entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (*m_SelectedEntity == entity)
				m_SelectedEntity = {};
		}
	}

	
	

}