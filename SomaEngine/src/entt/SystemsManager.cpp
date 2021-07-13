#include "somapch.hpp"
#include "entt/SystemsManager.hpp"

BaseSystem::Family BaseSystem::family_counter_;

void SystemsManager::UpdateAll(entt::registry& registry, entt::dispatcher& eventDispatcher, float dt)
{
	if (!m_initialized)
	{
		DEBUG_LOG("SystemsManager.cpp", "ERROR", "Failed to initialize SystemsManager");
		return;
	}
	for (auto& pair : m_systems) {
		pair.second->Update(registry, eventDispatcher, dt);
	}
}
void SystemsManager::Configure()
{
	for (auto& pair : m_systems) {
		pair.second->Configure();
	}
	m_initialized = true;
}