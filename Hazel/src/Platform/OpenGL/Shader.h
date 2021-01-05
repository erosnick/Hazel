#pragma once

#include <unordered_map>

namespace Hazel
{
	struct ShaderSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};

	class Shader
	{
	public:

		Shader() {}
		Shader(const std::string& inFilePath);
		~Shader();

		void Bind() const;
		void Unbind() const;
		
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	private:

		uint32_t GetUniformLocation(const std::string& name);

		ShaderSource ParseShader(const std::string& filePath);
		std::string LoadShader(const std::string& shaderFile);
		uint32_t CompileShader(unsigned int type, const std::string& source);
		int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	private:
		uint32_t rendererID = 0;
		std::string filePath;
		std::unordered_map<std::string, int> uniformLocationCache;
	};
}
