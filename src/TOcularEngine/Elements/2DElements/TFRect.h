#ifndef TFRECT_H
#define TFRECT_H

/**
 * @brief Draws a rectangle in screen.
 * 
 * @file TFRect.h
 */

#include "TFDrawable.h"
#include <TOEvector4d.h>

//FAST FORWARD DECLARATIONS
typedef unsigned int GLuint;
class TResourceTexture; 

class TFRect: public TFDrawable{
    friend class SceneManager;
public:
    //INHERITED FROM TFDRAWABLE
    void Draw() const override;
    void SetWidth(float w) override;
    void SetHeight(float h) override;

    /**
     * @brief Set the object visual mask
     * 
     * @param mask_path (path to the texture file)
     */
    void SetMask(std::string mask_path);
    
private:
    /**
     * @brief Construct a new TFRect object
     * 
     * @param position (object position in px)
     * @param size (object size in px)
     * @param rotation (object rotation in deg)
     */
    TFRect(TOEvector2df position, TOEvector2df size, float rotation);

    /**
     * @brief Destroy the TFRect object
     * 
     */
    ~TFRect();

    GLuint m_VBO;               //Vertex buffer object
    TResourceTexture* m_mask;   //Mask texture
    TOEvector2df m_mask_size;   //Mask texture size
    TOEvector4df m_mask_rect;   //Mask texture rectangle
};

#endif