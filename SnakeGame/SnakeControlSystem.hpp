#pragma once
#include <entt/entt.hpp>
#include <entt/SystemsManager.hpp>
#include <entt/component/Components.hpp>

#include "SnakeComponents.hpp"
#include "LerpComponent.h"

class SnakeControlSystem : public System<SnakeControlSystem>
{
public:
    SnakeControlSystem() {}
    ~SnakeControlSystem() {};
    virtual void Configure() {};
    virtual void Update(entt::registry& registry, entt::dispatcher& eventDispatcher, float dt) override
    {
        auto v = registry.view<SnakeBodyComponent, MovementControlComponent>();

        for (auto entity : v) {
            auto& snakeBody = v.get<SnakeBodyComponent>(entity);
            auto& controls = v.get<MovementControlComponent>(entity);

           if (controls.horizontal->GetAmt() > 0)
               snakeBody.direction = DIRECTION::RIGHT;
           else if (controls.horizontal->GetAmt() < 0)
               snakeBody.direction = DIRECTION::LEFT;
           else if (controls.vertical->GetAmt() > 0)
               snakeBody.direction = DIRECTION::UP;
           else if (controls.vertical->GetAmt() < 0)
               snakeBody.direction = DIRECTION::DOWN;

        }
    }
    virtual void Render(entt::registry& registry) {};
private:

};