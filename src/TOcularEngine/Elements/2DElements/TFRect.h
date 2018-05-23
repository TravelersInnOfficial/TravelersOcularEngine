#ifndef TFRECT_H
#define TFRECT_H

/**
 * @brief Draws a rectangle in screen.
 * 
 * @file TFRect.h
 */

#include "TFDrawable.h"
#include <TOEvector4d.h>

typedef unsigned int GLuint;
class TResourceTexture; 

class TFRect: public TFDrawable{
    friend class SceneManager;
public:
    void Draw() const override;
    void Erase() override;
    
    void SetMask(std::string mask_path);
    void SetWidth(float w) override;
    void SetHeight(float h) override;
    
private:
    TFRect(TOEvector2df position, TOEvector2df size, float rotation);
    ~TFRect();

    GLuint m_VBO;
    TOEvector2df m_mask_size;
    TOEvector4df m_mask_rect;
    TResourceTexture* m_mask;
};

#endif