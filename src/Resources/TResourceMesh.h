#ifndef TRESOURCEMESH_H
#define TRESOURCEMESH_H

#include "TResource.h"

#include <glm/gtc/type_ptr.hpp>
#include <vector>

class TResourceMesh: public TResource {

public:
    TResourceMesh();
    TResourceMesh(std::string name);
    ~TResourceMesh();

    /**************************************************************************
	 * @brief Loads the mesh passed
     **************************************************************************/  
    bool LoadFile();

    std::vector<glm::vec3>* GetVertexVector();
    std::vector<glm::vec2>* GetUvVector();
    std::vector<glm::vec3>* GetNormalVector();

    void AddVertex(glm::vec3 vertex);
    void AddUv(glm::vec2 uv);
    void AddNormal(glm::vec3 normal);
    void AddVertexIndex(unsigned int index);

    void ClearVertex();
    void ClearUv();
    void ClearNormal();
    void ClearVertexIndex();

    /**************************************************************************
     * @brief Devuelve un puntero al buffer de vertices
     **************************************************************************/  
    GLuint* GetVertexBuffer();

    /**************************************************************************
     * @brief Devuelve un puntero al buffer de elementos
     **************************************************************************/  
    GLuint* GetElementBuffer();
    GLuint* GetUvBuffer();
    GLuint* GetNormalBuffer();
    /**************************************************************************
     * @brief Devuelve el numero de Vertices que tiene el modelo
     **************************************************************************/  
    int GetVertexSize();

private:
    std::vector<glm::vec3> m_vertex;
    std::vector<glm::vec2> m_textures;
    std::vector<glm::vec3> m_normals;
    std::vector<unsigned int> m_vertexIndex;

    GLuint m_vbo;
    GLuint m_uvbo;
    GLuint m_ebo;
    GLuint m_nbo;
    
};

#endif