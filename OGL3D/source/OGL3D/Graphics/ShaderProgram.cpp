#include <OGL3D/Graphics/ShaderProgram.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const ShaderProgramPath& path)
{
	m_programID = glCreateProgram();
	attach(path.vertexShaderFilePath, VertexShader);
	attach(path.fragmentShaderFilePath, FragmentShader);
	link();
}

ShaderProgram::~ShaderProgram()
{
	for (int i = 0; i < 2; i++)
	{
		glDetachShader(m_programID, m_attachedShaders[i]);
		glDeleteShader(m_attachedShaders[i]);
	}
	glDeleteProgram(m_programID);
}

void ShaderProgram::attach(const wchar_t* filePath, ShaderType shaderType)
{
	std::ifstream fileStream(filePath);
	std::string shaderCode;
	if (fileStream.is_open())
	{
		std::stringstream buffer;
		buffer << fileStream.rdbuf();
		shaderCode = buffer.str();
		fileStream.close();
		//const char* shaderCodeCStr = shaderCode.c_str();
		/*
		int success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
			throw std::runtime_error(std::string("Shader Compilation Error: ") + infoLog);
		}
		glAttachShader(m_programID, shaderID);
		m_attachedShaders[shaderType] = shaderID;
		*/	
	}
	else
	{
		throw std::runtime_error("Shader File Error: Unable to open file");
	}

	unsigned int shaderID = 0;
	if (shaderType == VertexShader)
	{
		shaderID = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (shaderType == FragmentShader)
	{
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else
	{
		throw std::runtime_error("Shader Type Error: Unknown shader type");
	}

	auto shaderCodeCStr = shaderCode.c_str();
	glShaderSource(shaderID, 1, &shaderCodeCStr, NULL);

	glCompileShader(shaderID);

	glAttachShader(m_programID, shaderID);
	m_attachedShaders[shaderType] = shaderID;
}

void ShaderProgram::link()
{
	glLinkProgram(m_programID);
}
