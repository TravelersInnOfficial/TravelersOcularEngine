#ifndef TPARTICLESYSTEM_H
#define TPARTICLESYSTEM_H

#include <glm/vec3.hpp>
#include "./TEntity.h"
#include "./../Resources/TResourceTexture.h"
#include "./../TOcularEngine/Elements/Particles/ParticleManager.h"

class TParticleSystem: public TEntity{
public:
	TParticleSystem(std::string path = "");
	~TParticleSystem();

	virtual void BeginDraw() override;
	virtual void EndDraw() override;
	virtual void DrawShadow() override;

	void Update(float deltaTime);

	void SetTexture(std::string path);
	void SetManager(ParticleManager* manager);
	void SetTranslate(glm::vec3 position);
	void Translate(glm::vec3 position);
	
	void SetNewPerSecond(int newPerSecond);
	int GetNewPerSecond();

private:
	void SendShaderData();
	void ResetShaderData();
	int FindUnusedParticle();
	void AddNewParticles(float deltaTime);

	ParticleManager*	m_manager;
	TResourceTexture*	m_texture;

	int 				m_particleCount;			// Numero de particulas activas en el momento
	static const int 	m_maxParticles = 10000;		// Numero maximo de particulas
	int					m_newParticlesPerSecond;	// Numero de particulas que se crean cada segundo
	float				m_particleAcumulation;
	
	GLuint 				m_vbo;	// Vertex buffer del mesh basico
	GLuint				m_pbo; 	// Buffer con las posiciones de las particulas
	GLuint				m_ebo;	// Buffer con los extras de las particulas
	GLuint				m_cbo;	// Buffer con los colores de las particular

	int 				m_lastUsedParticle; 	// Numero de la ultima particula que se actualizo

	Particle 			m_particleContainer		[m_maxParticles*1];		// Array con todas las particulas
	unsigned char 		m_particlesColorData	[m_maxParticles*3];		// Array con todos los colores de las particulas
	float				m_particlePositionData	[m_maxParticles*3];		// Array con las posiciones de las particulas
	float 				m_particlesExtra		[m_maxParticles*2];		// Array con el tamanyo y la rotacion de las particulas

	bool m_drawingShadows;
};

#endif