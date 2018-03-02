#ifndef TENTITY_H
#define TENTITY_H

#include <stack>
#include <glm/gtc/matrix_transform.hpp>
#include "../Common/ShaderTypes.h"
#include "../Resources/Program.h"

class TEntity{
public:
	virtual ~TEntity();
	virtual void EndDraw() = 0;
	virtual void BeginDraw() = 0;
	void SetProgram(SHADERTYPE program);

	static void SetViewMatrixPtr(glm::mat4 view);
	static void SetProjMatrixPtr(glm::mat4 proj);

protected:
	static std::stack<glm::mat4> InitializeStack();
	static std::stack<glm::mat4> m_stack;
	static glm::mat4 ViewMatrix;
	static glm::mat4 ProjMatrix;
	
	SHADERTYPE m_program;

};

#endif