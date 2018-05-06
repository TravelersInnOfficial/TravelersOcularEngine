#ifndef TFRECT_H
#define TFRECT_H

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
private:
    TFRect(TOEvector2df position, TOEvector2df size, float rotation);
    ~TFRect();

    GLuint m_VBO;
    TOEvector4df m_mask_rect;
    TResourceTexture* m_mask;
};

#endif