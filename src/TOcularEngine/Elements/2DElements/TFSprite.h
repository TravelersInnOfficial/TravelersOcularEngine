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
    void SetRect (float x, float y, float w, float h);

    void SetTexture(std::string texture) override;

    void Erase() override;

    void ToBkg() override;
    void ToFront() override;

    void ScrollH(float vel);
    void ScrollV(float vel);

    void SetMask(std::string mask_path);

    float GetTextureHeight();
    float GetTextureWidth();
    toe::core::TOEvector2df GetTextureSize();

    float scrollH;
    float scrollV;

private:
    TFSprite(std::string texture, toe::core::TOEvector2df position, toe::core::TOEvector2df size);
    ~TFSprite();

    void p_recalculate_size();
    TResourceTexture* 	m_texture;
    toe::core::TOEvector2df m_texture_size;
    toe::core::TOEvector4df m_rect;
    toe::core::TOEvector4df m_mask_rect;
    TResourceTexture* m_mask;
    GLuint m_VAO, m_VBO;
};
#endif