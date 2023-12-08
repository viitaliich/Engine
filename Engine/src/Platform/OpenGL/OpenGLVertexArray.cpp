#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Engine {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case Engine::ShaderDataType::Float:    return GL_FLOAT;
        case Engine::ShaderDataType::Float2:   return GL_FLOAT;
        case Engine::ShaderDataType::Float3:   return GL_FLOAT;
        case Engine::ShaderDataType::Float4:   return GL_FLOAT;
        case Engine::ShaderDataType::Mat3:     return GL_FLOAT;
        case Engine::ShaderDataType::Mat4:     return GL_FLOAT;
        case Engine::ShaderDataType::Int:      return GL_INT;
        case Engine::ShaderDataType::Int2:     return GL_INT;
        case Engine::ShaderDataType::Int3:     return GL_INT;
        case Engine::ShaderDataType::Int4:     return GL_INT;
        case Engine::ShaderDataType::Bool:     return GL_BOOL;
        }

        EG_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        // ??? what is the difference between glGenVertexArrays and glCreateVertexArrays
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        EG_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);        // ??? why this is not in Create method?
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            // ??? OpenGL series
            // Specify buffer layout.
            // Is directly tied to shader.
            glEnableVertexAttribArray(index);
            // In Vertex buffer at index 0 we have 3 floats, that are not normalized; 
            // the stride is 3 * sizeof(float) and offset of this particular element is nothing.
            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); 
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);       // why void, not int ???
            index++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }

    // ??? why SetIndexBuffer, not AddIndexBuffer
    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);        // ??? why this is not in Create method?
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }

}