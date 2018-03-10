#ifndef TFDRAWABLE_H
#define TFDRAWABLE_H

#include <TOEvector2d.h>
#include <ShaderTypes.h>
#include <TColor.h>
#include <cmath>  

struct RectData{
    toe::core::TOEvector2df position;
    toe::core::TOEvector2df size;
    float rotation;
};

class TFDrawable{
public:
    virtual ~TFDrawable(){}
    virtual void Draw() const = 0;
    
    virtual toe::core::TOEvector2df GetPosition() const {return m_InData.position;}
    virtual float GetPosX() const {return m_InData.position.X;}
    virtual float GetPosY() const {return m_InData.position.Y;}

    virtual toe::core::TOEvector2df GetSize() const {return m_InData.size;}
    virtual float GetWidth() const {return m_InData.size.X;}
    virtual float GetHeight() const {return m_InData.size.Y;}

    virtual void SetPosition(float x, float y) = 0;
    virtual void SetPosX(float x) = 0;
    virtual void SetPosY(float y) = 0;

    virtual void SetSize(float w, float h) = 0;
    virtual void SetWidth(float w) = 0;
    virtual void SetHeight(float h) = 0;

    virtual void Rotate(float deg) = 0;
    virtual void SetRotation(float deg) = 0;


protected:
    toe::core::TOEvector2df m_position = toe::core::TOEvector2df(0,0);
    toe::core::TOEvector2df m_size = toe::core::TOEvector2df(0,0);
    float m_rotation = 0.0f;
    TColor m_color = TColor();

    SHADERTYPE m_program = TWOD_SHADER;
    toe::core::TOEvector2di w_dims;
    RectData m_InData;
};
#endif