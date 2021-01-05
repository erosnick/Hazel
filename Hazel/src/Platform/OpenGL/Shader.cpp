#include "HazelPCH.h"
#include "Shader.h"
#include "Hazel/Log.h"
#include "Utils.h"

namespace Hazel
{
	Shader::Shader(const std::string& inFilePath)
		: rendererID(0),
		filePath(inFilePath)
	{
		auto [vertexShader, fragmentShader] = ParseShader(filePath);
		rendererID = CreateShader(vertexShader, fragmentShader);
	}

	Shader::~Shader()
	{
		//GLCall(glDeleteProgram(rendererID));
	}

	void Shader::Bind() const
	{
		GLCall(glUseProgram(rendererID));
	}

	void Shader::Unbind() const
	{
		GLCall(glUseProgram(0));
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		GLCall(glUniform1i(GetUniformLocation(name), value));
	}

	void Shader::SetUniform1f(const std::string& name, float value)
	{
		GLCall(glUniform1f(GetUniformLocation(name), value));
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
	}

	uint32_t Shader::GetUniformLocation(const std::string& name)
	{
		if (uniformLocationCache.find(name) != uniformLocationCache.end())
		{
			return uniformLocationCache[name];
		}

		GLCall(int location = glGetUniformLocation(rendererID, name.c_str()));

		if (location == -1)
		{
			HAZEL_CORE_ERROR("Warning: uniform '{0}' doesn't exist!\n", name);
		}

		uniformLocationCache[name] = location;

		return location;
	}

	ShaderSource Shader::ParseShader(const std::string& filePath)
	{
		std::ifstream stream(filePath);

		enum class ShaderType
		{
			None = -1,
			Vertex = 0,
			Fragment = 1
		};

		std::string line;
		std::stringstream ss[2];

		ShaderType shaderType = ShaderType::None;

		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					shaderType = ShaderType::Vertex;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					shaderType = ShaderType::Fragment;
				}
			}
			else
			{
				ss[static_cast<int>(shaderType)] << line << "\n";
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	std::string Shader::LoadShader(const std::string& shaderFile)
	{
		std::ifstream file(shaderFile);

		if (file.eof())
		{
			HAZEL_CORE_ERROR("Can not open Error: {0}", shaderFile);
			return "";
		}

		int length;
		file.seekg(0, std::ios::end);
		length = file.tellg();

		file.seekg(0, std::ios::beg);
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string shader(buffer.str());
		//file.read(&shader[0], length);

		file.close();

		return shader;
	}

	uint32_t Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(sizeof(char) * length);
			glGetShaderInfoLog(id, length, &length, message);

			HAZEL_CORE_ERROR("Failed to compile {0}.", (type == GL_VERTEX_SHADER) ? "vertex shader" : "fragment shader");
			HAZEL_CORE_ERROR("OpenGL Error: {0}", message);

			glDeleteShader(id);

			return 0;
		}

		return id;
	}

	int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		//std::string vertexShader = loadShader(vertexShaderFile);
		//std::string fragmentShader = loadShader(fragmentShaderFile);

		if (!(vertexShader.length() > 0 && fragmentShader.size() > 0))
		{
			HAZEL_CORE_ERROR("Wrong shader size");
			return 0;
		}

		GLuint program = glCreateProgram();
		GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
}