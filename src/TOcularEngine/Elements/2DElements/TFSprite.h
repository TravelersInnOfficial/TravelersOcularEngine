#ifndef TFSPRITE_H
#define TFSPRITE_H

#include "TFDrawable.h"

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

    void SetTexture(std::string texture) override;

    void Erase() override;

    void ToBkg() override;
    void ToFront() override;

    void ScrollH(float vel);
    void ScrollV(float vel);

    void SetMask(std::string mask_path);

    float scrollH;
    float scrollV;

private:
    TFSprite(std::string texture, toe::core::TOEvector2df position, toe::core::TOEvector2df size);
    ~TFSprite();

    void p_recalculate_size();
    TResourceTexture* 	m_texture;
    TResourceTexture* m_mask;
    GLuint m_VAO, m_VBO;
};
#endif