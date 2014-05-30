#pragma once

#include "../core/Core.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>

namespace astro
{

	class Texture;

	class Model
	{

	public:

		Model(const std::string & relativePath, bool flipUV = false);
		~Model();

		void renderMeshes(unsigned int numInstances, const Matrix4f * MVPMatrices, const Matrix4f * WorldMatrices);

	private:

		struct Mesh
		{
			Mesh() :
			numIndices(0),
			baseVertex(0),
			baseIndex(0),
			textureID(-1)
			{
			}

			unsigned int numIndices;
			unsigned int baseVertex;
			unsigned int baseIndex;
			unsigned int textureID;
		};

		Handle vertexArray;
		Handle attributeBuffers[6];

		std::vector<Mesh> meshes;
		std::vector<Texture *> textures;

		void buildFromScene(const aiScene * scene);
		void buildMesh(const aiMesh * mesh,
			std::vector<Vector3f> & positions,
			std::vector<Vector3f> & normals,
			std::vector<Vector2f> & uvCoords,
			std::vector<unsigned int> & indices);
		void buildTextures(const aiScene * scene);

		Model(const Model & other);
		const Model & operator = (const Model & other);

	};

}