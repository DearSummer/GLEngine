#pragma once
#include <GL/glew.h>

class Texture2D
{
public:
	Texture2D();
	explicit Texture2D(const char * resourcePath);
	~Texture2D() = default;

	static void loadTexture2D(const char * resourcePath);
	static void setTextureLoadParameter(GLenum name, GLint param);
	void active(GLenum texture) const;
	void active() const;

	unsigned int id{};
};

