#include "./TEntity.h"

TEntity::~TEntity(){}

std::stack<glm::mat4> TEntity::InitializeStack(){
    static std::stack<glm::mat4> aux;   // 
    aux.push(glm::mat4(1.0f));          //
    return aux;                         // Creamos la pila con la matriz identidad en ella y la devolvemos
}

std::stack<glm::mat4> TEntity::m_stack = TEntity::InitializeStack();

unsigned int TEntity::currentFrame = 1;

void TEntity::SetProgram(SHADERTYPE program){
    m_program = program;
}

// Initialize static variables
glm::mat4 TEntity::ViewMatrix;
glm::mat4 TEntity::ProjMatrix;
bool TEntity::m_checkClipping = false;
float TEntity::m_clippingLimits[4] = {+1.0f, -1.0f, +1.0f, -1.0f};  // Limites por defecto de la pantalla
glm::mat4 TEntity::DepthWVP;

void TEntity::ResetClippingVariables(){
    m_clippingLimits[0] = 1;
    m_clippingLimits[1] = -1;
    m_clippingLimits[2] = 1;
    m_clippingLimits[3] = -1;
}

void TEntity::SetViewMatrixPtr(glm::mat4 view){
    ViewMatrix = view;
}

bool TEntity::CheckClipping(){
	glm::mat4 mvpMatrix = ProjMatrix * ViewMatrix * m_stack.top(); //
	glm::vec4 point = mvpMatrix * glm::vec4(0,0,0,1);              // 
	return CheckClippingPoint(point);                              // Comparamos el clipping con el centro del objeto
}

bool TEntity::CheckClippingPoint(glm::vec4 Pclip){
	return abs(Pclip.x) < Pclip.w && abs(Pclip.y) < Pclip.w && 0 < Pclip.z && Pclip.z < Pclip.w;
}

void TEntity::DrawShadow(){}

void TEntity::CheckClippingAreas(glm::vec4 point, int* upDown, int* leftRight, int* nearFar){
   float valueX = point.x / abs(point.w);                   //
   float valueY = point.y / abs(point.w);                   //
   float valueZ = point.z / abs(point.w);                   // Convertimos los valores a valores de la pantalla 

    if(valueX > m_clippingLimits[0]) (*leftRight)++;        //
    else if(valueX < m_clippingLimits[1]) (*leftRight)--;   // Comparamos si se sale por los lados con los limites almacenados en la clase

    if(valueY > m_clippingLimits[2]) (*upDown)++;           //
    else if(valueY < m_clippingLimits[3]) (*upDown)--;      // Comparamos si se sale por arriba/abajo con los limites almacenados en la clase

    if(valueZ > 1.0f) (*nearFar)++;                         //
    else if(valueZ < 0.0f) (*nearFar)--;                    // Comparamos si se sale por el near/far de la camara
}
