#pragma once
#include <memory>

class VertexArrayObject;
class ShaderProgram;

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

struct VertexAttribute
{
	unsigned int elements = 0;
};

struct VertexBufferData
{
	void* verticesList = nullptr;
	unsigned int vertexSize = 0;
	unsigned int listSize = 0;

	VertexAttribute* attributesList = nullptr;
	unsigned int attributesListSize = 0;
};

struct ShaderProgramPath
{
	const wchar_t* vertexShaderFilePath;
	const wchar_t* fragmentShaderFilePath;
};

enum ShaderType
{
	VertexShader = 0,
	FragmentShader
};

//LEFT OFF AT 37:43 in Shaders