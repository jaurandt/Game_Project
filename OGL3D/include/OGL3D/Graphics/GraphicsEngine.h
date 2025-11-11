#pragma once
#include <OGL3D/Prerequisites.h>
#include <OGL3D/Math/Vec4.h>
#include <OGL3D/Math/Rect.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferData& data);

	void clear(const Vec4& color);
	void setViewport(const Rect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	void drawTriangles(unsigned int vertexCount, unsigned int offset);
};

