#pragma once
#include <OGL3D/Prerequisites.h>

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferData& data);
	~VertexArrayObject();

	unsigned int getID();
private:
	unsigned int m_vertexBufferID = 0;
	unsigned int m_vertexArrayObjectID = 0;
};

