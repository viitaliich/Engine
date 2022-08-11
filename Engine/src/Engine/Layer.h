#pragma once

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace Engine {

	class ENGINE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");	// debug name of the layer
		virtual ~Layer();	// virtual destructor -> it's going to be subclassed

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}