#include "Texture2D.h"

#include <GL/glew.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using std::exception;

#define RGB_CHANNAL  3
#define RGBA_CHANNAL 4

Texture2D::Texture2D()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	//配置纹理环绕和纹理过滤的方式
	setTextureLoadParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	setTextureLoadParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	setTextureLoadParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	setTextureLoadParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
}

Texture2D::Texture2D(const char * resourcePath) :Texture2D()
{
	loadTexture2D(resourcePath);
}


void Texture2D::loadTexture2D(const char * resourcePath)
{
	int width, height, nrChannal;
	unsigned char * picData = stbi_load(resourcePath, &width, &height, &nrChannal, 0);
	if(picData)
	{
		//将图片载入cpu当中
		switch (nrChannal)
		{
		case RGB_CHANNAL:			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, picData);
			break;
		case RGBA_CHANNAL:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, picData);
			break;
		default:
			break;
		}

		
		glGenerateMipmap(GL_TEXTURE_2D);
	}else
	{
		throw exception("load img failed");
	}
	stbi_image_free(picData);
}

void Texture2D::setTextureLoadParameter(const GLenum name, const GLint param)
{
	glTextureParameteri(GL_TEXTURE_2D, name, param);
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
