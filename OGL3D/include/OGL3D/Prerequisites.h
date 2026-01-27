#pragma once

#include <memory>

class VertexArrayObject;
class UniformBuffer;
class ShaderProgram;

using VertexArrayObjectPtr = std::shared_ptr<VertexArrayObject>;
using UniformBufferPtr = std::shared_ptr<UniformBuffer>;
using ShaderProgramPtr = std::shared_ptr<ShaderProgram>;

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

struct UniformBufferData
{
	unsigned int size = 0;
};

enum TriangleType 
{
	TriangleList = 0,
	TriangleStrip
};

enum ShaderType
{
	VertexShader = 0,
	FragmentShader
};

enum class InputMouse
{
	LeftButtonDown,
	RightButtonDown,
	NoButtonDown
};