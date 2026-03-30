#include "VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices


// Binds the VBO
void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::destroy()
{
	glDeleteBuffers(1, &ID);
}