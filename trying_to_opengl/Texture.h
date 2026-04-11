#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
class Texture
{
public:
	GLuint ID = 0;
	GLenum type;
	~Texture();
	Texture(const char* image, GLenum texType, GLenum slot, GLenum pixelType);

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	Texture(Texture&&) = delete;
	Texture& operator=(Texture&&) = delete;
	// found out it is similar to Texture& operator=(Texture&& tex) = delete;

	/**
	 * @brief links texture unit to uniform in shader
	 */
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void bind();
	void unbind();
	void destroy();
};

#endif

