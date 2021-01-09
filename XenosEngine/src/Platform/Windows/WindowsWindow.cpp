#include "xenospch.h"
#include "WindowsWindow.h"

#include "Xenos/Events/ApplicationEvent.h"
#include "Xenos/Events/KeyEvent.h"
#include "Xenos/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"


namespace Xenos {


	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		XS_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	//Initialize Windows (Current implementation: GLFW)
	void WindowsWindow::Init(const WindowProperties& properties)
	{
		XS_PROFILE_FUNCTION();
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		

		//XS_CORE_INFO("Creating window {0} ({1}, {2})", properties.Title, properties.Width, properties.Height);

		//Initialize GLFW
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			XS_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
	
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}

			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keyCode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keyCode);
				data.EventCallback(event);
			});
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		XS_PROFILE_FUNCTION();
		Init(properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		XS_PROFILE_FUNCTION();
		Shutdown();
	}

	Window* Window::Create(const WindowProperties& properties)
	{
		XS_PROFILE_FUNCTION();
		return new WindowsWindow(properties);
	}

	void WindowsWindow::Shutdown()
	{
		XS_PROFILE_FUNCTION();
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		XS_PROFILE_FUNCTION();
		//Process all pending events
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync (bool enabled)
	{
		XS_PROFILE_FUNCTION();
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);

		}

		m_Data.VSync = enabled;
	}
	
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}


}