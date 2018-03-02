#ifndef TFRECT_H
#define TFRECT_H

#include "TFNode.h"
#include <TOEvector2d.h>

class TFRect: public TFNode{
    friend class SceneManager;
public:

    void SetTexture(std::string texture_path);
    void SetRotation(float rot);

private:
    TFRect(
        toe::core::TOEvector2df size = toe::core::TOEvector2df(0, 0),
		toe::core::TOEvector2df position = toe::core::TOEvector2df(0, 0),
		float rotation = 0,
		std::string texture = ""
        );

    ~TFRect();

};

#endif