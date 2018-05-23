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
    /**
     * @brief   - Constructor de la clase TResourceMesh
     *              en este inicializamos las variables y creamos los buffers 
     */
    TResourceMesh();

    /**
     * @brief   - Constructor de la clase TResourceMesh 
     *              en este inicializamos las variables, creamos los buffers y cargamos el mesh
     * 
     * @param   - name - Ruta al mesh 
     */
    TResourceMesh(std::string name);

    /**
     * @brief   - Destructor del TResourceMesh en el que se eliminan los buffers 
     */
    ~TResourceMesh();

    /**
     * @brief   - Carga el objeto que se tiene almacenado en el nombre del recurso 
     * 
     * @return  - bool - Si ha cargado correctamente el objeto 
     */
    bool LoadFile();

    /**
     * @brief   - Cambia la textura del recurso 
     * 
     * @param   - texture - Recurso textura que va a utilizar
     */
    void AddTexture(TResourceTexture* texture);

    /**
     * @brief   - Cambia el mapa de normales del recurso 
     * 
     * @param   - texture - Recurso textura con el mapa de normales a utilizar 
     */
    void AddBumpMap(TResourceTexture* texture);
    
    /**
     * @brief   - Cambia el mapa de especulares del recurso 
     * 
     * @param   - texture - Recurso textura con el mapa de especulares a utilizar 
     */
    void AddSpecularMap(TResourceTexture* texture);

    /**
     * @brief   - Cambia el material que va a utilizar el recurso 
     * 
     * @param   - material - Recurso material que va a utilizar el recurso 
     */
    void AddMaterial(TResourceMaterial* material);

    /**
     * @brief   - Guarda el numero de elementos que tiene el recurso 
     * 
     * @param   - value - numero de elementos 
     */
    void SetElementSize(int value);

    /**
     * @brief   - Devuelve el recurso textura del objeto
     *  
     * @return  - TResourceTexture - Textura que utiliza el recurso
     */
    TResourceTexture* GetTexture();

    /**
     * @brief   - Devuelve el recurso del mapa de especulares del objeto 
     * 
     * @return  - TResourceTexture - Mapa de especulares que utilizar el recurso
     */
    TResourceTexture* GetSpecularMap();

    /**
     * @brief   - Devuelve el recurso del mapa de normales del objeto 
     *
     * @return  - TResourceTexture - Mapa de normales que utiliza el recurso
     */
    TResourceTexture* GetBumpMap();

    /**
     * @brief   - Devuelve el recurso del material que utiliza el objeto 
     *
     * @return  - TResourceMaterial - Material que utilizar el objeto 
     */
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
    int m_elementSize;                      // m_elementSize - Numero de elementos que tiene el recurso
    TResourceTexture*   m_basicTexture;     // m_basicTexture - Textura que tiene almacenada el recurso
    TResourceTexture*   m_specularMap;      // m_specularMap - Mapa de especulares que tiene almacenada el recurso
    TResourceTexture*   m_bumpMap;          // m_bumpMap - Mapa de normales que tiene almacenada el recurso
    TResourceMaterial*  m_basicMaterial;    // m_basicMaterial - Material que tiene almacenado el recurso

    GLuint m_vbo;       // m_vbo - BUffer de vertices
    GLuint m_uvbo;      // m_uvbo - Buffer de Uvs
    GLuint m_ebo;       // m_ebo - Buffer de elementos
    GLuint m_nbo;       // m_nbo - Buffer de normales

    glm::vec3 m_size;       // m_size - Tamanyo del objeto
    glm::vec3 m_center;     // m_center - Centro del objeto
};

#endif