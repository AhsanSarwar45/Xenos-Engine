#include "xenospch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Xenos
{
	Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XS_CORE_ASSERT(false, "RendererAPI::None is currently no supported");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return std::make_shared<OpenGLShader>(filePath);
		default:

			break;
		}

		XS_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XS_CORE_ASSERT(false, "RendererAPI::None is currently no supported");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		default:

			break;
		}

		XS_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		XS_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists!");
		m_Shaders[name] = shader;
	}
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);

	}
	
	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		XS_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found!");
		return m_Shaders[name];
	}
}