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
    void Erase() override;

    void SetRect (float x, float y, float w, float h);
    void SetTextureRect(float x, float y, float w, float h);

    void SetTexture(std::string texture);
    std::string GetTexture() const;

    void ScrollH(float vel);
    void ScrollV(float vel);
    void SetScrollH(float value);
    void SetScrollV(float value);

    void SetMask(std::string mask_path);

    float GetTextureHeight();
    float GetTextureWidth();
    TOEvector2df GetTextureSize();

    float scrollH;
    float scrollV;

private:
    TFSprite(std::string texture, TOEvector2df position, TOEvector2df size);
    ~TFSprite();

    TResourceTexture* 	m_texture;
    TOEvector2df m_texture_size;
    TOEvector4df m_rect;
    TOEvector4df m_mask_rect;
    TResourceTexture* m_mask;
    GLuint m_VAO, m_VBO;
};
#endif