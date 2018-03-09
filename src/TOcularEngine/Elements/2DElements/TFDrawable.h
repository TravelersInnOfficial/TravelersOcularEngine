#ifndef TFDRAWABLE_H
#define TFDRAWABLE_H

#include <TOEvector2d.h>
#include <ShaderTypes.h>
#include <TColor.h>

class TFDrawable{
public:
    virtual ~TFDrawable(){}
    virtual void Draw() const = 0;

protected:
    toe::core::TOEvector2df m_position = toe::core::TOEvector2df(0,0);
    toe::core::TOEvector2df m_size = toe::core::TOEvector2df(0,0);
    float m_rotation = 0.0f;
    TColor m_color = TColor();

    SHADERTYPE m_program = TWOD_SHADER;
    toe::core::TOEvector2di w_dims;
};
#endif