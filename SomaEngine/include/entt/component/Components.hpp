#pragma once

#include "rendering/Texture.hpp"
#include "math/Vector.hpp"
#include "rendering/VertexArray.hpp"
#include "math/Transform.hpp"
#include "InputControl.hpp"
#include "rendering/model.hpp"

struct MeshComponent {
    Model* model = nullptr;
};

struct TransformComponent {
    Transform transform;
};