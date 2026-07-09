#pragma once

namespace Penguin
{
    class IndexBuffer
    {
        private:
            unsigned m_RendererID;
            unsigned int m_Count;
        public:
            IndexBuffer(const unsigned int* data, unsigned int count);
            ~IndexBuffer();
            unsigned int GetCount() const;

            void Bind() const;
            void Unbind() const;

    };
}