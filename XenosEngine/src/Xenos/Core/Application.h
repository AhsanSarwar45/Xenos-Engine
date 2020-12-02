#pragma once
#include "Core.h"
#include "LayerStack.h"
#include "Xenos/Events/Events.h"
#include "Xenos/Events/ApplicationEvent.h"
#include "Window.h"
#include "Xenos/Core/TimeStep.h"

#include "Xenos/ImGUI/ImGuiLayer.h"

namespace Xenos
{
	class Application
	{
	public :
		Application(const std::string& name);
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void CloseEditor();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		 
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		float m_LastFrameTime = 0.0f;
	};

	//To be defined in client
	Application* CreateApplication();
}