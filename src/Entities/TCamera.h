#ifndef TCAMERA_H
#define TCAMERA_H

#include "TEntity.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TCamera: public TEntity{
public:
	TCamera(bool m_perspective, float m_near, float m_far, float m_left, float m_right, float m_top, float m_bottom);
	~TCamera();

	void SetPerspectiva(float m_near, float m_far, float m_left, float m_right, float m_top, float m_bottom);
	void SetParalela(float m_near, float m_far, float m_left, float m_right, float m_top, float m_bottom);

	void SetPerspectiva();
	void SetParalela();

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

	glm::mat4 RecalculateProjectionMatrix();

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