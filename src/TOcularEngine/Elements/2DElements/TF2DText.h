#ifndef TF2DTEXT_H
#define TF2DTEXT_H

#include "TFDrawable.h"
#include <vector>
#include <TOEvector2d.h>

namespace glm{
    typedef glm::highp_vec3 vec3;
    typedef glm::highp_vec2 vec2;
}

typedef TOEvector2d<float> TOEvector2df;
typedef unsigned int GLuint;
class TResourceTexture;

class TF2DText : public TFDrawable{
    friend class SceneManager;
public:
    //IHERITED 
    void Draw() const override;
    void Erase() override;

    //SETTERS
    void SetText(std::string txt);
    void SetTextSize(float size);
    void SetPosition(float x, float y) override;
    void SetTextureFont(std::string path);

    //GETTERS
    std::string GetText();
    float GetTextSize();

private:
    TF2DText(std::string text = "", TOEvector2df position = TOEvector2df(0,0));
    ~TF2DText();

    TOEvector2df            m_position;
    std::string             m_text;
    float                   m_textSize;
    float                   m_vertexSize;
    TResourceTexture*       m_texture;
    GLuint                  m_VBO, m_UVBO;

};

#endif