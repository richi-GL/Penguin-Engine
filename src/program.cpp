#include "window/window.h"
#include "gfx.h"
#include "renderer.h"
#include <array>
#include <filesystem>

using namespace Penguin;

namespace
{
    std::string ResolveShaderPath(const std::string& filename)
    {
        std::filesystem::path current = std::filesystem::current_path();
        std::array<std::filesystem::path, 2> candidates = {
            current / "src" / "shader" / filename,
            current / filename
        };

        for (const auto& candidate : candidates)
        {
            if (std::filesystem::exists(candidate))
            {
                return candidate.string();
            }
        }

        std::filesystem::path exePath = std::filesystem::canonical("/proc/self/exe");
        std::filesystem::path root = exePath.parent_path();
        for (auto dir = root; dir != dir.parent_path(); dir = dir.parent_path())
        {
            for (const auto& candidate : std::array<std::filesystem::path, 2>{
                     dir / "src" / "shader" / filename,
                     dir / filename
                 })
            {
                if (std::filesystem::exists(candidate))
                {
                    return candidate.string();
                }
            }
        }

        return filename;
    }
}

int main()
{
    Window window;
    if (!window.createWindow(1200, 1000 , "Penguin Engine"))
    {
        return -1;
    }

    Penguin::Renderer renderer;
    Penguin::Shader shader(
        ResolveShaderPath("base_vs.glsl"),
        ResolveShaderPath("base_fs.glsl")
    );

    std::vector<Penguin::Vertex> vertices = {
        {  0.0f,  0.5f, 0.0f },
        { -0.5f, -0.5f, 0.0f }, 
        {  0.5f, -0.5f, 0.0f } 
    };
    std::vector<unsigned int> indices = { 0, 1, 2 };

    Penguin::Mesh Triangulo(vertices, indices);

    while (!window.shouldClose())
    {
        renderer.Clear(); 

    
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

        renderer.Render(Triangulo, shader); 


        window.swapBuffers(); 
        window.pollEvents();  
    }
    
    return 0;
}
