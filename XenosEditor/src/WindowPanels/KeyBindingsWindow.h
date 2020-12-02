#pragma once
#include <imgui/imgui.h>
#include "Xenos/Input/Input.h"
#include "Xenos/Input/InputMapping.h"
#include <unordered_map>

namespace Xenos
{
	class KeyBindingsWindow
	{
	public:
		static void Initialize();
		static void ShowWindow();
	};
}


