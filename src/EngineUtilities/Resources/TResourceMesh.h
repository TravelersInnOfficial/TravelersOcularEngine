#ifndef TRESOURCEMESH_H
#define TRESOURCEMESH_H

#include "TResource.h"
#include "TResourceTexture.h"
#include "TResourceMaterial.h"
#include <vector>
#include <glm/vec3.hpp>

typedef unsigned int GLuint;

class TResourceMesh: public TResource {

public:
    TResourceMesh();
    TResourceMesh(std::string name);
    ~TResourceMesh();

    /**************************************************************************
	 * @brief Loads the mesh passed
     **************************************************************************/  
    bool LoadFile();

    void AddTexture(TResourceTexture* texture);
    void AddMaterial(TResourceMaterial* material);
    void SetElementSize(int value);
    TResourceTexture* GetTexture();
    TResourceMaterial* GetMaterial();

// =====================================================================================================
//
//  BUFFERS
//
// ===================================================================================================== 
    
    /**************************************************************************
     * @brief Devuelve un puntero al buffer de vertices
     **************************************************************************/  
    GLuint GetVertexBuffer();

    /**************************************************************************
     * @brief Devuelve un puntero al buffer de elementos
     **************************************************************************/  
    GLuint GetElementBuffer();

    /**************************************************************************
     * @brief Devuelve un puntero al buffer de uv
     **************************************************************************/  
    GLuint GetUvBuffer();

    /**************************************************************************
     * @brief Devuelve un puntero al buffer de normales
     **************************************************************************/  
    GLuint GetNormalBuffer();

    /**************************************************************************
     * @brief Devuelve el numero de Vertices que tiene el modelo
     **************************************************************************/  
    int GetElementSize();

    /**************************************************************************
     * @brief Devuelve el array de Vertices que tiene el modelo
     **************************************************************************/  
    std::vector<glm::vec3> GetVerticesArray();

private:
    int m_elementSize;
    TResourceTexture*   m_basicTexture;
    TResourceMaterial*  m_basicMaterial;

    GLuint m_vbo;
    GLuint m_uvbo;
    GLuint m_ebo;
    GLuint m_nbo;

    std::vector<glm::vec3> m_vertices;
};

#endif