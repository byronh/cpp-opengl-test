#include "Mesh.h"

namespace astro
{

	Mesh::Mesh(const VertexBuffer & vertices, const IndexBuffer & indices) :
		numIndices(indices.size())
	{
		init(vertices, indices);
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &vertexArrayHandle);
		glDeleteBuffers(1, &vertexBufferHandle);
		glDeleteBuffers(1, &indexBufferHandle);
	}

	void Mesh::render()
	{
		glBindVertexArray(vertexArrayHandle);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void*)0);
		glBindVertexArray(0);
	}

	void Mesh::init(const VertexBuffer & vertices, const IndexBuffer & indices)
	{
		glGenVertexArrays(1, &vertexArrayHandle);
		glBindVertexArray(vertexArrayHandle);

		glGenBuffers(1, &vertexBufferHandle);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), &vertices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		glGenBuffers(1, &indexBufferHandle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* numIndices, &indices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

}