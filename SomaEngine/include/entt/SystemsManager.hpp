#pragma once
#include <unordered_map>
#include <core/common.hpp>
#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>
#include "NonCopyable.hpp"

	class SystemsManager;

	class SOMA_API BaseSystem : NonCopyable {
	public:
		typedef size_t Family;
		static Family family_counter_;
		virtual ~BaseSystem() {};

		virtual void Configure() = 0;
		virtual void Update(entt::registry& registry, entt::dispatcher& eventDispatcher, float dt) = 0;
		virtual void Render(entt::registry& registry) = 0;
	private:

	};

	template <typename Derived>
	class System : public BaseSystem {
	public:
		virtual ~System() {};

	private:
		friend class SystemsManager;

		static Family family()
		{
			static Family family = family_counter_++;
			return family;
		}

	};

	class SOMA_API SystemsManager : NonCopyable {

	public:
		SystemsManager() {};
		template <typename S>
		void Add(std::shared_ptr<S> system) {
			m_systems.insert(std::make_pair(S::family(), system));
		}

		template <typename S, typename ... Args>
		std::shared_ptr<S> Add(Args && ... args)
		{
			std::shared_ptr<S> s(new S(std::forward<Args>(args) ...));
			Add(s);
			return s;
		}
		template <typename S>
		std::shared_ptr<S> System() {
			auto it = m_systems.find(S::family());
			if (it == m_systems.end())
			{
				DEBUG_LOG("SystemsManager.hpp", "ERROR", "Failed to find System");
				return nullptr;
			}
			else
			{
				return it == m_systems.end()
					? std::shared_ptr<S>()
					: std::shared_ptr<S>(std::static_pointer_cast<S>(it->second));
			}
		}
		template <typename S>
		void Update(entt::registry& registry, entt::dispatcher& eventDispatcher, float dt) {
			if (!m_initialized)
			{
				DEBUG_LOG("SystemsManager.cpp", "ERROR", "Failed to initialize SystemsManager");
			}
			else {
				std::shared_ptr<S> s = System<S>();
				s->Update(registry, eventDispatcher, dt);
			}
		}

		void UpdateAll(entt::registry& registry, entt::dispatcher& eventDispatcher, float dt);

		void Configure();

	private:
		bool m_initialized = false;
		std::unordered_map<BaseSystem::Family, std::shared_ptr<BaseSystem>> m_systems;

	};