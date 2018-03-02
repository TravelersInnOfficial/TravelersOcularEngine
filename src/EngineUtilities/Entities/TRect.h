#ifndef TRECT_H
#define TRECT_H

#include "TEntity.h"
#include "./../Resources/TResourceTexture.h"
#include "../Resources/Program.h"
#include <TOEvector2d.h>
#include <TOEvector4d.h>

class TRect : public TEntity{
    public:
    TRect(  toe::core::TOEvector2df size, 
            std::string texture = "",
            toe::core::TOEvector2df position = toe::core::TOEvector2df(0,0) 
            );
    ~TRect();
    
    static void SetColor(toe::core::TOEvector4df color);
    static void LoadTexture(std::string path);

    void BeginDraw() override;
    void EndDraw() override;

    private:
    void SendShaderData();

    static TResourceTexture* m_texture;
    static toe::core::TOEvector4df m_color;
    static int m_size;
	static GLuint m_uvbo;
	static GLuint m_vbo;
};

#endif