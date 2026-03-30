#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string getFileContents(const char* filename);

class Shader {
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

	~Shader() { destroy(); }

	Shader(const Shader&) = delete;
	Shader& operator= (const Shader&) = delete;

	Shader(Shader&& other) noexcept : ID(other.ID) { other.ID = 0; }
	Shader& operator=(Shader&& other) noexcept {
		if (this != &other) {
			destroy();
			ID = other.ID;
			other.ID = 0;
		}
		return *this;
	}

    void activate();
    void destroy();

	void checkForCompileErrors(unsigned int shader, const char* type);
};

#endif