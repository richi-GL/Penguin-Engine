#include "gfx/gfx.h"
#include "shader.h"
#include <fstream>
#include <sstream>

namespace Penguin
{
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : m_filePath(vertexPath + " " + fragmentPath), m_RendererID(0)
    {
        std::string vertexShaderSource = ParseShader(vertexPath);
        std::string fragmentShaderSource = ParseShader(fragmentPath);
        m_RendererID = CreateShader(vertexShaderSource, fragmentShaderSource);
    }
    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }
    
    unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // Error handling
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    std::string Shader::ParseShader(const std::string& filepath)
    {
        std::ifstream stream(filepath);

        if (!stream.is_open())
        {
            std::cout << "[Shader Error]: ¡No se pudo abrir el archivo en la ruta: " << filepath << "!" << std::endl;
            return "";
        }

        std::stringstream ss;
        std::string line;

        while (getline(stream, line))
        {
            ss << line << "\n";
        }

        return ss.str();
    }

    int Shader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        {
            return m_UniformLocationCache[name];
        }

        int location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location != -1)
        {
            m_UniformLocationCache[name] = location;
        }

        return location;
    }
}