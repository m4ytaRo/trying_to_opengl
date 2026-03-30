#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
    GLuint ID;
	VAO(){ glGenVertexArrays(1, &ID); }

	~VAO() { destroy(); }

	VAO(const VBO&) = delete;
	VAO& operator= (const VAO&) = delete;

	VAO(VAO&& other) noexcept : ID(other.ID) { other.ID = 0; }
	VAO& operator=(VAO&& other) noexcept {
		if (this != &other) {
			destroy();
			ID = other.ID;
			other.ID = 0;
		}
		return *this;
	}

    void linkVBO(VBO& VBO, GLuint layout);
    void bind();
    void unbind();
    void destroy();

};

#endif