#include "xenospch.h"
#include "Scene.h"
#include "Xenos/Scene/Components.h"
#include "Xenos/Scene/Entity.h"
#include "Xenos/Renderer/Renderer2D.h"
#include <glm/glm.hpp>

namespace Xenos
{
    Scene::Scene()
    {
        
       
    }
    Scene::~Scene()
    {
    }
    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity e = { m_Registry.create(), this };;
        e.AddComponent<TransformComponent>();
        auto& tag = e.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Entity" : name;
        return e;
    }
	Entity Scene::CreateCamera(const std::string& name)
	{
		Entity e = CreateEntity(name);
		auto& cameraComponent = e.AddComponent<CameraComponent>();
		if (!cameraComponent.FixedAspectRatio)
			cameraComponent.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
		return e;
	}
	Entity Scene::CreateSprite(const std::string& name)
	{
		Entity e = CreateEntity(name);
		e.AddComponent<SpriteRendererComponent>();
		return e;
	}
	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}
    void Scene::OnUpdate(TimeStep timeStep)
    {
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					// TODO: Move to Scene::OnScenePlay
					if (!nsc.Instance)
					{
						nsc.Instance = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.Instance->OnCreate();
					}

					nsc.Instance->OnUpdate(timeStep);
				});
		}

		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			auto group = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : group)
			{
				auto [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			}

			Renderer2D::EndScene();
		}
    }
}