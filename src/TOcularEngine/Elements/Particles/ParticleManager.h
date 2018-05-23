#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

/**
 * @brief Updates and manages all Particle Systems.
 * 
 * @file ParticleManager.h
 */

#include <TOEvector3d.h>

struct Particle{
	TOEvector3df pos, speed, translation;
	unsigned char r, g, b;
	float size, rotation;
	float life = -1.0f;
};

class ParticleManager{
public:	
	ParticleManager();
	virtual ~ParticleManager();

	virtual void InitParticle(Particle& p);
	virtual void UpdateParticle(Particle& p, float deltaTime);
private:
};

#endif