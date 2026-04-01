#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

int main() {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // These lines tells library GLFW to request to create OpenGL context of version 3.3 (runtime)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //This line tells GLFW to request a Core Profile context, which excludes deprecated OpenGL functionality

    GLfloat vertices[] = {
        -0.5f,          -0.5f,      0.0f,   1.0f,    0.0f,      0.0f,       0.0f, 1.0f,      // left upper
        0.5f,           -0.5f,      0.0f,   0.0f,    1.0f,      0.0f,       1.0f, 1.0f,      // right upper
        0.5f,           0.5f,       0.0f,   0.0f,    0.0f,      1.0f,       1.0f, 0.0f,      // right lower corner
        -0.5f,          0.5f,       0.0f,   1.0f,    0.0f,      0.0f,       0.0f, 0.0f,      // left lower corner
    };

    GLuint indeces[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLFWwindow* window = glfwCreateWindow(800, 800, "Test", NULL, NULL);
    // glfwCreateWindow atomically (for user) creates both a window and its associated context
    // in fact these are 2 low-level operations
    if (window == NULL) {
        std::cout << "Failed to create a window!\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // remind: openGL is a state machine

    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 800);
    // Defines the drawing area in pixels. 
    // It stretches the normalized scene (-1 to +1) to fill the 800x800 region 
    // starting from the bottom-left corner (0,0).

    Shader shaderProgram = Shader("default.vert", "default.frag");

    VAO VAO1;
    VAO1.bind();


    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1;
    EBO1.bind();
    EBO1.loadData(indeces, sizeof(indeces));

    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.linkAttrib(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    VAO1.unbind();
    VBO1.unbind();
    EBO1.unbind();
    
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    int imgWidth, imgHeight, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("water16x.png", &imgWidth, &imgHeight, &numColCh, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLenum format = (numColCh == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(bytes);

    GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
    shaderProgram.activate();
    glUniform1i(tex0Uni, 0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.activate();
        glUniform1f(uniID, 0.0f);
        glBindTexture(GL_TEXTURE_2D, texture);
        VAO1.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.destroy();
    VBO1.destroy();
    EBO1.destroy();
    shaderProgram.destroy();
    glDeleteTextures(1, &texture);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}