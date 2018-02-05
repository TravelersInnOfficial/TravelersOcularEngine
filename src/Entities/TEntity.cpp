#include "./TEntity.h"


std::stack<glm::mat4> TEntity::m_stack = TEntity::InitializeStack();