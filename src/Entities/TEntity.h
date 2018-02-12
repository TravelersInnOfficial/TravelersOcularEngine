#ifndef TENTITY_H
#define TENTITY_H

#include <stack>
#include <glm/gtc/matrix_transform.hpp>

class TEntity{
public:
	virtual void EndDraw() = 0;
	virtual void BeginDraw() = 0;

protected:
	static std::stack<glm::mat4> InitializeStack();
	static std::stack<glm::mat4> m_stack;

};

#endif