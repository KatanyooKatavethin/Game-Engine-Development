#include "Mesh.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : vertices(vertices), indices(indices)
{
    setupMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Vertex attributes
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    glEnableVertexAttribArray(1);

    // TexCoord (optional)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::Draw() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Mesh Mesh::CreateCube(float size)
{
    float h = size / 2.0f; 

    std::vector<Vertex> verts = {
        // Front 
        {{-h, -h,  h}, {1, 0, 0}},  
        {{ h, -h,  h}, {0, 1, 0}},  
        {{ h,  h,  h}, {0, 0, 1}},  
        {{-h,  h,  h}, {1, 1, 0}},  

        // Back
        {{-h, -h, -h}, {1, 0, 0}},  
        {{ h, -h, -h}, {0, 1, 0}},  
        {{ h,  h, -h}, {0, 0, 1}},  
        {{-h,  h, -h}, {1, 1, 0}},  
    };

    std::vector<unsigned int> inds = {
        // Front
        0, 1, 2,  2, 3, 0,

        // Right
        1, 5, 6,  6, 2, 1,

        // Back
        5, 4, 7,  7, 6, 5,

        // Left
        4, 0, 3,  3, 7, 4,

        // Top
        3, 2, 6,  6, 7, 3,

        // Bottom
        4, 5, 1,  1, 0, 4
    };

    return Mesh(verts, inds);
}
