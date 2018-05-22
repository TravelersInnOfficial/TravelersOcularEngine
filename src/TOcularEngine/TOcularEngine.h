#ifndef TOCULARENGINE_h
#define TOCULARENGINE_h

#include "VideoDriver.h"

namespace toe{
    //PUBLIC
    VideoDriver* GetVideoDriver();

    SceneManager* GetSceneManager();

    TFMesh* AddCube(TOEvector3df position = TOEvector3df(0,0,0),
                 TOEvector3df rotation = TOEvector3df(0,0,0),
                 TOEvector3df scale = TOEvector3df(1,1,1));

    TFMesh* AddSphere(TOEvector3df position = TOEvector3df(0,0,0),
                 TOEvector3df rotation = TOEvector3df(0,0,0),
                 TOEvector3df scale = TOEvector3df(1,1,1));

    TFRect* Add2DRect(TOEvector2df position = TOEvector2df(0.0f),
                 TOEvector2df size = TOEvector2df(10,10),
                 float rotation = 0.0f);

    TF2DText* Add2DText(std::string text = "",
                 TOEvector2df position = TOEvector2df(0.0f,0.0f));

    TFSprite* AddSprite(std::string texture = "", TOEvector2df position = TOEvector2df(0,0), TOEvector2df size = TOEvector2df(10,10));

    void LoadMesh(std::string path);
    void LoadTexture(std::string path);
    void UnloadTexture(std::string path);
    GLuint GetTextureID(std::string path);
    TOEvector2di GetTextureDims(std::string path);
    int GetTextureWidth(std::string path);
    int GetTextureHeight(std::string path);

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

    // TODO:: GUARDARSE TODOS LOS PUNTEROS A NODOS QUE CONTIENEN LUCES Y CAMARAS
    //- Metodos para el registro y manejo de viewports
    //- Metodos para el registro y manejo de camaras
    //- Metodos para el registro y manejo de luces
};

#endif