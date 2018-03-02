#ifndef TOCULARENGINE_h
#define TOCULARENGINE_h

#include "VideoDriver.h"

namespace toe{
    //PUBLIC
    VideoDriver* GetVideoDriver();
    TFMesh* AddCube(toe::core::TOEvector3df position = toe::core::TOEvector3df(0,0,0),
                 toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0,0,0),
                 toe::core::TOEvector3df scale = toe::core::TOEvector3df(1,1,1));
                 
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