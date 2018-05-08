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
	virtual void DrawShadow();
	virtual bool CheckClipping();
	void SetProgram(SHADERTYPE program);

	static void SetViewMatrixPtr(glm::mat4 view);
	static void ResetClippingVariables();

	static std::stack<glm::mat4> InitializeStack();
	static std::stack<glm::mat4> m_stack;
	static bool m_checkClipping;
	static float m_clippingLimits[4];	// 0 (+X) / 1 (-X) / 2 (+Y) / 3 (-Y)
	
	// PROVISIONAL STATIC VARIABLES
	static glm::mat4 ViewMatrix;
	static glm::mat4 ProjMatrix;
	static glm::mat4 DepthWVP;
	
    SHADERTYPE m_program = NONE_SHADER;

protected:
	bool CheckClippingPoint(glm::vec4 point);
	void CheckClippingAreas(glm::vec4 point, int* upDown, int* leftRight, int* nearFar);
};

#endif