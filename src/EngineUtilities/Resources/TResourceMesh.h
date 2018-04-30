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
    void AddSpecularMap(TResourceTexture* texture);
    void AddMaterial(TResourceMaterial* material);
    void SetElementSize(int value);
    TResourceTexture* GetTexture();
    TResourceTexture* GetSpecularMap();
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
     * @brief Guarda el size del modelo
     **************************************************************************/  
    void SetSize(glm::vec3 size);

    /**************************************************************************
     * @brief Guarda el centro del modelo
     **************************************************************************/  
    void SetCenter(glm::vec3 center);

    /**************************************************************************
     * @brief Devuelve el size del modelo
     **************************************************************************/  
    glm::vec3 GetSize();

    /**************************************************************************
     * @brief Devuelve el centro del modelo
     **************************************************************************/  
    glm::vec3 GetCenter();

private:
    int m_elementSize;
    TResourceTexture*   m_basicTexture;
    TResourceTexture*   m_specularMap;
    TResourceMaterial*  m_basicMaterial;

    GLuint m_vbo;
    GLuint m_uvbo;
    GLuint m_ebo;
    GLuint m_nbo;

    glm::vec3 m_size;
    glm::vec3 m_center;
};

#endif