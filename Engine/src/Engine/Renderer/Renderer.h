#pragma once

#include "RenderCommand.h"

namespace Engine {

    /*enum class RendererAPI
    {
        None = 0, OpenGL = 1
    };*/

    class Renderer
    {
    public:
        /*inline static RendererAPI GetAPI() { return s_RendererAPI; }
    private:
        static RendererAPI s_RendererAPI;*/

        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    };
}