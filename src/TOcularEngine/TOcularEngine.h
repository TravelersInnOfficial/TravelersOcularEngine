#ifndef TOCULARENGINE_h
#define TOCULARENGINE_h

#include "VideoDriver.h"

namespace toe{
    //PUBLIC
    VideoDriver* GetVideoDriver();

    SceneManager* GetSceneManager();

    TFMesh* AddCube(toe::core::TOEvector3df position = toe::core::TOEvector3df(0,0,0),
                 toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0,0,0),
                 toe::core::TOEvector3df scale = toe::core::TOEvector3df(1,1,1));

    TFMesh* AddSphere(toe::core::TOEvector3df position = toe::core::TOEvector3df(0,0,0),
                 toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0,0,0),
                 toe::core::TOEvector3df scale = toe::core::TOEvector3df(1,1,1));

    void LoadMesh(std::string path);
    void LoadTexture(std::string path);

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

        void Draw2DRect(float color ,toe::core::rect );
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