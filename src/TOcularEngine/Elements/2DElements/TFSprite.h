#ifndef TFSPRITE_H
#define TFSPRITE_H

#include "TFDrawable.h"
#include <TOEvector4d.h>
//FAST FORWARD DECLARATION
class TResourceTexture;
typedef unsigned int GLuint;

class TFSprite : public TFDrawable{
    friend class SceneManager;
public:
    void Draw() const override;
    
    void SetPosition(float x, float y) override;                       
    void SetPosX(float x) override;
    void SetPosY(float y) override;

    void SetSize(float w, float h) override;                  
    void SetWidth(float w) override; 
    void SetHeight(float h) override; 

    void Rotate(float deg) override;
    void SetRotation(float deg) override;

private:
    TFSprite(std::string texture, toe::core::TOEvector2df position, toe::core::TOEvector2df size = toe::core::TOEvector2df(0,0));
    ~TFSprite();

    TResourceTexture* 	m_texture;
    GLuint m_VAO, m_VBO;
};
#endif