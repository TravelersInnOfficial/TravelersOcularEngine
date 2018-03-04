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

void TEntity::SetViewMatrixPtr(glm::mat4 view){
    ViewMatrix = view;
}

void TEntity::SetProjMatrixPtr(glm::mat4 proj){
    ProjMatrix = proj;
}
