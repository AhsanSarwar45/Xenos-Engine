#include "xenospch.h"
#include "PreferenceSerializer.h"
#include <fstream>
#include <yaml-cpp/yaml.h>

namespace Xenos
{
	std::unordered_map<std::string, InputMapping> PreferenceSerializer::ContextMap = {};
	std::string PreferenceSerializer::FilePath = "assets/preferences/keymapping/Test.prefs";
	void PreferenceSerializer::SerializeInputMapping(const std::unordered_map<std::string, InputMapping>& contextMap)
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Contexts" << YAML::Value << YAML::BeginSeq;

		for (auto& it : contextMap) {
			// Do stuff
			out << YAML::BeginMap;
			out << YAML::Key << "Context" << YAML::Value << it.first;
			out << YAML::Key << "Actions" << YAML::Value << YAML::BeginSeq;

			for (auto& actions : it.second.actionMap)
			{
				out << YAML::BeginMap;
				out << YAML::Key << "Action" << YAML::Value << actions.first;
				out << YAML::Key << "Key" << YAML::Value << actions.second.first;
				out << YAML::Key << "Modifiers";
				out << YAML::BeginMap;
				out << YAML::Key << "Shift" << YAML::Value << actions.second.second[2];
				out << YAML::Key << "Ctrl" << YAML::Value << actions.second.second[1];
				out << YAML::Key << "Alt" << YAML::Value << actions.second.second[0];
				out << YAML::EndMap;

				out << YAML::EndMap;
			}
			out << YAML::EndSeq;
			out << YAML::EndMap;
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(FilePath);
		fout << out.c_str();
			
	}
	void PreferenceSerializer::SerializeInputMapping()
	{
		SerializeInputMapping(ContextMap);
	}
	void PreferenceSerializer::DeserializeInputMapping()
	{
		YAML::Node data = YAML::LoadFile(FilePath);

		auto contexts = data["Contexts"];
		if (contexts)
		{
			for (auto context : contexts)
			{
				std::string name = context["Context"].as<std::string>();
				InputMapping inputMapping;
				auto actions = context["Actions"];
				for (auto action : actions)
				{
					std::string name = action["Action"].as<std::string>();
					
					Modifiers mods;
					auto modifiers = action["Modifiers"];
					mods[0] = modifiers["Alt"].as<bool>();
					mods[1] = modifiers["Ctrl"].as<bool>();
					mods[2] = modifiers["Shift"].as<bool>();
					KeyAction keyAction = { action["Key"].as<KeyCode>(), mods };

					inputMapping.actionMap.emplace(name, keyAction);
				}
				ContextMap.emplace(name, inputMapping);
			}
		}
	}
}

