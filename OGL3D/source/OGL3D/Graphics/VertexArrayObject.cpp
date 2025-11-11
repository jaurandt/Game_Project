#include <OGL3D/Graphics/VertexArrayObject.h>
#include <glad/glad.h>

VertexArrayObject::VertexArrayObject(const VertexBufferData& data)
{
	glGenBuffers(1, &m_vertexBufferID);

	glGenVertexArrays(1, &m_vertexArrayObjectID);
	glBindVertexArray(m_vertexArrayObjectID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	
	//LEFT OFF AT 24:27 
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.vertexSize, 0);
	glEnableVertexAttribArray(0);



	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayObjectID);

}

unsigned int VertexArrayObject::getID()
{
	return m_vertexArrayObjectID;
}
