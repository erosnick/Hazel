#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hazel
{
	class HAZEL_API Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDeatch() {};
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return debugName; }

	protected:

		std::string debugName;
	};
}

