#ifndef TFRECT_H
#define TFRECT_H

#include "TFDrawable.h"

typedef unsigned int GLuint;

class TFRect: public TFDrawable{
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
    
    void Erase() override;

private:
    TFRect(toe::core::TOEvector2df position, toe::core::TOEvector2df size, float rotation);
    ~TFRect();

    void p_recalculate_size();
    GLuint m_VBO, m_VAO;
    
};

#endif