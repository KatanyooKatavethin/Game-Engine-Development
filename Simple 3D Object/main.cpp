#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Mesh.hpp"

const char* vertexShaderSource = R"(
#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;

uniform mat4 MVP;
out vec3 vertexColor;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
    vertexColor = aColor;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core 
in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}

)";

unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &source, NULL);
    glCompileShader(shader_id); 

    return shader_id;
}

unsigned int createShaderProgram()
{
    unsigned int vertexShader_id = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader_id = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader_id);
    glAttachShader(shaderProgram, fragmentShader_id);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader_id);
    glDeleteShader(fragmentShader_id);

    return shaderProgram;
}

using namespace std;

int main(void)
{
    float X = 0.0f;
    float Y = 0.0f;

    GLFWwindow* window;

    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    unsigned int shaderProgram = createShaderProgram();

    glEnable(GL_DEPTH_TEST); 

    Mesh cube = Mesh::CreateCube(1.0f);

    while (!glfwWindowShouldClose(window))
    {
        const float rotationSpeed = 0.1f;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            X -= rotationSpeed;

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            X += rotationSpeed;

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            Y -= rotationSpeed;

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            Y += rotationSpeed;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(X), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(Y), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);
        glm::mat4 MVP = projection * view * model;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        int mvpLoc = glGetUniformLocation(shaderProgram, "MVP");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));

        cube.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}