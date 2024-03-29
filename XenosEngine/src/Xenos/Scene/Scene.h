#pragma once
#include "entt.hpp"
#include "Xenos/Core/TimeStep.h"
#include "Xenos/Renderer/EditorCamera.h"

namespace Xenos
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateCamera(const std::string& name = std::string());
		Entity CreateSprite(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		Entity GetPrimaryCameraEntity();

		void OnViewportResize(uint32_t width, uint32_t height);

		void OnUpdateRuntime(TimeStep timeStep);
		void OnUpdateEditor(TimeStep timeStep, EditorCamera& camera);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		 
		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class SceneSerializer;
	};


}


