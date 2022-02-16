//
// Created by egor on 2/16/22.
//

#ifndef AZATHOTH_BASICMESH_HPP
#define AZATHOTH_BASICMESH_HPP

#include <string>
#include <glm/glm.hpp>
#include <memory>

#include "Renderer/IVertexBuffer.hpp"
#include "Renderer/IIndexBuffer.hpp"
#include "Texture/Texture.h"

struct Vertex3dUVNormal
{
    glm::vec3 m_position;
    glm::vec2 m_texCoord;
    glm::vec3 m_normal;

    Vertex3dUVNormal(glm::vec3 position, glm::vec2 texCoord, glm::vec3 normal) {
        m_position = position;
        m_texCoord = texCoord;
        m_normal = normal;
    }
    Vertex3dUVNormal() {}
};

class Mesh {
public:
    Mesh(std::vector<Vertex3dUVNormal> vertices, std::vector<unsigned short> indices);
    Mesh(std::string filePath);
    ~Mesh();
    void Draw();
private:
    std::vector<Vertex3dUVNormal> m_vertices;
    std::vector<unsigned short> m_indices;
    unsigned int m_vertexBuffer;
    unsigned int m_indexBuffer;
};


#endif