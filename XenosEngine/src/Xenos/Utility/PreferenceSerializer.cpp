#include "xenospch.h"
#include "PreferenceSerializer.h"
#include "Xenos/Renderer/EditorCamera.h"
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "magic_enum.hpp"

namespace Xenos
{
	ContextMap PreferenceSerializer::s_ContextMap = {};
	InputSettings PreferenceSerializer::s_InputSettings = {};
	std::string PreferenceSerializer::s_InputMappingFilePath = "assets/preferences/keymapping/Test.prefs";
	std::string PreferenceSerializer::s_InputSettingsFilePath = "assets/preferences/input settings/Test.prefs";

	void PreferenceSerializer::SerializeInputMapping(const ContextMap& contextMap)
	{
		XS_PROFILE_FUNCTION();
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Contexts" << YAML::Value << YAML::BeginSeq;

		for (const auto& it : contextMap) {
			// Do stuff
			out << YAML::BeginMap;
			out << YAML::Key << "Context" << YAML::Value << (int)it.first;
			out << YAML::Key << "Actions" << YAML::Value << YAML::BeginSeq;

			for (const auto& actions : it.second.actionMap)
			{
				out << YAML::BeginMap;
				out << YAML::Key << "Action" << YAML::Value << (int)actions.first;
				out << YAML::Key << "Key" << YAML::Value << actions.second.keyCode;
				out << YAML::Key << "Modifiers";
				out << YAML::BeginMap;
				out << YAML::Key << "Shift" << YAML::Value << actions.second.shift;
				out << YAML::Key << "Ctrl" << YAML::Value << actions.second.ctrl;
				out << YAML::Key << "Alt" << YAML::Value << actions.second.alt;
				out << YAML::EndMap;

				out << YAML::EndMap;
			}
			out << YAML::EndSeq;
			out << YAML::EndMap;
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(s_InputMappingFilePath);
		fout << out.c_str();
			
	}
	void PreferenceSerializer::SerializeInputMapping()
	{
		SerializeInputMapping(s_ContextMap);
	}
	void PreferenceSerializer::DeserializeInputMapping()
	{
		YAML::Node data = YAML::LoadFile(s_InputMappingFilePath);

		auto contexts = data["Contexts"];
		if (contexts)
		{
			for (const auto& context : contexts)
			{
				Context contextName = (Context)context["Context"].as<uint16_t>();
				InputMapping inputMapping;
				auto actions = context["Actions"];
				for (const auto& action : actions)
				{
					Action actionName = (Action)action["Action"].as<uint16_t>();
					
					KeyAction keyAction;
					auto modifiers = action["Modifiers"];
					keyAction.keyCode = action["Key"].as<KeyCode>();
					keyAction.alt = modifiers["Alt"].as<bool>();
					keyAction.ctrl = modifiers["Ctrl"].as<bool>();
					keyAction.shift = modifiers["Shift"].as<bool>();

					inputMapping.actionMap.emplace(actionName, keyAction);
				}
				s_ContextMap.emplace(contextName, inputMapping);
			}
		}
	}
	void PreferenceSerializer::SerializeInputSettings()
	{
		SerializeInputSettings(s_InputSettings);
	}
	void PreferenceSerializer::SerializeInputSettings(const InputSettings& inputSettings)
	{
		XS_PROFILE_FUNCTION();
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Viewport Rotation Speed" << YAML::Value << inputSettings.viewportRotationSpeed;
		out << YAML::Key << "Max Zoom Speed" << YAML::Value << inputSettings.maxZoomSpeed;
		out << YAML::EndMap;

		std::ofstream fout(s_InputSettingsFilePath);
		fout << out.c_str();
	}
	void PreferenceSerializer::DeserializeInputSettings()
	{
		YAML::Node data = YAML::LoadFile(s_InputSettingsFilePath);

		 if (data["Viewport Rotation Speed"])  s_InputSettings.viewportRotationSpeed = data["Viewport Rotation Speed"].as<float>();
		 if (data["Max Zoom Speed"])  s_InputSettings.maxZoomSpeed = data["Max Zoom Speed"].as<float>();
		
		 
	}
}

