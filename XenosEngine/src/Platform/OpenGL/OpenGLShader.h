#pragma once
#include "Xenos/Renderer/Shader.h"
#include<glm/glm.hpp>

typedef unsigned int GLenum;
namespace Xenos
{
	
	class OpenGLShader: public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string fragmentSrc);
		OpenGLShader(const std::string& filePath);
		virtual ~OpenGLShader();

		virtual const std::string& GetName() const override { return m_Name; }

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat(const std::string& name, const float value) override;
		virtual void SetInt(const std::string& name, const int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);

		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat(const std::string& name, const float value);

		void UploadUniformInt(const std::string& name, const int  value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string source);
		void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}