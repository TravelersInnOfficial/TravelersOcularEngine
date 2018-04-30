#include "TFDrawable.h"
#include "./../../VideoDriver.h"

TOEvector2df TFDrawable::GetPosition() const {return m_InData.position;}
float TFDrawable::GetPosX() const {return m_InData.position.X;}
float TFDrawable::GetPosY() const {return m_InData.position.Y;}

TOEvector2df TFDrawable::GetSize() const {return m_InData.size;}
float TFDrawable::GetWidth() const {return m_InData.size.X;}
float TFDrawable::GetHeight() const {return m_InData.size.Y;}

void TFDrawable::SetRotation(float rot){m_rotation = rot;}

void TFDrawable::SetPosition(float x, float y) {   
    m_position = TOEvector2df((x*2 - w_dims.X) / w_dims.X , (y*2 - w_dims.Y) / w_dims.Y);
    m_InData.position.X = x;
    m_InData.position.Y = y;
};

void TFDrawable::SetPosX(float x){
    m_position.X = (x*2 - w_dims.X) / w_dims.X;
    m_InData.position.X = x;
}

void TFDrawable::SetPosY(float y){
    m_position.Y = (y*2 - w_dims.Y) / w_dims.Y;
    m_InData.position.Y = y;
}

void TFDrawable::SetSize(float w, float h){
    m_size = TOEvector2df((std::abs(w *2) / w_dims.X), (std::abs(h *2) / w_dims.Y));
    m_InData.size.X = w;
    m_InData.size.Y = h;
}

void TFDrawable::SetWidth(float w){
    m_size.X = (std::abs(w *2) / w_dims.X);
    m_InData.size.X = w;
}

void TFDrawable::SetHeight(float h){
    m_size.Y =  (std::abs(h *2) / w_dims.Y);
    m_InData.size.Y = h;
}

void TFDrawable::SetColor(float r, float g, float b, float a){
    m_color.SetR(r);
    m_color.SetG(g);
    m_color.SetB(b);
    m_color.SetA(a);
}

void TFDrawable::SetRed(float r) {m_color.SetR(r);}
void TFDrawable::SetGreen(float g) {m_color.SetG(g);}
void TFDrawable::SetBlue(float b) {m_color.SetB(b);}
void TFDrawable::SetAlpha(float a) {m_color.SetA(a);}

void TFDrawable::ToBkg(){
    VideoDriver::GetInstance()->GetSceneManager()->PushToBkg(this);
}

void TFDrawable::ToFront(){
    VideoDriver::GetInstance()->GetSceneManager()->PushToFront(this);
}