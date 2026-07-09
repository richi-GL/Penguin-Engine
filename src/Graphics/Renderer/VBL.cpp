#include <vector>
#include "gfx/gfx.h"
#include "VBL.h"

namespace Penguin
{
    VertexBufferLayout::VertexBufferLayout() : m_stride(0)
    {

    }
    
    void VertexBufferLayout::PushFloat(unsigned int count)
    {
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
    {
        return m_Elements;
    }

}