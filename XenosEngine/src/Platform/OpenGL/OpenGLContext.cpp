#include "xenospch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Xenos
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		XS_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}
	void OpenGLContext::Init()
	{
		XS_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);

		//Initialize Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		XS_CORE_ASSERT(status, "Could not initialize Glad!");
	}
	void OpenGLContext::SwapBuffers()
	{
		XS_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}