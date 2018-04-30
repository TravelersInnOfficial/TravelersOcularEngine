#ifndef TFRECT_H
#define TFRECT_H

#include "TFDrawable.h"

typedef unsigned int GLuint;

class TFRect: public TFDrawable{
    friend class SceneManager;
public:
    void Draw() const override;
    void Erase() override;
    
private:
    TFRect(TOEvector2df position, TOEvector2df size, float rotation);
    ~TFRect();

    GLuint m_VBO;
    
};

#endif