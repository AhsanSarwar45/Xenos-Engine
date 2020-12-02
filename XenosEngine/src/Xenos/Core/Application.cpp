#include "xenospch.h"

#include "Application.h"
#include "Xenos/Renderer/Renderer.h"
#include "GLFW/glfw3.h"
#include "Xenos/Input/Input.h"


namespace Xenos
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	

	Application::Application(const std::string& name = "Xenos Engine")
	{
		XS_PROFILE_FUNCTION();
		XS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;


		//Create a new Window. Application will have ownership of the windows
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProperties(name)));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(true);

		Renderer::Init();

		//Setup the ImGuiLayer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		XS_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		XS_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::CloseEditor()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& event)
	{
		XS_PROFILE_FUNCTION();
		//Create a new EventDispatcher with the recieved event
		EventDispatcher dispatcher(event);

		//If the recieved event is WindowCloseEvent, then OnWindowClose will be called
		//This is handled by the application only. Most other events are passed to the layers, 
		//so they can do whatever they see fit
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			//Decrement the iterator and call its OnEvent
			(*--it)->OnEvent(event);

			//If event is handled by the current layer, donot propagate it further
			if (event.Handled)
				break;
		}
	}

	void Application::Run()
	{
		XS_PROFILE_FUNCTION();
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			TimeStep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timeStep);

			}


			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
		

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		XS_PROFILE_FUNCTION();

		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
		return false;
	}
}