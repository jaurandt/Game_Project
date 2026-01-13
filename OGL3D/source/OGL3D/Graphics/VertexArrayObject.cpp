#include <OGL3D/Graphics/VertexArrayObject.h>
#include <glad/glad.h>

VertexArrayObject::VertexArrayObject(const VertexBufferData& data)
{
	glGenBuffers(1, &m_vertexBufferID);

	glGenVertexArrays(1, &m_vertexArrayObjectID);
	glBindVertexArray(m_vertexArrayObjectID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);
	
	for(unsigned int i = 0; i < data.attributesListSize; i++)
	{
		glVertexAttribPointer(
			i, 
			data.attributesList[i].elements,
			GL_FLOAT, 
			GL_FALSE, 
			data.vertexSize, 
			(void*)((i == 0) ? 0 : data.attributesList[i - 1].elements * sizeof(float))
		);
		glEnableVertexAttribArray(i);
	}
	
	glBindVertexArray(0);

	m_vertexBufferData = data;
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
