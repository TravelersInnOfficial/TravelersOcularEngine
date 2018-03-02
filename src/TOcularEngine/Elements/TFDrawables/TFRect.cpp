#include "TFRect.h"
#include <GL/glew.h>

TFRect::TFRect(toe::core::TOEvector2df size){
}

TFRect::~TFRect(){
}

void TFRect::Rotate(float rot){
}
    
void TFRect::Scale(toe::core::TOEvector2df scal){
}

void TFRect::draw(sf::RenderTarget& target, sf::RenderStates states) const {
}

//SETTERS
void TFRect::SetPosition(toe::core::TOEvector2df pos){
}

void TFRect::SetOrigin(toe::core::TOEvector2df ori){
}

void TFRect::SetSize(toe::core::TOEvector2df siz){
}

void TFRect::SetRotation(float rot){
}

void TFRect::SetScale(toe::core::TOEvector2df scal){
}

void TFRect::SetColor(toe::core::TOEvector4df col){
}

void TFRect::SetTexture(std::string path, toe::core::TOEvector4df rect){
}

//GETTERS
toe::core::TOEvector2df TFRect::GetPosition() const{
}

toe::core::TOEvector2df TFRect::GetOrigin() const{
}

toe::core::TOEvector2df TFRect::GetSize() const{
}

float TFRect::GetRotation() const{
}

toe::core::TOEvector2df TFRect::GetScale() const{
}