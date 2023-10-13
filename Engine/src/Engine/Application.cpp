#include "pch.h"

#include "Application.h"

#include <glad/glad.h>

#include "Input.h"		// ??? do we need it here?

namespace Engine {

    // Why static and why it's here, not in Buffer.h?   ???
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

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		EG_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(EG_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

        // ??? watch OpenGL series (vertex array vs vertex buffer)
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        // ??? watch OpenGL series

        // clock counter-wise
        float vertices[3 * 7] = {       // ??? color at vertex
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        // STATIC_DRAW - we won't update data in further frame
        // ARRAY_BUFFER == vertex buffer
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float4, "a_Color" }
            };

            // Vertex attributes are stored in Vertex Array and describe data in a Vertex Buffer.
            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = m_VertexBuffer->GetLayout();
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

        uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        // location 0 coresponds to glEnableVertexAttribArray(0);
        // variables passed between shaders are called varying, so v_ in name
        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
            
            out vec3 v_Position;
			out vec4 v_Color;

            void main()
			{
				v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
            in vec3 v_Position;
			in vec4 v_Color;
            
            void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
			}
		)";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	void Application::Run() {
		
		while (m_Running)
		{
            glClearColor(0.1f, 0.1f, 0.1f, 1);		// set color buffer will be cleared with
			glClear(GL_COLOR_BUFFER_BIT);	// clears set buffer
			
            m_Shader->Bind(); 
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(EG_BIND_EVENT_FN(Application::OnWindowClose));

		// go backwards through the layer stack
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
