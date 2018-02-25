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