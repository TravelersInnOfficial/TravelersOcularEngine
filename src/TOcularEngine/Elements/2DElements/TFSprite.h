#ifndef TFSPRITE_H
#define TFSPRITE_H

/**
 * @brief Draws 2D sprite in screen.
 * 
 * @file TFSprite.h
 */

#include "TFDrawable.h"
#include <TOEvector4d.h>

//FAST FORWARD DECLARATION
class TResourceTexture;
typedef unsigned int GLuint;

class TFSprite : public TFDrawable{
    friend class SceneManager;
public:
    //INHERITED FROM TFDRAWABLE
    void Draw() const override;

    /**
     * @brief Selects a rectangle from the texture given (calculating the corners)
     * 
     * @param x (x position ) |
     * @param y (y position ) \ Down left corner
     * @param w (width)       |
     * @param h (height)      \ Up right corner
     */
    void SetRect (float x, float y, float w, float h);

    /**
     * @brief Selects a rectangle from the texture given (directly)
     * 
     * @param x (x position ) |
     * @param y (y position ) \ Down left corner
     * @param w (width)       |
     * @param h (height)      \ Up right corner
     */
    void SetTextureRect(float x, float y, float w, float h);

    /**
     * @brief Set the sprite texture
     * 
     * @param texture (texture path)
     */
    void SetTexture(std::string texture);

    /**
     * @brief Returns the sprite texture path 
     * 
     * @return std::string (texture path)
     */
    std::string GetTexture() const;

    /**
     * @brief Adds the value the texture horizontal scrolling velocity
     * 
     * @param vel (horizontal scroll velocity)
     */
    void ScrollH(float vel);

    /**
     * @brief Adds the value to the texture vertical scrolling velocity
     * 
     * @param vel (vertical scroll velocity)
     */
    void ScrollV(float vel);

    /**
     * @brief Set the texture horizontal scrolling velocity
     * 
     * @param value (horizontal scroll velocity)
     */
    void SetScrollH(float value);

    /**
     * @brief Adds the value to the texture vertical scrolling velocity
     * 
     * @param value (vertical scroll velocity)
     */
    void SetScrollV(float value);

    /**
     * @brief Applies a mask to the sprite
     * 
     * @param mask_path (texture path)
     */
    void SetMask(std::string mask_path);

    /**
     * @brief Returns the texture height in pixel units
     * 
     * @return float (texture height)
     */
    float GetTextureHeight();

    /**
     * @brief Returns the texture width in pixel units
     * 
     * @return float (texture width)
     */
    float GetTextureWidth();

    /**
     * @brief Returns the texture dimensions
     * 
     * @return TOEvector2df (texture size)
     */
    TOEvector2df GetTextureSize();

    float scrollH; //Horizontal scroll velocity
    float scrollV; //Vertical scroll velocity

private:
    /**
     * @brief Construct a new TFSprite object
     * 
     * @param texture (texture path)
     * @param position (position in pixel units)
     * @param size (size in pixel units)
     */
    TFSprite(std::string texture, TOEvector2df position, TOEvector2df size);

    /**
     * @brief Destroy the TFSprite object
     * 
     */
    ~TFSprite();

    TResourceTexture* 	m_texture;  //Texture resource
    TOEvector2df m_texture_size;    //Texture size in OpenLG units
    TOEvector4df m_rect;            //Texture rectangle coordinates in OpenGL units
    TOEvector4df m_mask_rect;       //Mask texture rectangle coordinates in OpenGL units
    TResourceTexture* m_mask;       //Mask texture resource
    GLuint m_VAO, m_VBO;            //Vertex Array and Vertex Buffer objects
};
#endif