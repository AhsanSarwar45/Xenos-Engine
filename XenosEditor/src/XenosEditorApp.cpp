#include <Xenos.h>
/*-----------ENTRY POINT--------------*/
#include "Xenos/Core/EntryPoint.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EditorLayer.h"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Xenos
{
	class XenosEditor : public Application
	{
	public:
		XenosEditor()
			:Application("Xenos Editor")
		{
			//PushLayer(new TestLayer());
			PushLayer(new EditorLayer());
		}

		~XenosEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new XenosEditor();
	}
}

