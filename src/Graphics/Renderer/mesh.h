#pragma once
#include "IBO.h"
#include "VBO.h"
#include "VAO.h"
#include "vertex.h"
#include <vector>

namespace Penguin
{
    class Mesh
    {
        private:
            VertexArray m_VAO;
            VertexBuffer m_VBO;
            IndexBuffer m_IBO;
        public:

            Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

            void Bind() const;
            unsigned int GetIndexCount() const;
        
        
            
    };
}