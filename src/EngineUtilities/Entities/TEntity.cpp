#include "./TEntity.h"

TEntity::~TEntity(){}

std::stack<glm::mat4> TEntity::InitializeStack(){
    static std::stack<glm::mat4> aux;
    aux.push(glm::mat4(1.0f));
    return aux;
}

std::stack<glm::mat4> TEntity::m_stack = TEntity::InitializeStack();

void TEntity::SetProgram(SHADERTYPE program){
    m_program = program;
}

// Initialize static variables
glm::mat4 TEntity::ViewMatrix;
glm::mat4 TEntity::ProjMatrix;
bool TEntity::m_checkClipping = false;
float TEntity::m_clippingLimits[4] = {+1.0f, -1.0f, +1.0f, -1.0f};
glm::mat4 TEntity::DepthWVP;
unsigned int TEntity::ShadowMap = 0;


void TEntity::SetViewMatrixPtr(glm::mat4 view){
    ViewMatrix = view;
}

bool TEntity::CheckClipping(){
	glm::mat4 mvpMatrix = ProjMatrix * ViewMatrix * m_stack.top();
	glm::vec4 point = mvpMatrix * glm::vec4(0,0,0,1);
	return CheckClippingPoint(point);
}

bool TEntity::CheckClippingPoint(glm::vec4 Pclip){
	return abs(Pclip.x) < Pclip.w && abs(Pclip.y) < Pclip.w && 0 < Pclip.z && Pclip.z < Pclip.w;
}

void TEntity::DrawShadow(){}

#include <iostream>

void TEntity::CheckClippingAreas(glm::vec4 point, int* upDown, int* leftRight, int* nearFar){
   float valueX = point.x / abs(point.w);
   float valueY = point.y / abs(point.w);
   float valueZ = point.z / abs(point.w);

    if(valueX > m_clippingLimits[0]) (*leftRight)++;
    else if(valueX < m_clippingLimits[1]) (*leftRight)--;

    if(valueY > m_clippingLimits[2]) (*upDown)++;
    else if(valueY < m_clippingLimits[3]) (*upDown)--;

    if(valueZ > 1.0f) (*nearFar)++;
    else if(valueZ < 0.0f) (*nearFar)--;


   /* if(point.x > point.w) (*leftRight)++;
    else if(point.x < -point.w) (*leftRight)--;

    if(point.y > point.w) (*upDown)++;
    else if(point.y < -point.w) (*upDown)--;

    if(point.z > point.w) (*nearFar)++;
    else if(point.z < 0) (*nearFar)--;*/
}
