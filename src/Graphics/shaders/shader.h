#pragma once
#include <iostream>
#include <unordered_map>

namespace Penguin
{
    class Shader
    {
        private:
            unsigned int m_RendererID;
            std::string m_filePath;
            std::unordered_map<std::string, int> m_UniformLocationCache;
        public:
            Shader(const std::string& vertexPath, const std::string& fragmentPath);
            ~Shader();

            void Bind() const;
            void Unbind() const;

            void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        
        private:
            unsigned int CompileShader(unsigned int type, const std::string& source);
            unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

            std::string ParseShader(const std::string& filepath); 
            int GetUniformLocation(const std::string& name);
    };
}