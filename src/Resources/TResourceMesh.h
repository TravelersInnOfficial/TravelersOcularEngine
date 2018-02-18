#ifndef TRESOURCEMESH_H
#define TRESOURCEMESH_H

#include "TResource.h"
#include "TResourceTexture.h"

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

    void AddTexture(TResourceTexture* texture);
    void SetElementSize(int value);
    TResourceTexture* GetTexture();

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

private:
    int m_elementSize;
    TResourceTexture* m_basicTexture;

    GLuint m_vbo;
    GLuint m_uvbo;
    GLuint m_ebo;
    GLuint m_nbo;  
};

#endif