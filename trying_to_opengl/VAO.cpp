#include"VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VAO::linkVBO(VBO& VBO, GLuint layout)
{
	VBO.bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.unbind();
}

// Binds the VAO
void VAO::bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::destroy()
{
	glDeleteVertexArrays(1, &ID);
}