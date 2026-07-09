#pragma once
#include "gfx/gfx.h"
#include "mesh.h"
#include "shader.h"

namespace Penguin
{
    class Renderer
    {
        public:
            void Clear() const;
            void Render(const Mesh& mesh, const Shader& shader) const;

    };
}