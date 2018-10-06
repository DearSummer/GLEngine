#pragma once
#include <GL/glew.h>

class Texture2D
{
private:
	Texture2D() = default;
public:
	~Texture2D() = default;

	static void loadTexture2D(const char * resourcePath);
	void active(GLenum texture) const;
	void active() const;

	unsigned int id{};

	class Builder
	{
	private:
		unsigned int id = 0;
		int wrapS = GL_REPEAT;
		int wrapT = GL_REPEAT;
		int minFilter = GL_LINEAR;
		int magFilter = GL_LINEAR;
		const char * resourcePath = nullptr;

	public:
		Builder & setTextureLoadParamerter(GLenum name, GLint param);
		Builder & setResourcePath(const char * resourcePath);
		Texture2D * build();
	};
};

