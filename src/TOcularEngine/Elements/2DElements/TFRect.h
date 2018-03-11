#ifndef TFRECT_H
#define TFRECT_H

#include "TFDrawable.h"

class TFRect: public TFDrawable{
    friend class SceneManager;
public:
    void Draw() const override;

private:
    TFRect(toe::core::TOEvector2df size, toe::core::TOEvector2df position, float rotation);
    ~TFRect();

};

#endif