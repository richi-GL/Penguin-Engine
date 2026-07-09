#include "IBO.h"
#include "VBO.h"
#include "VAO.h"
#include "mesh.h"
#include <vector>

namespace Penguin
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
        : m_VBO(vertices.data(), vertices.size() * sizeof(Vertex)), 
          m_IBO(indices.data(), indices.size())
    {

        VertexBufferLayout layout;
        layout.PushFloat(3); 
        
        m_VAO.AddBuffer(m_VBO, layout);
    }

    void Mesh::Bind() const
    {
        m_VAO.Bind();
        m_IBO.Bind();
    }

    unsigned int Mesh::GetIndexCount() const
    {
        return m_IBO.GetCount();
    }
}