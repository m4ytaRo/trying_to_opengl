#include"EBO.h"

void EBO::bind()
{
	// also links EBO to current VAO
	// you should bind VAO before calling this function
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::loadData(GLuint* indices, GLsizeiptr size) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::destroy()
{
    if (ID != 0)
    {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
}