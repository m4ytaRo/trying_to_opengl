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
        -0.5f,      -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f,    0.2f,      0.1f,           // lower left corner
        0.5f,       -0.5f * float(sqrt(3)) / 3,     0.0f,   0.9f,    0.125f,    0.1f,           //lower right corner
        0.0f,       0.5f * float(sqrt(3)) * 2 / 3,  0.0f,   0.8f,    0.782f,    0.4568f,        // upper corner

        -0.5f / 2,  0.5f * float(sqrt(3)) / 6,      0.0f,   0.8f,    0.2f,     0.1f,            //inner left
        0.5f / 2,   0.5f * float(sqrt(3)) / 6,      0.0f,   0.9f,    0.125f,   0.1f,            //inner right
        0.0f,       -0.5f * float(sqrt(3)) / 3,     0.0f,   0.8f,    0.782f,   0.4568f,         //inner down
    };

    GLuint indeces[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

    GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
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

    glViewport(0, 0, 800, 600);
    // Defines the drawing area in pixels. 
    // It stretches the normalized scene (-1 to +1) to fill the 800x600 region 
    // starting from the bottom-left corner (0,0).

    Shader shaderProgram = Shader("default.vert", "default.frag");

    VAO VAO1;
    VAO1.bind();


    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1;
    EBO1.bind();
    EBO1.loadData(indeces, sizeof(indeces));

    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    
    VAO1.unbind();
    VBO1.unbind();
    EBO1.unbind();
    
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.activate();
        glUniform1f(uniID, 0.5f);
        VAO1.bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.destroy();
    VBO1.destroy();
    EBO1.destroy();
    shaderProgram.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}