#pragma once
#include <vector>
#include <string>

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"



class Model
{
public:
	Model();

	void loadModel(const std::string& fileName, const std::string& textFolder);
	void renderModel();
	void clearModel();
	Transform transform;
	~Model();

private:
	void loadNode(aiNode* node , const aiScene *scene);
	void loadMesh(aiMesh *mesh, const aiScene *scene);
	void loadMaterial(const aiScene *scene, const std::string& textFolder);



	std::vector<Mesh*> meshList;
	std::vector<Texture*> textureList;
	std::vector<unsigned int> meshToTexture;
};

