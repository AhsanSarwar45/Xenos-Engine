#pragma once
#include "Xenos/Input/Input.h"
#include "Xenos/Input/InputMapping.h"
#include "Xenos/Input/InputSettings.h"
#include <unordered_map>

namespace Xenos
{
	class PreferenceSerializer
	{
	public:
		static void SerializeInputMapping();
		static void SerializeInputMapping(const ContextMap& contextMap);
		static void DeserializeInputMapping();
		static void SerializeInputSettings();
		static void SerializeInputSettings(const InputSettings& inputSettings);
		static void DeserializeInputSettings();
		static ContextMap s_ContextMap;
		static InputSettings s_InputSettings;
		static std::string s_InputMappingFilePath;
		static std::string s_InputSettingsFilePath;
	};

}

