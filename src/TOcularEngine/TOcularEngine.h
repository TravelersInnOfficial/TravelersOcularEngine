#ifndef TOCULARENGINE_h
#define TOCULARENGINE_h

/**
 * @brief Main file to include. Has all needed for the Engine Fachade. 
 * 
 * @file TOcularEngine.h
 */

#include "VideoDriver.h"

namespace toe{
    /**
     * @brief   - Devuelve el VideoDriver que es singleton
     */
    VideoDriver* GetVideoDriver();

    /**
     * @brief   - Devuelve el SceneManager que es singleton 
     */
    SceneManager* GetSceneManager();

    /**
     * @brief   - Anyade un cube a la escena 
     * 
     * @param   - position - Posicion del cubo
     * @param   - rotation - Rotacion del cubo
     * @param   - scale - Tamanyo del cubo
     * @return  - TFMesh - Cubo creado
     */
    TFMesh* AddCube(TOEvector3df position = TOEvector3df(0,0,0),
                 TOEvector3df rotation = TOEvector3df(0,0,0),
                 TOEvector3df scale = TOEvector3df(1,1,1));

    /**
     * @brief   - Anyade una esfera a la escena 
     * 
     * @param   - position - Posicion de la esfera
     * @param   - rotation - Rotacion de la esfera
     * @param   - scale - Tamanyo de la esfera
     * @return  - TFMesh - Esfera creada
     */
    TFMesh* AddSphere(TOEvector3df position = TOEvector3df(0,0,0),
                 TOEvector3df rotation = TOEvector3df(0,0,0),
                 TOEvector3df scale = TOEvector3df(1,1,1));

    /**
     * @brief   - Anyade un rectangulo 2D a la escena 
     * 
     * @param   - position - Posicion del rectangulo 
     * @param   - size - Tamanyo del rectangulo
     * @param   - rotation - Rotacion del rectangulo
     * @return  - TFRect - Rectangulo creado
     */
    TFRect* Add2DRect(TOEvector2df position = TOEvector2df(0.0f),
                 TOEvector2df size = TOEvector2df(10,10),
                 float rotation = 0.0f);

    /**
     * @brief   - Anyade un texto 2D a la escena
     *  
     * @param   - text - Cadena a mostrar
     * @param   - position - Posicion del texto
     * @return  - TF2DTexto - Texto 2D creado
     */
    TF2DText* Add2DText(std::string text = "",
                 TOEvector2df position = TOEvector2df(0.0f,0.0f));

    /**
     * @brief   - Anyade un Sprite a la escena 
     * 
     * @param   - texture - Ruta a la textura a mostrar
     * @param   - position - Posicion del SPrite
     * @param   - size - Tamanyo del Sprite
     * @return  - TFSprite - Sprite creado
     */
    TFSprite* AddSprite(std::string texture = "", TOEvector2df position = TOEvector2df(0,0), TOEvector2df size = TOEvector2df(10,10));

    /**
     * @brief   - Carga un mesh 
     * 
     * @param   - path - Ruta del mesh 
     */
    void LoadMesh(std::string path);

    /**
     * @brief   - Carga una textura 
     * 
     * @param   - path - Ruta de la textura 
     */
    void LoadTexture(std::string path);

    /**
     * @brief   - Elimina una textura 
     * 
     * @param   - path - Ruta de la textura a eliminar 
     */
    void UnloadTexture(std::string path);

    /**
     * @brief   - Consigue el puntero de Opengl de una textura 
     * 
     * @param   - path - Ruta de la textura 
     */
    GLuint GetTextureID(std::string path);

    /**
     * @brief   - Consigue las dimensiones de una textura 
     * 
     * @param   - path - Ruta de la textura a la que conseguir la textura 
     */
    TOEvector2di GetTextureDims(std::string path);

    /**
     * @brief   - Consigue el ancho de una textura 
     * 
     * @param   - path - Ruta de la textura de la que conseguir el ancho 
     */
    int GetTextureWidth(std::string path);

    /**
     * @brief   - Consigue el alto de una textura 
     * 
     * @param   - path - Ruta de la textura de la que conseguir el alto 
     */
    int GetTextureHeight(std::string path);

    /**
     * @brief   - Clase creada para poder almacenar la posicion y tamanyo de un rectangulo
     */
    namespace core{ 
        class rect{
            public:
                rect(float x, float y, float w, float h){ m_x = x; m_y = y; m_w = w; m_h = h;};
                ~rect();

            private:

            float m_x = 0.0f;
            float m_y = 0.0f;
            float m_w = 0.0f;
            float m_h = 0.0f;
        };

       
    }

    namespace{
        VideoDriver* privateVideoDriver;
        SceneManager* privateSceneManager;
        IODriver* privateIOManager;
    }
};

#endif