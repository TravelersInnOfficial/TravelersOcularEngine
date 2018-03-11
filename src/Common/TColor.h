#ifndef TCOLOR_H
#define TCOLOR_H

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

class TColor {
public:
	TColor(glm::vec4 rgbaData = glm::vec4(0,0,0,0));
	~TColor();

	void SetRGBA(glm::vec4 newVal);
	void SetRGB(glm::vec3 newVal);
	void SetR(float newVal);
	void SetG(float newVal);
	void SetB(float newVal);
	void SetA(float newVal);

	glm::vec4 GetRGBA();
	glm::vec3 GetRGB();
	float GetR() const;
	float GetG() const;
	float GetB() const;
	float GetA() const;

	float CapValues(float valueToCap);
	glm::vec3 CapValues(glm::vec3 valueToCap);
	glm::vec4 CapValues(glm::vec4 valueToCap);

private:
	glm::vec4 m_rgba;

};

#endif