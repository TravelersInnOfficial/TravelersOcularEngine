#ifndef TFDRAWABLE_H
#define TFDRAWABLE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <TOEvector2d.h>
#include <TOEvector4d.h>
#include <iostream>

class TFDrawable{
    public:
    virtual ~TFDrawable() = default;

    virtual void Rotate(float rot) = 0;
    virtual void Scale(toe::core::TOEvector2df scal) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    //SETTERS
    virtual void SetPosition(toe::core::TOEvector2df pos) = 0;
    virtual void SetOrigin(toe::core::TOEvector2df ori) = 0;
    virtual void SetSize(toe::core::TOEvector2df siz) = 0; 
    virtual void SetRotation(float deg) = 0;
    virtual void SetScale(toe::core::TOEvector2df scal) = 0;
    virtual void SetColor(toe::core::TOEvector4df col) = 0;
    virtual void SetTexture(std::string path, toe::core::TOEvector4df rect) = 0;

    //GETTERS
    virtual toe::core::TOEvector2df GetPosition() const = 0;
    virtual toe::core::TOEvector2df GetOrigin() const = 0;
    virtual toe::core::TOEvector2df GetSize() const = 0;
    virtual float GetRotation() const = 0;
    virtual toe::core::TOEvector2df GetScale() const = 0;
    virtual toe::core::TOEvector4df GetColor() const {return m_color;}
    virtual std::string GetTexture() const {return m_texture_path;}

    protected:
    static toe::core::TOEvector4df m_color;
    static std::string m_texture_path;

};
#endif