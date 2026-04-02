#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:
    GLuint ID = 0;
	VBO(GLfloat* vertices, GLsizeiptr size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	~VBO() { destroy(); }

	VBO(const VBO&) = delete;
	VBO& operator= (const VBO&) = delete;

	VBO(VBO&& other) noexcept : ID(other.ID) { other.ID = 0; }
	VBO& operator=(VBO&& other) noexcept {
		if (this != &other) {
			destroy();
			ID = other.ID;
			other.ID = 0;
		}
		return *this;
	}

    void bind();
    void unbind();
    void destroy();

};

#endif

