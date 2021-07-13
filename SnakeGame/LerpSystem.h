#pragma once
#include <entt/entt.hpp>
#include <entt/SystemsManager.hpp>
#include <math/Vector.hpp>
#include <entt/component/Components.hpp>
#include <GameRenderContext.hpp>
#include "LerpComponent.h"
class LerpSystem : public System<LerpSystem> {
public:
    LerpSystem() {}
    ~LerpSystem() {};
    virtual void Configure() {};
    virtual void Update(entt::registry& registry, entt::dispatcher& eventDispatcher, float dt)
    {
        auto v = registry.view<TransformComponent, LerpComponent>();

        for (auto entity : v) {
            auto& transform = v.get<TransformComponent>(entity);
            auto& lerp = v.get<LerpComponent>(entity);

            if (lerp.timeElapsed < lerpDuration)
            {
                Vector3f newPosition = Math::lerp(lerp.start, lerp.destination, lerp.timeElapsed/lerpDuration);
                transform.transform.setTranslation(newPosition);
                lerp.timeElapsed += dt* lerpScale;
            }
            else {
                transform.transform.setTranslation(lerp.destination);
            }
        }
    }
    virtual void Render(entt::registry& registry) {};

private:
    uint32 lerpDuration = 1.0f;
    uint32 lerpScale = 4.0f;
};