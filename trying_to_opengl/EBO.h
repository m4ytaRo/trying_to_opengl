#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	GLuint ID;
	EBO() { glGenBuffers(1, &ID); }
	EBO(GLuint* indices, GLsizeiptr size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}
	~EBO() { destroy(); }

	EBO(const EBO&) = delete;
	EBO& operator= (const EBO&) = delete;

	EBO(EBO&& other) noexcept : ID(other.ID) { other.ID = 0; }
	EBO& operator=(EBO&& other) noexcept {
		if (this != &other) {
			destroy();
			ID = other.ID;
			other.ID = 0;
		}
		return *this;
	}

	void bind();
	void unbind();
	void loadData(GLuint* indices, GLsizeiptr size);
	void destroy();
};

#endif