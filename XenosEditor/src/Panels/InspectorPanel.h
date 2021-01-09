#pragma once
#include "Panel.h"
#include <Xenos.h>
namespace Xenos
{
	class InspectorPanel : Panel
	{
	public:
		InspectorPanel() = default;
		InspectorPanel(Ref<Entity> selectedEntity);
		virtual void ShowPanel() override;
	private:
		void DrawInspector(Entity entity);
		Ref<Entity> m_SelectedEntity;

	};
}


