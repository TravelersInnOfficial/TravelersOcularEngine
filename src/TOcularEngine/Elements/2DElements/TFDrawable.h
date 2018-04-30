#ifndef TFDRAWABLE_H
#define TFDRAWABLE_H

#include <TOEvector2d.h>
#include <ShaderTypes.h>
#include <TColor.h>
#include <cmath>  

struct RectData{
    TOEvector2df position;
    TOEvector2df size;
    std::string texture = "";
};

class TFDrawable{
public:
    virtual ~TFDrawable(){}
    virtual void Draw() const = 0;
    
    virtual TOEvector2df GetPosition() const;
    virtual float GetPosX() const;
    virtual float GetPosY() const;

    virtual TOEvector2df GetSize() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual void SetRotation(float rot);
    virtual void SetPosition(float x, float y);
    virtual void SetPosX(float x);
    virtual void SetPosY(float y);

    virtual void SetSize(float w, float h);
    virtual void SetWidth(float w);
    virtual void SetHeight(float h);

    virtual void SetColor(float r, float g, float b, float a = 1.0f);

    virtual void SetRed(float r);
    virtual void SetGreen(float g);
    virtual void SetBlue(float b);
    virtual void SetAlpha(float a);

    virtual void Erase() = 0;

    virtual void ToBkg();
    virtual void ToFront();

protected:
    TOEvector2df m_position;
    TOEvector2df m_size;
    float m_rotation;
    TColor m_color;

    SHADERTYPE m_program = TWOD_SHADER;
    TOEvector2di w_dims;
    RectData m_InData;
};
#endif