#ifndef TPARTICLESYSTEM_H
#define TPARTICLESYSTEM_H

#include <glm/vec3.hpp>
#include "./TEntity.h"
#include "./../Resources/TResourceTexture.h"

struct Particle{
	Particle();
	void InitParticle();
	glm::vec3 pos, speed;
	unsigned char r, g, b;
	float size;
	float life, cameraDistance;

	bool operator<(Particle& that){
        // Sort in reverse order : far particles drawn first.
        return this->cameraDistance < that.cameraDistance;
    }
};



class TParticleSystem: public TEntity{
public:
	TParticleSystem(std::string path = "");
	~TParticleSystem();

	void BeginDraw();
	void EndDraw();

	void Update(float deltaTime);

	void SetTexture(std::string path);
private:
	void SendShaderData();
	void ResetShaderData();
	void SortParticles();
	int FindUnusedParticle();
	void AddNewParticles();

	TResourceTexture*	m_texture;

	int 				m_particleCount;		// Numero de particulas activas en el momento
	static const int 	m_maxParticles = 10000;	// Numero maximo de particulas
	
	GLuint 				m_vbo;	// Vertex buffer del mesh basico
	GLuint				m_pbo; 	// Buffer con las posiciones de las particulas
	GLuint				m_cbo;	// Buffer con los colores de las particular

	glm::vec3 			m_center; 				// Centro absoluto del sistema de particulas
	int 				m_lastUsedParticle; 	// Numero de la ultima particula que se actualizo

	Particle 			m_particleContainer		[m_maxParticles*1];		// Array con todas las particulas
	unsigned char 		m_particlesColorData	[m_maxParticles*3];		// Array con todos los colores de las particulas
	float				m_particlePositionData	[m_maxParticles*4];		// Array con las posiciones de las particulas
};

#endif