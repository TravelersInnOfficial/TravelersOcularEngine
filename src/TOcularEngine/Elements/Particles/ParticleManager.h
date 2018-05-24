#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

/**
 * @brief Updates and manages all Particle Systems.
 * 
 * @file ParticleManager.h
 */

#include <TOEvector3d.h>

struct Particle{
	TOEvector3df pos, speed, translation;		// Position, speed and traslation
	unsigned char r, g, b;						// color of the particle
	float size, rotation;						// size and rotation
	float life = -1.0f;							// time of life
};

class ParticleManager{
public:
	/**
	 * @brief Construct a new Particle Manager object
	 * 
	 */
	ParticleManager();

	/**
	 * @brief Destroy the Particle Manager object
	 * 
	 */
	virtual ~ParticleManager();

	/**
	 * @brief Inits Particle System
	 * 
	 * @param p: particle to init
	 */
	virtual void InitParticle(Particle& p);
	
	/**
	 * @brief Update all particles
	 * 
	 * @param p: particle to update
	 * @param deltaTime: time between frames
	 */
	virtual void UpdateParticle(Particle& p, float deltaTime);
	
};

#endif