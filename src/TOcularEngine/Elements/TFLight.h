#ifndef TFLIGHT_H
#define TFLIGHT_H

#include <vector4d.h>
#include "TFNode.h"

class TFLight: public TFNode{
	friend class SceneManager;

public:
	void SetColor(toe::core::vector4df color);				// Changes the light color
	void SetIntensity(float intensity);			// Changes the light intensity
	void SetActive(bool active);				// Changes the light active state

	toe::core::vector4df GetColor();	// Returns the light color
	float GetIntensity();	// Returns the light intensity
	bool GetActive();		// Returns the light active state

private:
	TFLight(
		toe::core::vector3df position = toe::core::vector3df(0, 0, 0),
		toe::core::vector3df rotation = toe::core::vector3df(0, 0, 0),
		toe::core::vector4df color = toe::core::vector4df(255.0f, 255.0f, 255.0f, 255.0f),
		float intensity = 1.0f
	);
	~TFLight();
	void CreateEstructure();

};

#endif