#ifndef TFDRAWABLE_H
#define TFDRAWABLE_H

#include <TOEvector2d.h>

class TFDrawable{
public:
    virtual ~TFDrawable(){}
    virtual void Draw() const = 0;

protected:
    toe::core::TOEvector2df m_position = toe::core::TOEvector2df(0,0);

};
#endif