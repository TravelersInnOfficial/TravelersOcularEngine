#include "./TParticleSystem.h"
#include "../TOcularEngine/VideoDriver.h"
#include "./../TResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/norm.hpp>
#include <GL/glew.h>
#include <algorithm>

// Mesh que van a compartir todas las texturas
static const GLfloat g_vertex_buffer_data[] = {
 -0.5f, -0.5f, 0.0f,
 -0.5f, 0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 0.5f, 0.5f, 0.0f,
};

Particle::Particle(){
	InitParticle();
	life = -1.0f;
}

void Particle::InitParticle(){
	// Valores por defecto
	translation = glm::vec3(0,0,0);

	float X = (rand() % 10)/10.0f - 0.5f;
	float Y = (rand() % 10)/10.0f - 0.5f;
	float Z = (rand() % 10)/10.0f - 0.5f;

	pos 	= glm::vec3(X, Y, Z);

	X = (rand() % 4)/10.0f - 0.2f;
	Y = (rand() % 4)/10.0f - 0.2f;
	Z = (rand() % 4)/10.0f - 0.2f;

	speed 	= glm::vec3(X,Y,Z);

	r = (unsigned char)(rand() % 255);
	g = (unsigned char)(rand() % 255);
	b = (unsigned char)(rand() % 255);

	//size = (rand() % 5)/20.0f;
	size = (rand() % 5)/75.0f;
	rotation = (rand() % 360);
	life = 20.0f;
	cameraDistance = 0.0f;
}


TParticleSystem::~TParticleSystem(){
	m_lastUsedParticle = 0;
	m_center = glm::vec3(0,0,0);
}

TParticleSystem::TParticleSystem(std::string path){
	// Cargamos en el vertex buffer el mesh que vamos a utilizar
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Preparamos el buffer que se utilizara para las posiciones de las particulas
	// Inicializamos el buffer vacio, se rellenara a cada frame con las nuevas posiciones
	glGenBuffers(1, &m_pbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_pbo);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	// Preparamos el buffer que se utiizara para los colores de las particulas
	// Inicializamos el buffer vacio, se rellenara a cada frame con las nuevas posiciones
	glGenBuffers(1, &m_cbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_cbo);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 3 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

	// Preparamos el buffer que se utilizara para los extras de las particulas
	// Inicializamos el buffer vacio, se rellenara a cada frame con las nuevas posiciones
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 2 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	m_program = PARTICLE_SHADER;
	m_particleCount = 0;
	m_lastUsedParticle = 0;

	SetTexture(path);
}

void TParticleSystem::BeginDraw(){
	SendShaderData();

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_particleCount);

	ResetShaderData();
}

void TParticleSystem::EndDraw(){

}

void TParticleSystem::ResetShaderData(){
	Program* myProgram = VideoDriver::GetInstance()->GetProgram(m_program);
	GLuint idProgram = myProgram->GetProgramID();

	GLint indexAttrib = glGetAttribLocation(idProgram, "ParticleCenter");
	glVertexAttribDivisor(indexAttrib, 0);
	indexAttrib = glGetAttribLocation(idProgram, "ParticleColor");
	glVertexAttribDivisor(indexAttrib, 0);
	indexAttrib = glGetAttribLocation(idProgram, "ParticleExtra");
	glVertexAttribDivisor(indexAttrib, 0);
}

void TParticleSystem::SendShaderData(){
	Program* myProgram = VideoDriver::GetInstance()->GetProgram(m_program);
	GLuint idProgram = myProgram->GetProgramID();

	// Le decimos que programa debe utilizar
	glUseProgram(idProgram);

	// Enviamos la matriz MVP
		// Calculamos la matriz MVP

		// PRIMERO DE TODO QUITAMOS LA ROTACION DE LA MATRIZ DE LA PILA
		glm::mat4 m_matrix = m_stack.top();
		m_matrix[0] = glm::vec4(1, 0, 0, m_matrix[0][3]);
		m_matrix[1] = glm::vec4(0, 1, 0, m_matrix[1][3]);
		m_matrix[2] = glm::vec4(0, 0, 1, m_matrix[2][3]);

		// SEGUIDAMENTE COGEMOS LA ROTACION DE LA CAMARA Y LA INVERTIMOS
		// DE ESTA FORMA CONSEGUIMOS QUE SIEMPRE MIRE A LA CAMARA
		glm::mat3 m_view = ViewMatrix;
		m_view = glm::inverse(m_view);

		m_matrix[0] = glm::vec4(m_view[0][0], m_view[0][1], m_view[0][2], m_matrix[0][3]);
		m_matrix[1] = glm::vec4(m_view[1][0], m_view[1][1], m_view[1][2], m_matrix[1][3]);
		m_matrix[2] = glm::vec4(m_view[2][0], m_view[2][1], m_view[2][2], m_matrix[2][3]);

		glm::mat4 modelView = ViewMatrix * m_matrix;
		glm::mat4 mvpMatrix = ProjMatrix * modelView;

		// SEND THE MATRIX
		GLint indexAttrib = glGetUniformLocation(idProgram, "MVP");
		glUniformMatrix4fv(indexAttrib, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	// Enviamos los vertex basicos
		// Le decimos al shader que el atributo solamente se va a pasar una vez
		indexAttrib = glGetAttribLocation(idProgram, "VertexPosition");

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glVertexAttribPointer(indexAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glVertexAttribDivisor(indexAttrib, 0);
		glEnableVertexAttribArray(indexAttrib);

	// Enviamos el centro de las particulas
		// Le decimos al shader que el atributo se le va a pasar una vez por particula
		indexAttrib = glGetAttribLocation(idProgram, "ParticleCenter");

		glBindBuffer(GL_ARRAY_BUFFER, m_pbo);
		glVertexAttribPointer(indexAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glVertexAttribDivisor(indexAttrib, 1);
		glEnableVertexAttribArray(indexAttrib);

	// Enviamos el color de las particulas
		// Le decimos al shader que el atributo se le va a pasar una vez por particula
		indexAttrib = glGetAttribLocation(idProgram, "ParticleColor");

		glBindBuffer(GL_ARRAY_BUFFER, m_cbo);
		glVertexAttribPointer(indexAttrib, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0);

		glVertexAttribDivisor(indexAttrib, 1);
		glEnableVertexAttribArray(indexAttrib);

	// Enviamos los extras de las particulas
		// Le decimos al shader que el atributo se le va a pasar una vez por particula
		indexAttrib = glGetAttribLocation(idProgram, "ParticleExtra");

		glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
		glVertexAttribPointer(indexAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glVertexAttribDivisor(indexAttrib, 1);
		glEnableVertexAttribArray(indexAttrib);

	if(m_texture != nullptr){
		GLuint TextureID = glGetUniformLocation(idProgram, "myTextureSampler");
		glUniform1i(TextureID, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureId());
	}
}

void TParticleSystem::AddNewParticles(){
	int size = 10;
	for(int i=0; i<size; i++){
		int pos = FindUnusedParticle();
		m_particleContainer[pos].InitParticle();
	}
}


void TParticleSystem::Update(float deltaTime){
	// Anyadimos las particulas nuevas
	AddNewParticles();

	m_particleCount = 0;
	for(int i=0; i<m_maxParticles; i++){

	    Particle& p = m_particleContainer[i]; // shortcut

	    if(p.life > 0.0f){

	        // Decrease life
	        p.life -= deltaTime;
	        if (p.life > 0.0f){

	            // Simulate simple physics : gravity only, no collisions
	            //p.speed += glm::vec3(0.0f,-0.01f, 0.0f) * deltaTime * 0.5f;
				p.speed += glm::vec3(0.0f,0.5f, 0.0f) * deltaTime * 0.5f;
	            p.pos += p.speed * deltaTime;

	            p.cameraDistance = 1.0f;

	            // Fill the GPU buffer
	            m_particlePositionData[3*m_particleCount+0] = p.pos.x + p.translation.x;
	            m_particlePositionData[3*m_particleCount+1] = p.pos.y + p.translation.y;
	            m_particlePositionData[3*m_particleCount+2] = p.pos.z + p.translation.z;
	            
	            m_particlesColorData[3*m_particleCount+0] = p.r;
	            m_particlesColorData[3*m_particleCount+1] = p.g;
	            m_particlesColorData[3*m_particleCount+2] = p.b;

	            m_particlesExtra[2*m_particleCount+0] = p.size;
	            m_particlesExtra[2*m_particleCount+1] = p.rotation;

	            m_particleCount++;

	        }else{
	            // Particles that just died will be put at the end of the buffer in SortParticles();
	            p.cameraDistance = -1.0f;
	        }

	    }
	}

	// Rellenamos los buffers
	glBindBuffer(GL_ARRAY_BUFFER, m_pbo);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_particleCount * sizeof(GLfloat) * 3, m_particlePositionData);

	glBindBuffer(GL_ARRAY_BUFFER, m_cbo);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 3 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_particleCount * sizeof(GLubyte) * 3, m_particlesColorData);

	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 2 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_particleCount * sizeof(GLfloat) * 2, m_particlesExtra);

}

int TParticleSystem::FindUnusedParticle(){
	// Para hacerlo mas eficiento empezamos a buscar desde la ultima particula actualizada
	for(int i=m_lastUsedParticle; i<m_maxParticles; i++){
		if(m_particleContainer[i].life < 0.0f){
			m_lastUsedParticle = i;
			return i;
		}
	}

	// En el caso de llegar hasta el final y no encontrar ninguna, probamos desde el inicio hasta el ultimo pillado
	for(int i=0; i<m_lastUsedParticle; i++){
		if(m_particleContainer[i].life < 0.0f){
			m_lastUsedParticle = i;
			return i;
		}
	}

	// En el caso de no haber encontrado ninguna particula sobreescribimos la primera
	return 0;
}

void TParticleSystem::SetTranslate(glm::vec3 position){
	for(int i=0; i<m_maxParticles; i++){
		m_particleContainer[i].translation.x += position.x;
		m_particleContainer[i].translation.y += position.y;
		m_particleContainer[i].translation.z += position.z;
	}
}

void TParticleSystem::Translate(glm::vec3 position){
	for(int i=0; i<m_maxParticles; i++){
		m_particleContainer[i].translation -= position;
	}
}

void TParticleSystem::SetTexture(std::string path){
	if(path.compare("") == 0) m_texture = TResourceManager::GetInstance()->GetResourceTexture(VideoDriver::GetInstance()->GetAssetsPath() + "/textures/PerfectCookie.png");
	else m_texture = TResourceManager::GetInstance()->GetResourceTexture(path);
}