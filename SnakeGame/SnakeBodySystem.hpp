#pragma once
#include <entt/entt.hpp>
#include <entt/SystemsManager.hpp>
#include <entt/component/Components.hpp>

#include "SnakeComponents.hpp"
#include "LerpComponent.h"

class SnakeBodySystem : public System<SnakeBodySystem>
{
public:
    SnakeBodySystem() {}
    ~SnakeBodySystem() {};
    virtual void Configure() {};
    virtual void Update(entt::registry& registry, entt::dispatcher& eventDispatcher, float dt) override
    {
        auto v = registry.view<TransformComponent, LerpComponent, SnakeBodyComponent>();

        for (auto entity : v) {
            auto& transform = v.get<TransformComponent>(entity);
            auto& lerp = v.get<LerpComponent>(entity);
            auto& snakeBody = v.get<SnakeBodyComponent>(entity);

            //Check Distance
            float distance = transform.transform.getTranslation().dist(lerp.destination);
            if (distance <= 0.0f)
            {
                //Snake Head
                if (snakeBody.nextSnakeBody == entt::null){
                    if(snakeBody.direction == DIRECTION::RIGHT)
                        lerp.destination.set(lerp.destination[0] + 2.0f, lerp.destination[1], lerp.destination[2]);
                    else if (snakeBody.direction == DIRECTION::UP)
                        lerp.destination.set(lerp.destination[0], lerp.destination[1] + 2.0f, lerp.destination[2]);
                    else if (snakeBody.direction == DIRECTION::DOWN)
                        lerp.destination.set(lerp.destination[0], lerp.destination[1] - 2.0f, lerp.destination[2]);
                    else if (snakeBody.direction == DIRECTION::LEFT)
                        lerp.destination.set(lerp.destination[0] - 2.0f, lerp.destination[1], lerp.destination[2]);

                    lerp.start = transform.transform.getTranslation();
                    lerp.timeElapsed = 0;
                }
                //Snake Body
                else {
                    auto& t =  registry.get<TransformComponent>(snakeBody.nextSnakeBody);
                    lerp.destination = t.transform.getTranslation();
                    lerp.start = transform.transform.getTranslation();
                    lerp.timeElapsed = 0;
                }
                //DEBUG_LOG("SnakeBodyStstem", "DEBUG", "Hit Destination");
            }
        }
    }
    virtual void Render(entt::registry& registry) {};
private:

};