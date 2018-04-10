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
    std::string texture = "";
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

    virtual void SetColor(float r, float g, float b, float a = 1.0f) {  m_color.SetR(r);
                                                                        m_color.SetG(g);
                                                                        m_color.SetB(b);
                                                                        m_color.SetA(a);}

    virtual void SetRed(float r) {m_color.SetR(r);}
    virtual void SetGreen(float g) {m_color.SetG(g);}
    virtual void SetBlue(float b) {m_color.SetB(b);}
    virtual void SetAlpha(float a) {m_color.SetA(a);}

    virtual void Erase() = 0;

    virtual void ToBkg() = 0;
    virtual void ToFront() = 0;

    virtual void SetTexture(std::string texture_path) = 0;
    virtual std::string GetTexture() const {return m_InData.texture;}

protected:
    toe::core::TOEvector2df m_position;
    toe::core::TOEvector2df m_size;
    float m_rotation = 0.0;
    TColor m_color;

    SHADERTYPE m_program = TWOD_SHADER;
    toe::core::TOEvector2di w_dims;
    RectData m_InData;
};
#endif