#pragma once

#include <memory>
#include "Engine/Renderer/Buffer.h"

namespace Engine {

    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        // These are good for testing, but not really needed for engine ???
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        // shared pointer because every resource must be reference counted ???
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

        static VertexArray* Create();
    };

}