#include "gfx/gfx.h"
#include "renderer.h"

namespace Penguin
{
    void Renderer::Clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::Render(const Mesh& mesh, const Shader& shader) const
    {
        shader.Bind();
        mesh.Bind();
        glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
    }
}