#include "Texture2D.h"

#include <GL/glew.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <fstream>

using std::exception;

#define RED_CHANNAL  1
#define RGB_CHANNAL  3
#define RGBA_CHANNAL 4


void Texture2D::loadTexture2D(const char * resourcePath)
{
	int width, height, nrChannal;
	unsigned char * picData = stbi_load(resourcePath, &width, &height, &nrChannal, 0);
	if (picData)
	{
		//将图片载入cpu当中
		switch (nrChannal)
		{
		case RED_CHANNAL:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, picData);
			break;
		case RGB_CHANNAL:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, picData);
			break;
		case RGBA_CHANNAL:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, picData);
			break;
		default:
			throw exception("unknow channl");
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		throw exception("load img failed");
	}
	stbi_image_free(picData);
}



void Texture2D::active(const GLenum texture) const
{
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::active() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

Texture2D::Builder & Texture2D::Builder::setTextureLoadParamerter(const GLenum name, const GLint param)
{
	switch (name)
	{
	case GL_TEXTURE_WRAP_S:
		wrapS = param;
		break;;
	case GL_TEXTURE_WRAP_T:
		wrapT = param;
		break;
	case GL_TEXTURE_MIN_FILTER:
		minFilter = param;
		break;
	case GL_TEXTURE_MAG_FILTER:
		magFilter = param;
		break;
	default:
		throw exception("not exist such name");
	}
	
	return * this;
}

Texture2D::Builder & Texture2D::Builder::setResourcePath(const char* resourcePath)
{
	this->resourcePath = resourcePath;
	return * this;
}

Texture2D * Texture2D::Builder::build()
{

	std::fstream imageFile;
	imageFile.open(resourcePath, std::ios::in);
	if (!imageFile)
		return nullptr;

	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	Texture2D * result = new Texture2D();
	result->id = id;

	if (resourcePath == nullptr)
		return result;

	loadTexture2D(resourcePath);
	return result;
}
