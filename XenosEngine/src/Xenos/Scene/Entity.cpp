#include "xenospch.h"
#include "Entity.h"

namespace Xenos
{
	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene)
	{
	}
}