#ifndef TPARTICLESYSTEM_H
#define TPARTICLESYSTEM_H

#include <glm/vec3.hpp>
#include "./TEntity.h"
#include "./../Resources/TResourceTexture.h"

class ParticleManager{
public:	
	/**
	 * @brief      Create the object
	 */
	ParticleManager();

	/**
	 * @brief      Destroys the object.
	 */
	~ParticleManager();

	/**
	 * @brief      Init the values of the particle
	 *
	 * @param      p     Instance of the particle that is going to be initialized
	 */
	void InitParticle(Particle& p);

	/**
	 * @brief      Update the value
	 *
	 * @param      p          Instance of the particle that is going to be update
	 * @param[in]  deltaTime  The delta time
	 */
	void UpdateParticle(Particle& p, float deltaTime);
private:
};

struct Particle{
	Particle();
	glm::vec3 pos, speed, translation;
	unsigned char r, g, b;
	float size, rotation;
	float life;
};

class TParticleSystem: public TEntity{
public:
	TParticleSystem(std::string path = "");
	~TParticleSystem();

	void BeginDraw();
	void EndDraw();

	void Update(float deltaTime);

	void SetTexture(std::string path);
	void SetTranslate(glm::vec3 position);
	void Translate(glm::vec3 position);
private:
	void SendShaderData();
	void ResetShaderData();
	int FindUnusedParticle();
	void AddNewParticles();

	ParticleManager*	m_manager;
	TResourceTexture*	m_texture;

	int 				m_particleCount;		// Numero de particulas activas en el momento
	static const int 	m_maxParticles = 10000;	// Numero maximo de particulas
	
	GLuint 				m_vbo;	// Vertex buffer del mesh basico
	GLuint				m_pbo; 	// Buffer con las posiciones de las particulas
	GLuint				m_ebo;	// Buffer con los extras de las particulas
	GLuint				m_cbo;	// Buffer con los colores de las particular

	int 				m_lastUsedParticle; 	// Numero de la ultima particula que se actualizo

	Particle 			m_particleContainer		[m_maxParticles*1];		// Array con todas las particulas
	unsigned char 		m_particlesColorData	[m_maxParticles*3];		// Array con todos los colores de las particulas
	float				m_particlePositionData	[m_maxParticles*3];		// Array con las posiciones de las particulas
	float 				m_particlesExtra		[m_maxParticles*2];		// Array con el tamanyo y la rotacion de las particulas
};

#endif