#pragma once

#include "../core/Core.h"

#include <vector>

namespace astro
{

	struct Vertex
	{
		Vector3f position;
		Vector2f texture;
		//Vector3f normal;
	};

	typedef std::vector<Vertex> VertexBuffer;
	typedef std::vector<unsigned int> IndexBuffer;


	class Mesh
	{

	public:

		Mesh(const VertexBuffer & vertices, const IndexBuffer & indices);
		~Mesh();

		void render();

	private:

		unsigned int numIndices;

		Handle vertexArrayHandle;
		Handle vertexBufferHandle;
		Handle indexBufferHandle;

		void init(const VertexBuffer & vertices, const IndexBuffer & indices);

	};

}