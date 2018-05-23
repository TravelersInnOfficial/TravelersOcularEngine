#ifndef TFPARTICLESYSTEM_H
#define TFPARTICLESYSTEM_H

/**
 * @brief Particle System Facade.
 * 
 * @file TFParticleSystem.h
 */

#include "./../TFNode.h"
#include "ParticleManager.h"

class TFParticleSystem: public TFNode{
	friend class SceneManager;
public:
	/**
	 * @brief Translates Particle emissor
	 * 
	 * @param translation 
	 */
	void Translate(TOEvector3df translation) override;
	
	/**
	 * @brief Traslates Emissor without changing particles
	 * 
	 * @param translation 
	 */
	void SetTranslateSmooth(TOEvector3df translation);

	/**
	 * @brief Set Particles Texture 
	 * 
	 * @param path 
	 */
	void SetTexture(std::string path);
	
	/**
	 * @brief Set Particle Manager
	 * 
	 * @param manager 
	 */
	void SetManager(ParticleManager* manager);
	
	/**
	 * @brief Update all particles
	 * 
	 * @param deltaTime
	 */
	void Update(float deltaTime);

	/**
	 * @brief Set Number of particles created per second
	 * 
	 * @param newPerSecond: particles per second
	 */
	void SetNewPerSecond(int newPerSecond);
	/**
	 * @brief Get Number of particles created per second
	 * 
	 * @return int: particles per second
	 */
	int GetNewPerSecond();

private:
	/**
	 * @brief Construct a new ParticleSystem object
	 * 
	 * @param position 
	 * @param rotation 
	 * @param scale 
	 */
	TFParticleSystem(
		TOEvector3df position = TOEvector3df(0, 0, 0),
		TOEvector3df rotation = TOEvector3df(0, 0, 0),
		TOEvector3df scale = TOEvector3df(1, 1, 1)
	);
	
	/**
	//  * @brief Destroy the ParticleSystem
	 * 
	 */
	~TFParticleSystem();
};

#endif