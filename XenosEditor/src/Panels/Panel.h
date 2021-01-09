#pragma once

namespace Xenos
{
	class Panel
	{
	public:
		virtual ~Panel() = default;

		virtual void ShowPanel() = 0;
	protected:
		Panel() = default;

		bool m_IsHovered;
		bool m_IsFocused;
	};
}


