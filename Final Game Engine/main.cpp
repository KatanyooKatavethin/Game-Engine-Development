#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <miniaudio.h>
#include <fstream>     

#include "thirdparty\nlohmann - json\single_include\nlohmann/json.hpp"      
using json = nlohmann::json;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "SoundManager.hpp"
#include <iostream>

using namespace std;

const char* vertexShaderSource = R"(
#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 atexCoord;
layout (location=3) in vec3 aNormal;

out vec3 vertexColor;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform float size;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  vec4 worldPos = model * vec4(aPos.x*size, aPos.y*size, aPos.z*size, 1.0);
  fragPos = vec3(worldPos);
  gl_Position = projection * view * worldPos;
  vertexColor = aColor;
  texCoord = atexCoord;
  normal = normalize(aNormal);
}

)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform sampler2D mytexture; 
uniform float ambientIntensity;

uniform vec3 lightPos;

vec3 finalLight;
vec3 lightColor;

void main()
{

  lightColor.r = 1.0;
  lightColor.g = 1.0;
  lightColor.b = 1.0;
  
  vec3 lightDirection = normalize(lightPos-fragPos) ;
  float diff = max(dot(normal, lightDirection), 0.0);
  vec3 diffLight = diff * lightColor;

  vec3 ambientLignt = ambientIntensity * lightColor;

  finalLight = ambientLignt + diff;
  FragColor = vec4(finalLight, 1.0) * texture(mytexture, texCoord);
}
)";

unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &source, NULL); 
    glCompileShader(shader_id); 


    int success;
    char infoLog[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
        std::cout << "ERROR : " << infoLog << std::endl;
    }

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

bool loadConfig(const std::string& filepath, json& outConfig) 
{
    std::ifstream file(filepath);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open config.json: " << filepath << std::endl;
        return false;
    }
    file >> outConfig;
    return true;
}

int main(void)
{
    json config;
    if (!loadConfig("config.json", config)) return -1;

    int windowWidth = config.value("windowWidth", 1000);
    int windowHeight = config.value("windowHeight", 800);
    float ambientIntensity = config.value("ambientIntensity", 0.5f);

    std::vector<float> camPosVec = config["cameraPosition"];
    std::vector<float> camCenterVec = config["cameraTarget"];
    std::vector<float> objPosVec = config["objectPosition"];
    std::vector<float> objRotVec = config["objectRotation"];

    glm::vec3 cam_position(camPosVec[0], camPosVec[1], camPosVec[2]);
    glm::vec3 cam_center(camCenterVec[0], camCenterVec[1], camCenterVec[2]);
    glm::vec3 position(objPosVec[0], objPosVec[1], objPosVec[2]);
    glm::vec3 rotation(objRotVec[0], objRotVec[1], objRotVec[2]);
    float size = config.value("objectSize", 1.0f);

    std::string texturePath = config.value("texturePath", "assets/AVGN.png");
    std::string musicPath = config.value("musicPath", "assets/default.mp3");

    TK::SoundManager soundManager;
    if (soundManager.init() < 0)
    {
        std::cout << "Sound init is unsuccessful";
        return -1;
    }
    soundManager.playMusic(musicPath.c_str());

    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Game Engine", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_DEPTH_TEST);

    // Load Texture
    stbi_set_flip_vertically_on_load(true);
    int texW, texH, texChannels;
    unsigned char* data = stbi_load(texturePath.c_str(), &texW, &texH, &texChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        return -1;
    }
   
    unsigned int textureID1;
    glGenTextures(1, &textureID1);
    glBindTexture(GL_TEXTURE_2D, textureID1);

    // set texture warping and filtering option
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);


    float vertices[] = {
       //Front
       // positions          // colors           // texture coords  // normal vector
      -0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,        0.0f, 0.0f, 1.0f,
       0.5f, -0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,        0.0f, 0.0f, 1.0f,
       0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,        0.0f, 0.0f, 1.0f,
      -0.5f,  0.5f, 0.5f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f,        0.0f, 0.0f, 1.0f,

       //Back
       // positions          // colors           // texture coords  // normal vector
      -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,        0.0f, 0.0f, 1.0f,
       0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,        0.0f, 0.0f, 1.0f,
       0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,        0.0f, 0.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,        0.0f, 0.0f, 1.0f,

        //Left
       // positions          // colors           // texture coords  // normal vector
      -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,       -1.0f, 0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,       -1.0f, 0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,       -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,       -1.0f, 0.0f, 0.0f,

        //Right
       // positions          // colors           // texture coords  // normal vector
       0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,        1.0f, 0.0f, 0.0f,
       0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,        1.0f, 0.0f, 0.0f,
       0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,        1.0f, 0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,        1.0f, 0.0f, 0.0f,

       //Top
      // positions          // colors           // texture coords  // normal vector
      -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,        0.0f, 1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,        0.0f, 1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,        0.0f, 1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,        0.0f, 1.0f, 0.0f,

       //Bottom
      // positions          // colors           // texture coords  // normal vector
      -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,        0.0f, -1.0f, 0.0f,
       0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,        0.0f, -1.0f, 0.0f,
       0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,        0.0f, -1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,        0.0f, -1.0f, 0.0f
    };

    unsigned int indices[] = {
      // Front
      0, 1, 2,     2, 3, 0,

      // Back
      4, 5, 6,     6, 7, 4,

      // Left
      8, 9,10,    10,11, 8,

      // Right
      12,13,14,   14,15,12,

      // Top
      16,17,18,   18,19,16,

      // Bottom
      20,21,22,   22,23,20
    };

    unsigned int VAO, VBO, VEO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VEO);

    glBindVertexArray(VAO); 

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);   

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Postion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)0);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture Coord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    unsigned int shaderProgram = createShaderProgram();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          
    ImGui_ImplOpenGL3_Init();

    glm::vec3 lightPos(3.0f, 3.0f, 3.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glfwPollEvents();


        glUseProgram(shaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID1); 

        glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));


        glm::mat4 view = glm::lookAt(
            cam_position,
            cam_center,
            glm::vec3(0.0f, 1.0f, 0.0f));

        float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1,
            GL_FALSE,
            glm::value_ptr(model));

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1,
            GL_FALSE,
            glm::value_ptr(view));

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1,
            GL_FALSE,
            glm::value_ptr(projection));

        glUniform1i(glGetUniformLocation(shaderProgram, "mytexture"), 0);

        glUniform1f(glGetUniformLocation(shaderProgram, "ambientIntensity"), ambientIntensity);

        glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));

        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Inspector");
        ImGui::Text("Transform");
        ImGui::DragFloat3("Position (X, Y, Z)", &position.x, 0.1f);
        ImGui::DragFloat3("Rotation (X, Y, Z)", &rotation.x, 1.0f);
        ImGui::SliderFloat("Size", &size, 0.1f, 3.0f);
        ImGui::DragFloat3("Camera Position", &cam_position.x, 0.1f);
        ImGui::DragFloat3("Camera Center", &cam_center.x, 0.1f);

        ImGui::Spacing();
        ImGui::DragFloat3("light Position", &lightPos.x, -0.1f, 0.1f);
        ImGui::SliderFloat("Ambient Intensity", &ambientIntensity, 0.0f, 1.0f);
        ImGui::Spacing();

        static bool songPlaying = true;
        static float volume = 1.0f;

        ImGui::Text("Music");

        if (ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f)) 
        {
            soundManager.setVolume(volume);
        }

        if (songPlaying) 
        {
            if (ImGui::Button("Pause")) {
                soundManager.pauseMusic();
                songPlaying = false;
            }
        }
        else 
        {
            if (ImGui::Button("Resume")) {
                soundManager.resumeMusic();
                songPlaying = true;
            }
        }

        if (ImGui::Button("Stop")) {
            soundManager.stopMusic();
            songPlaying = false;
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    stbi_image_free(data);

    return 0;
}