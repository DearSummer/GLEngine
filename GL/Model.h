#pragma once
#include "Shader.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class Model
{
public:
	Model(const char* path,const char * textureDirectory);
	~Model();

	void draw(const Shader * shader);
private:
	/*model data*/
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> texturesLoaded;

	void loadModel(const std::string& path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType textureType);
	

};

