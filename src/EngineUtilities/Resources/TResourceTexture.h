#ifndef TRESOURCETEXTURE_H
#define TRESOURCETEXTURE_H

/**
 * @brief Texture Resource containing all pixels info.
 * 
 * @file TResourceTexture.h
 */

#include "TResource.h"
#include <vector>

// Forward declaration
typedef unsigned int GLuint;

class TResourceTexture: public TResource {

public:
    /**
     * @brief   - Constructor de la textura donde inicializamos los valores y cargamos la textura 
     * 
     * @param   - name - Ruta a la textura 
     */
    TResourceTexture(std::string name);

    /**
     * @brief   - Destructor de la textura, vaciamos y elminamos los buffers 
     */
    ~TResourceTexture();

    /**
     * @brief   - Carga la textura a traves del nombre almacenado en la clase 
     * 
     * @return  - bool - Se ha cargador correctamente el archivo 
     */
    bool LoadFile();

    /**
     * @brief   - Devuelve un puntero a la textura 
     *
     * @return  - GLuint - Puntero de la textura 
     */
    GLuint GetTextureId();

    /**
     * @brief   - Devuelve el ancho de la imagen 
     *
     * @return  - int - Ancho de la imagen
     */
    int GetWidth();

    /**
     * @brief   - Devuelve el alto de la imagen 
     *
     * @return  - int - Alto de la imagen 
     */
    int GetHeight();

    /**
     * @brief   ⁻ Devuelve la ruta a la textura     
     * 
     * @return  - std::string - Ruta de la textura 
     */
    std::string GetTexturePath();
    
private:
    unsigned char* m_imageData; // m_imageData - Datos de la imagen
    int m_width;                // m_width - Ancho de la imagen    
    int m_height;               // m_height - Alto de la imagen
    bool m_loaded;              // m_loaded - Ha cargado correctamente el recurso
    GLuint m_textureID;         // m_textureID - Puntero a la imagen

};

#endif