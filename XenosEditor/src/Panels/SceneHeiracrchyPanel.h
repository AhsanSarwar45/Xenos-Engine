#pragma once
#include <Xenos.h>
#include "Panel.h"

namespace Xenos
{
	class SceneHierarchyPanel : Panel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context, Ref<Entity> selectedEntity);
		void SetContext(const Ref<Scene>& context);
		Entity GetSelectedEntity() const;
		virtual void ShowPanel() override;
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Ref<Entity> m_SelectedEntity;
	};

}

