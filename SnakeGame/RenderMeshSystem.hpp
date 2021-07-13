#pragma once

#include <entt/entt.hpp>
#include <entt/SystemsManager.hpp>
#include <math/Vector.hpp>
#include <entt/component/Components.hpp>
#include <GameRenderContext.hpp>
class RenderMeshSystem : public System<RenderMeshSystem> {
public:
    RenderMeshSystem(GameRenderContext& contextIn) : context(contextIn) {}
    ~RenderMeshSystem() {};
    virtual void Configure() {};
    virtual void Update(entt::registry& registry, entt::dispatcher& eventDispatcher, float dt)
    {
        auto v = registry.view<TransformComponent, MeshComponent>();
        for (auto entity : v) {
            auto& mesh = v.get<MeshComponent>(entity);
            auto& transform = v.get<TransformComponent>(entity);

            context.renderMesh(mesh.model, transform.transform.toMatrix());
        }
    }
    virtual void Render(entt::registry& registry) {};

private:
    GameRenderContext& context;

};