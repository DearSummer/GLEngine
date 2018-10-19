#include "Mesh.h"
#include <utility>

Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	:vertices(std::move(vertices)),indices(std::move(indices)),textures(std::move(textures))
{
	setUpMesh();
}

Mesh::~Mesh()
= default;

void Mesh::draw(const Shader * shader)
{
	unsigned int diffuseIndex = 1;
	unsigned int specularIndex = 1;

	for (unsigned int i = 0;i < textures.size();i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name;
		switch (textures[i].type)
		{
		case TextureType::diffuse:
			name = "texture_diffuse_";
			number = std::to_string(diffuseIndex++);
			break;
		case TextureType::specular:
			name = "texture_specular_";
			number = std::to_string(specularIndex++);
			break;

		default:
			break;
		}
		const std::string textureName = name + number;

		shader->setFloat("material." + textureName, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);


	//draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setUpMesh()
{
	//gen vao vbo ebo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind vao and vbo
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//bind vbo data
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), &vertices[0], GL_STATIC_DRAW);

	//bind ebo and ebo data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void *)0);

	//vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void *)offsetof(MeshVertex, normal));

	//vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void *)offsetof(MeshVertex, normal));

	glBindVertexArray(0);
}
