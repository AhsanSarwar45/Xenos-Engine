#pragma once
#include "Panel.h"
#include <Xenos.h>
#include <unordered_map>

namespace Xenos
{
	class PreferencesPanel : Panel
	{
	public:
		PreferencesPanel() = default;
		PreferencesPanel(const Ref<EditorCamera>& camera);
		virtual void ShowPanel() override;
		bool IsWaitingForInput() const;
		void SetBind(KeyCode key, bool shift, bool alt, bool ctrl);
		bool IsFocused() const;
		bool IsHovered() const;
	private:
		bool m_Changing;
		Context m_Context;
		Action m_Action;
		Ref<EditorCamera> m_EditorCamera;
	};
}


