#ifndef TFRECT_H
#define TFRECT_H

#include "TFDrawable.h"

class TFRect: public TFDrawable{
public:
    TFRect(toe::core::TOEvector2df position = toe::core::TOEvector2df(0,0));
    ~TFRect();
    void Draw() const override;

private:

};

#endif