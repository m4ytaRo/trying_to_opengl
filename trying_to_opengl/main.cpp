#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

int main() {

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 800;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // These lines tells library GLFW to request to create OpenGL context of version 3.3 (runtime)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //This line tells GLFW to request a Core Profile context, which excludes deprecated OpenGL functionality

    GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
         0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
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
    EBO1.loadData(indices, sizeof(indices));

    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.linkAttrib(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    VAO1.unbind();
    VBO1.unbind();
    EBO1.unbind();
    
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    Texture texWater("bricks16x.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    texWater.texUnit(shaderProgram, "tex0", 0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.activate();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        glUniform1f(uniID, 0.0f);
        texWater.bind();
        VAO1.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO1.destroy();
    VBO1.destroy();
    EBO1.destroy();
    shaderProgram.destroy();
    texWater.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}