#pragma once
#include <unordered_map>
#include <bitset>
#include "Xenos/Input/KeyCodes.h"
namespace Xenos
{
	//1: Shift, 2:Ctrl, 3:Alt
	using Modifiers = std::bitset<3>;
	using KeyAction = std::pair<KeyCode, Modifiers> ;

	struct InputMapping
	{
		std::unordered_map <std::string, KeyAction> actionMap;
	};
}