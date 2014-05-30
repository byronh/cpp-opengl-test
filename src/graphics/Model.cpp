#include "Model.h"
#include "Texture.h"

#include <assert.h>

#define INDEX_BUFFER 0    
#define POS_VB       1
#define NORMAL_VB    2
#define TEXCOORD_VB  3    
#define WVP_MAT_VB   4
#define WORLD_MAT_VB 5

#define POSITION_LOCATION 0
#define TEX_COORD_LOCATION 1
#define NORMAL_LOCATION 2
#define WVP_LOCATION 3
#define WORLD_LOCATION 7

namespace astro
{

	Model::Model(const std::string & relativePath, bool flipUV)
	{
		std::string absolutePath = ASSET_DIR + relativePath;

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(sizeof(attributeBuffers) / sizeof(attributeBuffers[0]), attributeBuffers);

		Assimp::Importer importer;

		unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals;
		if (flipUV)
		{
			flags |= aiProcess_FlipUVs;
		}

		const aiScene * scene = importer.ReadFile(absolutePath, flags);
		if (!scene)
		{
			throw Exception("Failed to load scene " + absolutePath + ":\n" + importer.GetErrorString());
		}

		buildFromScene(scene);

		glBindVertexArray(0);
	}

	Model::~Model()
	{
		glDeleteVertexArrays(1, &vertexArray);
		glDeleteBuffers(sizeof(attributeBuffers) / sizeof(attributeBuffers[0]), attributeBuffers);
	}

	void Model::renderMeshes(unsigned int numInstances, const Matrix4f * MVPMatrices, const Matrix4f * WorldMatrices)
	{

		glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers[WVP_MAT_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Matrix4f)* numInstances, MVPMatrices, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers[WORLD_MAT_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Matrix4f)* numInstances, WorldMatrices, GL_DYNAMIC_DRAW);

		glBindVertexArray(vertexArray);

		for (unsigned int i = 0; i < meshes.size(); ++i)
		{
			const unsigned int textureID = meshes[i].textureID;
			assert(textureID < meshes.size());

			if (textures[textureID])
			{
				textures[textureID]->bind(0);
			}
			glDrawElementsInstancedBaseVertex(
				GL_TRIANGLES,
				meshes[i].numIndices,
				GL_UNSIGNED_INT,
				(void*)(sizeof(unsigned int)* meshes[i].baseIndex),
				numInstances,
				meshes[i].baseVertex);
			if (textures[textureID])
			{
				textures[textureID]->unbind();
			}
		}

		glBindVertexArray(0);
	}

	void Model::buildFromScene(const aiScene * scene)
	{
		meshes.resize(scene->mNumMeshes);
		textures.resize(scene->mNumMaterials);

		unsigned int vertexCount = 0;
		unsigned int indexCount = 0;

		for (unsigned int i = 0; i < meshes.size(); ++i)
		{
			// TODO iterate through mFaces first and count indices
			meshes[i].numIndices = scene->mMeshes[i]->mNumFaces * 3;
			meshes[i].baseVertex = vertexCount;
			meshes[i].baseIndex = indexCount;
			meshes[i].textureID = scene->mMeshes[i]->mMaterialIndex;

			vertexCount += scene->mMeshes[i]->mNumVertices;
			indexCount += meshes[i].numIndices;
		}

		std::vector<Vector3f> positions;
		std::vector<Vector3f> normals;
		std::vector<Vector2f> uvCoords;
		std::vector<unsigned int> indices;

		positions.reserve(vertexCount);
		normals.reserve(vertexCount);
		uvCoords.reserve(vertexCount);
		indices.reserve(indexCount);

		for (unsigned int i = 0; i < meshes.size(); ++i)
		{
			buildMesh(scene->mMeshes[i], positions, normals, uvCoords, indices);
		}

		buildTextures(scene);

		// TODO refactor with an Attribute class
		glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers[POS_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(POSITION_LOCATION);
		glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers[TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoords[0]) * uvCoords.size(), &uvCoords[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(TEX_COORD_LOCATION);
		glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers[NORMAL_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0])* normals.size(), &normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(NORMAL_LOCATION);
		glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, attributeBuffers[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers[WVP_MAT_VB]);

		for (unsigned int i = 0; i < 4; ++i)
		{
			glEnableVertexAttribArray(WVP_LOCATION + i);
			glVertexAttribPointer(WVP_LOCATION + i, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4f), (const GLvoid*)(sizeof(GLfloat)* i * 4));
			glVertexAttribDivisor(WVP_LOCATION + i, 1);
		}

		glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers[WORLD_MAT_VB]);

		for (unsigned int i = 0; i < 4; ++i)
		{
			glEnableVertexAttribArray(WORLD_LOCATION + i);
			glVertexAttribPointer(WORLD_LOCATION + i, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4f), (const GLvoid*)(sizeof(GLfloat)* i * 4));
			glVertexAttribDivisor(WORLD_LOCATION + i, 1);
		}
	}

	void Model::buildMesh(const aiMesh * mesh, std::vector<Vector3f> & positions, std::vector<Vector3f> & normals, std::vector<Vector2f> & uvCoords, std::vector<unsigned int> & indices)
	{
		const aiVector3D origin(0.0f, 0.0f, 0.0f);

		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			const aiVector3D * pos = &(mesh->mVertices[i]);
			const aiVector3D * normal = &(mesh->mNormals[i]);
			const aiVector3D * uvCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &origin;
			positions.push_back(Vector3f(pos->x, pos->y, pos->z));
			normals.push_back(Vector3f(normal->x, normal->y, normal->z));
			uvCoords.push_back(Vector2f(uvCoord->x, uvCoord->y));
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			const aiFace & face = mesh->mFaces[i];
			assert(face.mNumIndices == 3);
			for (unsigned int i = 0; i < 3; ++i)
			{
				indices.push_back(face.mIndices[i]);
			}
		}
	}

	void Model::buildTextures(const aiScene * scene)
	{
		for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
		{
			textures[i] = NULL;
			const aiMaterial * material = scene->mMaterials[i];

			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
			{
				aiString path;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				{
					textures[i] = new Texture(path.data, Texture::TEXTURETYPE_2D);
				}
			}
		}
	}

}