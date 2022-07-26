#pragma once
#include "KaluoEngine/Core/Core.h"
#include "KaluoEngine/Core/TimeStep.h"
#include "KaluoEngine/Events/Event.h"

namespace KaluoEngine{

	//subclass layer class and construct an actual layer
	class KALUO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnImGuiRender() {};

		virtual void OnUpdate(TimeStep timestep) {}
		virtual void OnEvent(Event& event) {}


		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}


