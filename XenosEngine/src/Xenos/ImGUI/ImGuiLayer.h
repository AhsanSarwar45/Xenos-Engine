#pragma once

#include "Xenos/Core/Layer.h"

#include "Xenos/Events/ApplicationEvent.h"
#include "Xenos/Events/KeyEvent.h"
#include "Xenos/Events/MouseEvent.h"



namespace Xenos {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void Begin(); //Begin ImGUI Rendering
		void End();

		void BlockEvent(bool block) { m_BlockEvents = block; }
	private:
		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}