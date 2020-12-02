#pragma once
#include "Xenos/Input/Input.h"
#include "Xenos/Input/InputMapping.h"
#include <unordered_map>

namespace Xenos
{
	class PreferenceSerializer
	{
	public:
		static void SerializeInputMapping();
		static void SerializeInputMapping(const std::unordered_map<std::string, InputMapping>& contextMap);
		static void DeserializeInputMapping();
		static std::unordered_map<std::string, InputMapping> ContextMap;
		static std::string FilePath;
	};

}

