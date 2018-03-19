#ifndef TENTITY_H
#define TENTITY_H

#include <ShaderTypes.h>
#include "../Resources/Program.h"
#include <stack>
#include <glm/mat4x4.hpp>

class TEntity{
public:
	virtual ~TEntity();
	virtual void EndDraw() = 0;
	virtual void BeginDraw() = 0;
	virtual bool CheckClipping();
	void SetProgram(SHADERTYPE program);

	static void SetViewMatrixPtr(glm::mat4 view);
	static void SetProjMatrixPtr(glm::mat4 proj);

	static std::stack<glm::mat4> InitializeStack();
	static std::stack<glm::mat4> m_stack;
	static glm::mat4 ViewMatrix;
	static glm::mat4 ProjMatrix;
	static bool m_checkClipping;
	
	SHADERTYPE m_program;

protected:
	bool CheckClippingPoint(glm::vec4 point);
	void CheckClippingAreas(glm::vec4 point, int* upDown, int* leftRight, int* nearFar);
};

#endif