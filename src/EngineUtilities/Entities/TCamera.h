#ifndef TCAMERA_H
#define TCAMERA_H

#include "TEntity.h"
#include <glm/mat4x4.hpp>
#include "../Resources/Program.h"

class TCamera: public TEntity{
public:
	TCamera	(
				bool perspective = true,
				float left = -0.1f,
				float right = 0.1f,
				float bottom = -0.075f,
				float top = 0.075f,
				float near = 0.1f,
				float far = 500.0f
			);
	~TCamera();

	void SetPerspective(float left, float right, float bottom, float top, float near, float far);
	void SetParallel(float left, float right, float bottom, float top, float near, float far);

	void SetPerspective();
	void SetParallel();
	bool GetPerspective();

	void SetNear(float newVal);
	float GetNear();

	void SetFar(float newVal);
	float GetFar();

	void SetLeft(float newVal);
	float GetLeft();

	void SetRight(float newVal);
	float GetRight();

	void SetTop(float newVal);
	float GetTop();

	void SetBottom(float newVal);
	float GetBottom();

	glm::mat4 GetProjectionMatrix();

	void RecalculateProjectionMatrix();
	
	SHADERTYPE m_program;

	void BeginDraw();
	void EndDraw();

private:
	bool m_perspective;

	float m_near, m_far;
	float m_left, m_right;
	float m_top, m_bottom;

	glm::mat4 m_projectionMatrix;

	glm::mat4 CalculatePerspectiveMatrix();
	glm::mat4 CalculateOrthogonalMatrix();

};

#endif