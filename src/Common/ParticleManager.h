#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include <glm/vec3.hpp>

struct Particle{
	glm::vec3 pos, speed, translation;
	unsigned char r, g, b;
	float size, rotation;
	float life = -1.0f;
};

class ParticleManager{
public:	
	ParticleManager();
	~ParticleManager();

	void InitParticle(Particle& p);
	void UpdateParticle(Particle& p, float deltaTime);
private:
};

#endif