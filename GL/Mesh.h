#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include "Shader.h"
#include <glm/vec2.hpp>
#include <assimp/types.h>

enum TextureType
{
	specular,
	diffuse
};

struct MeshVertex
{
	glm::vec3 position = glm::vec3(0);
	glm::vec3 normal = glm::vec3(0);
	glm::vec2 texCoords = glm::vec2(0);
};

struct Texture
{
	unsigned int id;
	TextureType type;
	aiString path;
};

class Mesh
{
public:

	/*mesh data*/
	std::vector<MeshVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<MeshVertex> vertices,std::vector<unsigned int> indices,std::vector<Texture> textures);
	~Mesh();

	/*draw mesh(like link samplers to texture)*/
	void draw(const Shader * shader);
private:

	/*render data*/
	unsigned int VAO = 0, VBO = 0, EBO = 0;
	void setUpMesh();
};

