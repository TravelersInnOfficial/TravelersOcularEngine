#ifndef TFRECT_H
#define TFRECT_H

#include "TFDrawable.h"

class TFRect : public TFDrawable{
public:
    TFRect(toe::core::TOEvector2df size);
    ~TFRect() override;
    
    void Rotate(float rot) override;
    void Scale(toe::core::TOEvector2df scal) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    //SETTERS
    void SetPosition(toe::core::TOEvector2df pos) override;
    void SetOrigin(toe::core::TOEvector2df ori) override;
    void SetSize(toe::core::TOEvector2df siz) override; 
    void SetRotation(float rot) override;
    void SetScale(toe::core::TOEvector2df scal) override;
    void SetColor(toe::core::TOEvector4df col) override;
    void SetTexture(std::string path, toe::core::TOEvector4df rect) override;
    
    //GETTERS
    toe::core::TOEvector2df GetPosition() const override;
    toe::core::TOEvector2df GetOrigin() const override;
    toe::core::TOEvector2df GetSize() const override;
    float GetRotation() const override;
    toe::core::TOEvector2df GetScale() const override;

private:
};

#endif