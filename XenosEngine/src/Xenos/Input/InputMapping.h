#pragma once
#include <unordered_map>
#include <bitset>
#include "Xenos/Input/KeyCodes.h"
namespace Xenos
{
	

	enum class Context
	{
		None = -1,
		File,
		Viewport
	};

	enum class Action
	{
		None = -1,

		SaveAsScene,
		OpenScene,
		NewScene,

		Select,
		Translate,
		Rotate,
		Scale

	};
	//1: Shift, 2:Ctrl, 3:Alt
	struct KeyAction
	{
		KeyCode keyCode;
		bool shift;
		bool ctrl;
		bool alt;
	};


	struct InputMapping
	{
		std::unordered_map <Action, KeyAction> actionMap;
	};

	using ContextMap = std::unordered_map<Context, InputMapping>;

	std::string_view GetActionString(Action action);
	std::string_view GetContextString(Context context);
}