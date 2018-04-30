#ifndef TF2DTEXT_H
#define TF2DTEXT_H

#include "TFDrawable.h"
#include <vector>
#include <TOEvector2d.h>

namespace glm{
    typedef glm::highp_vec3 vec3;
    typedef glm::highp_vec2 vec2;
}

typedef TOEvector3d<float> TOEvector3df;
typedef unsigned int GLuint;
class TResourceTexture;

class TF2DText : public TFDrawable{
    friend class SceneManager;
public:
    void Draw() const override;
    void Erase() override;

    void SetText(std::string txt);

private:
    TF2DText(std::string text = "", TOEvector2df position = TOEvector2df(0,0));
    ~TF2DText();

    TOEvector2df            m_position;
    std::string             m_text;
    float                   m_textSize;
    float                   m_size;
    TResourceTexture*       m_texture;
    GLuint                  m_VBO, m_UVBO;

};

#endif