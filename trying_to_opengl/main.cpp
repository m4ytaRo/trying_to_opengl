#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n";

int main() {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // These lines tells library GLFW to request to create OpenGL context of version 3.3 (runtime)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //This line tells GLFW to request a Core Profile context, which excludes deprecated OpenGL functionality

    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     //lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   // upper corner

        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,    //inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,     //inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f          //inner down
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

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // configuring the currently bound VAO
    // 0 - means atribute #0 - position (aPos)
    // 3 - number of components representing vertex - vec3 (x, y, z) (for texture it will be vec2 - 2, for color - vec4 - 4 (argb))
    // GL_FLOAT - data type of each component
    // GL_FALSE - should normilize?
    // stride = 3 * 4 bytes = 12 bytes
    // shift for attribute from the beginning of VBO

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // if you place this line before the previous one, nothing will be drawn

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}