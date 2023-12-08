#include "pch.h"
#include "Renderer.h"

namespace Engine {

    //RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;
    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}