#include "Model.h"



Model::Model()
{
}

void Model::renderModel()
{
	for (size_t i = 0; i < meshList.size(); i++)
	{
		unsigned int materialInd = meshToTexture[i];

		if (materialInd < textureList.size()&& textureList[materialInd])
		{
			textureList[materialInd]->useTexture();
		}

		meshList[i]->renderMesh();
	}
}
void Model::loadModel(const std::string& fileName, const std::string& textFolder) 
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene) {
		printf("Failure to load model : %s", fileName, importer.GetErrorString());
		return;
	}

	loadNode(scene->mRootNode, scene);

	loadMaterial(scene,textFolder);
}
void Model::loadNode(aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		loadNode(node->mChildren[i], scene);
	}
}
void Model::loadMesh(aiMesh* mesh, const aiScene* scene) 
{
	std::vector<GLfloat>vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i <mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y });
		}
		else
		{
			vertices.insert(vertices.end(), { 0.0f,0.0f });
		}
		//maybe change to pos if weird
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x,-mesh->mNormals[i].y,-mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);

		}
	}

	Mesh* newMesh = new Mesh();

	newMesh->createMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshList.push_back(newMesh);
	meshToTexture.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterial(const aiScene* scene, const std::string& textFolder) 
{
	textureList.resize(scene->mNumMaterials);

	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		textureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE)) 
		{
			aiString path;

			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int index = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(index + 1);

				std::string texPath = std::string("..//Resources//textures//") + textFolder + ("//") + filename;

				textureList[i] = new Texture(texPath.c_str());

				if (!textureList[i]->loadTexture()) 
				{
					//printf("Failed to load texture: %s", texPath);
					delete textureList[i];
					textureList[i] = nullptr;
				}

			}
		}
		if (!textureList[i])
		{
		//	printf("Set to default texture");
			textureList[i] = new Texture("..//Resources//textures//plain.png");
			textureList[i]->loadTextureA();
		}
	}
}
void Model ::clearModel()
{
	for (size_t i = 0; i < meshList.size(); i++)
	{
		if (meshList[i]) {
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}

	for (size_t i = 0; i < textureList.size(); i++)
	{
		if (textureList[i]) {
			delete textureList[i];
			textureList[i] = nullptr;
		}
	}
}
Model::~Model()
{
}
