#ifndef TFDRAWABLE_H
#define TFDRAWABLE_H

/**
 * @brief Father class of all 2D stuff.
 * 
 * @file TFDrawable.h
 * 
 * The necesary info for creating this interface and all the inherited clases was found in this pages:
 * https://open.gl/drawing
 * https://www.opengl.org/archives/resources/faq/technical/transparency.htm
 * https://stackoverflow.com/questions/1568559/opengl-spritesheets-beginner-needs-some-guidance
 */

#include <TOEvector2d.h>
#include <ShaderTypes.h>
#include <TColor.h>
#include <cmath>  

/**
 * @brief Data struct for storing dimensions in pixel units and the texture path
 * 
 */
struct RectData{
    TOEvector2df position = TOEvector2df(0.0f, 0.0f);
    TOEvector2df size = TOEvector2df(0.0f, 0.0f);
    std::string texture = "";
};

class TFDrawable{
public:
    /**
     * @brief Destroy the TFDrawable object
     * 
     */
    virtual ~TFDrawable(){}

    /**
     * @brief Virtual TFDrawable interface constructor
     * 
     */
    virtual void Draw() const = 0;
    
    /**
     * @brief Returns the object 2D position
     * 
     * @return TOEvector2df position
     */
    virtual TOEvector2df GetPosition() const;

    /**
     * @brief Returns the position X coordinate
     * 
     * @return float X coordinate
     */
    virtual float GetPosX() const;

    /**
     * @brief Returns the position Y coordinate
     * 
     * @return float Y coordinate
     */
    virtual float GetPosY() const;

    /**
     * @brief Returns the object size in PIXELS
     * 
     * @return TOEvector2df size
     */
    virtual TOEvector2df GetSize() const;
    
    /**
     * @brief Returns the object width in PIXELS
     * 
     * @return float width
     */
    virtual float GetWidth() const;

    /**
     * @brief Returns the object height in PIXELS
     * 
     * @return float height
     */
    virtual float GetHeight() const;

    /**
     * @brief Sets the object rotation in DEGREES
     * 
     * @param ro (rotation in deg)
     */
    virtual void SetRotation(float rot);

    /**
     * @brief Set the object position in PIXELS
     * 
     * @param x (x coordinate in px)
     * @param y (y coordinate in px)
     */
    virtual void SetPosition(float x, float y);

    /**
     * @brief Set the object X coordinate in PIXELS
     * 
     * @param x (x coordinate in px)
     */
    virtual void SetPosX(float x);

    /**
     * @brief Set the object Y coordinate in PIXELS
     * 
     * @param y (y coordinate in px)
     */
    virtual void SetPosY(float y);

    /**
     * @brief Set the object size in PIXELS
     * 
     * @param w (width in px)
     * @param h (height in px)
     */
    virtual void SetSize(float w, float h);

    /**
     * @brief Set the object width in PIXELS
     * 
     * @param w (width in px)
     */
    virtual void SetWidth(float w);

    /**
     * @brief Set the object height in PIXELS
     * 
     * @param h (height in px)
     */
    virtual void SetHeight(float h);

    /**
     * @brief Set the object color (range 0.0f - 1.0f)
     * 
     * @param r (red component)
     * @param g (green component)
     * @param b (blue component)
     * @param a (alpha channel)
     */
    virtual void SetColor(float r, float g, float b, float a = 1.0f);

    /**
     * @brief Set the object red color component value
     * 
     * @param r (red value 0.0f-1.0f)
     */
    virtual void SetRed(float r);

    /**
     * @brief Set the object green color component value
     * 
     * @param g (green value 0.0f-1.0f)
     */
    virtual void SetGreen(float g);

    /**
     * @brief Set the object blue color component value
     * 
     * @param b (blue value 0.0f-1.0f) 
     */
    virtual void SetBlue(float b);

    /**
     * @brief Set the the object alpha color channel value
     * 
     * @param a (alpha channel value 0.0f-1.0f)
     */
    virtual void SetAlpha(float a);

    /**
     * These methods are used for drawing other objects in between with another libary like ImGui or SDL
     * 
     */
    /**
     * @brief Puts the object in the second plane drawing list
     * 
     */
    virtual void ToBkg();

    /**
     * @brief Puts the object in the first plane drawing list
     * 
     */
    virtual void ToFront();

protected:

    TOEvector2df m_position;            //Object position in OPENGL UNITS
    TOEvector2df m_size;                //Size in OPENGL UNITS
    float m_rotation;                   //Rotation in OPENGL UNITS
    TColor m_color;                     //Object color and transparency components

    SHADERTYPE m_program = TWOD_SHADER; //Shader program used for this class
    TOEvector2di w_dims;                //Window dimensions in PIXEL units
    RectData m_InData;                  //Shape and position data in PIXEL units
};
#endif