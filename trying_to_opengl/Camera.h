#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#define GLM_ENABLE_EXPERIMENTAL

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{

public:
    const float DEF_SPEED = 0.001f;

    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    // right because we use Right-Hand Grip Rule: rotating from orientation vector to up vector

    int width;
    int height;

    bool firstClick = true;

    float speed = 0.001f;
    float sensitivity = 100.0f;

    Camera(int width, int height, glm::vec3 position) : width(width), height(height), position(position) {};

    void matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
    void registerInputs(GLFWwindow* window);

};

#endif