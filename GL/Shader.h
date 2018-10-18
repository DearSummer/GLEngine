#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/vec3.hpp>


class Shader
{
private:
	unsigned int createShaderProgram() const;
	static void checkCompileErrors(unsigned int id, const std::string& type);
public:
	Shader(const char* vertexPath,const char* fragmentPath);
	~Shader() = default;

	void use() const;
	void setBool(const std::string& name,bool value) const;
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
	void setUnsignInt(const std::string& name, unsigned int value) const;
	void setMatrix4X4(const std::string& name, GLsizei count, const GLfloat * value) const;
	void setVector3(const std::string& name, const GLfloat x, const GLfloat y, const GLfloat z) const;
	void setVector3(const std::string& name, const glm::vec3 vec3)const;

	const char * vertexShaderCode;
	const char * fragmentShaderCode;


	unsigned int id; //shader program id
};

