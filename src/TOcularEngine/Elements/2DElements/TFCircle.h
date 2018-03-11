#ifndef TFCircle_H
#define TFCircle_H

#include "TFDrawable.h"

class TFCircle: public TFDrawable{
public:
    TFCircle(toe::core::TOEvector2df position = toe::core::TOEvector2df(0,0));
    ~TFCircle();
    void Draw() const override;

private:

};

#endif