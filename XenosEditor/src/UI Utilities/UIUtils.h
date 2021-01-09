#pragma once
#include <string>
#include <imgui/imgui.h>
#include <glm/glm.hpp>

namespace ImGui
{
	void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
	void DrawFloatControl(const std::string& label, float& value, float columnWidth);
}

