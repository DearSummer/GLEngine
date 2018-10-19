#include "Model.h"
#include <glm/vec2.hpp>
#include "Texture2D.h"


Model::Model(const char * path)
{
	loadModel(path);
}

Model::~Model()
= default;

void Model::draw(const Shader * shader)
{
	for(int i = 0;i < meshes.size();i++)
	{
		meshes[i].draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		throw std::exception(importer.GetErrorString());
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	for(unsigned int i = 0;i < node->mNumMeshes;i++)
	{
		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for(unsigned int i = 0;i < node->mNumChildren;i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<MeshVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> texturs;

	//process vertex positions,normals and texture coordinates
	for(unsigned int i= 0;i < mesh->mNumVertices;i++)
	{
		MeshVertex _vertex;
		glm::vec3 _vector(0);
		_vector.x = mesh->mVertices[i].x;
		_vector.y = mesh->mVertices[i].y;
		_vector.z = mesh->mVertices[i].z;
		_vertex.position = _vector;
		glm::vec3 _normal(0);
		_normal.x = mesh->mNormals[i].x;
		_normal.y = mesh->mNormals[i].y;
		_normal.z = mesh->mNormals[i].z;
		_vertex.normal = _normal;

		glm::vec2 _coords(0);
		if(mesh->mTextureCoords[0])
		{
			_coords.x = mesh->mTextureCoords[0]->x;
			_coords.y = mesh->mTextureCoords[0]->y;
		}
		_vertex.texCoords = _coords;
		vertices.push_back(_vertex);
	}

	//process indices
	for(unsigned int i = 0;i < mesh->mNumFaces;i++)
	{
		aiFace face = mesh->mFaces[i];
		for(unsigned int j = 0;j < face.mNumIndices;j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//process texture if have
	if(mesh->mMaterialIndex >= 0)
	{
		aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::diffuse);
		texturs.insert(texturs.end(), diffuseMap.begin(), diffuseMap.end());

		std::vector<Texture> spcularMap = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::specular);
		texturs.insert(texturs.end(), spcularMap.begin(), spcularMap.end());
	}

	return Mesh(vertices, indices, texturs);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, TextureType textureType)
{
	std::vector<Texture> textures;
	for(unsigned int i = 0;i < mat->GetTextureCount(type);i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for(unsigned int j = 0;j < texturesLoaded.size();j++)
		{
			if(std::strcmp(texturesLoaded[j].path.data,str.C_Str()) == 0)
			{
				textures.push_back(texturesLoaded[j]);
				skip = true;
				break;
			}
		}
		if(skip)
			continue;

		Texture texture;
		std::string resourcePath = directory;
		resourcePath.append("/");
		resourcePath.append(str.C_Str());
		Texture2D * texture2D = Texture2D::Builder().setResourcePath(str.C_Str()).build();
		texture.id = texture2D->id;
		texture.type = textureType;
		texture.path = str;
		textures.push_back(texture);
	}

	return textures;
}
