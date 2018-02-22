#ifndef TOCULARENGINE_h
#define TOCULARENGINE_h

#include <vector>

#include "./Elements/TFCamera.h"
#include "./Elements/TFLight.h"
#include "./Elements/TFMesh.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./../TResourceManager.h"
#include "./../Resources/TResourceMesh.h"

namespace toe{
    //PUBLIC
    namespace scene{
        TFCamera*   AddCamera(vector3df position, vector3df rotation, bool perspective);
        TFLight*    AddLight(vector3df position, vector3df rotation, vector4df color, float intensity);
        TFMesh*     AddMesh(vector3df position, vector3df rotation, vector3df scale, std::string meshPath);
        void        DeleteCamera(TFCamera*);
        void        DeleteLight(TFLight*);
        void        DeleteMesh(TFMesh*);
    };

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
        float       GetTime();
    }


    void BeginScene();
    void Run();
    void EndScene();
    void Drop();

    //DRAW FUNCTIONS
    
    //PRIVATE
    namespace{
        float m_time = 0;
        std::vector<TFCamera*> m_cameras;
        std::vector<TFLight*> m_lights;
    };

    // TODO:: GUARDARSE TODOS LOS PUNTEROS A NODOS QUE CONTIENEN LUCES Y CAMARAS
    //- Metodos para el registro y manejo de viewports
    //- Metodos para el registro y manejo de camaras
    //- Metodos para el registro y manejo de luces
};

#endif