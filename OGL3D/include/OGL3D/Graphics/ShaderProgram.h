#pragma once
#include <OGL3D/Prerequisites.h>


class ShaderProgram
{
public:
	ShaderProgram(const ShaderProgramPath& path);
	~ShaderProgram();
	unsigned int getID() { return m_programID; }

private:
	void attach(const wchar_t* filePath, ShaderType shaderType);
	void link();

	unsigned int m_programID = 0;
	unsigned int m_attachedShaders[2] = {};
};

