#pragma once
#include <vector>
#include "gfx/gfx.h"

namespace Penguin
{
    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int GetSizeOfType(unsigned int type)
        {
            switch (type)
            {
                case GL_FLOAT:         return 4;
                case GL_UNSIGNED_INT:  return 4;
                case GL_UNSIGNED_BYTE: return 1;
            }
            return 0;
        }
    };

    class VertexBufferLayout
     {
        private:
            std::vector<VertexBufferElement> m_Elements;
            unsigned int m_stride;
        public:
            VertexBufferLayout();
            void PushFloat(unsigned int count);

            const std::vector<VertexBufferElement>& GetElements() const;
            inline unsigned int GetStride() const { return m_stride;}
     };
}
