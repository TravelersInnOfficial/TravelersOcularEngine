#ifndef TENTITY_H
#define TENTITY_H

#include <stack>
#include <glm/gtc/matrix_transform.hpp>
#include "../Common/ProgramEnum.h"
#include "../Resources/Program.h"

class TEntity{
public:
	virtual void EndDraw() = 0;
	virtual void BeginDraw() = 0;
	void SetProgram(PROGRAM program);

protected:
	static std::stack<glm::mat4> InitializeStack();
	static std::stack<glm::mat4> m_stack;
	PROGRAM m_program;

};

#endif