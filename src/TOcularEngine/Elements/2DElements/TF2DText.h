#ifndef TF2DTEXT_H
#define TF2DTEXT_H

/**
 * @brief Draws 2D text in screen.
 * 
 * @file TF2DText.h
 */

#include "TFDrawable.h"
#include <vector>
#include <TOEvector2d.h>

//FAST FORWARD DECLARATIONS
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
    //IHERITED FROM TFDRAWABLE CLASS
    void Draw() const override;

    //SETTERS
    /**
     * @brief Set the object text to show
     * 
     * @param txt (text data)
     */
    void SetText(std::string txt);

    /**
     * @brief Set the text characters size
     * 
     * @param size (character size)
     */
    void SetTextSize(float size);

    /**
     * @brief Set the Position object
     * 
     * @param x (x coordinate in px)
     * @param y (y coordinate in px)
     */
    void SetPosition(float x, float y) override;

    /**
     * @brief Set the texture image font 
     * 
     * @param path (image font path)
     */
    void SetTextureFont(std::string path);

    //GETTERS
    /**
     * @brief Get the actual text displayed
     * 
     * @return std::string (text)
     */
    std::string GetText();

    /**
     * @brief Get the text character size
     * 
     * @return float (character size)
     */
    float GetTextSize();

private:
    /**
     * @brief Construct a new TF2DText object
     * 
     * @param text (text to display) 
     * @param position (object position in px)
     */
    TF2DText(std::string text = "", TOEvector2df position = TOEvector2df(0,0));

    /**
     * @brief Destroy the TF2DText object
     * 
     */
    ~TF2DText();

    TOEvector2df            m_position;     //Object position in OpenGL units
    std::string             m_text;         //Actual text displayed
    float                   m_textSize;     //Character size in pixels
    float                   m_vertexSize;   //Vertex array size
    TResourceTexture*       m_texture;      //Font texture path
    GLuint                  m_VBO, m_UVBO;  //Opengl buffer objects

};

#endif