#include "TMesh.h"

#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <iostream>
#include <chrono>

TMesh::TMesh(){
	m_program 	= NULL;
	m_mesh 		= TResourceManager::GetInstance()->GetResourceMesh("./../assets/models/Wizard.obj");
	m_texture 	= TResourceManager::GetInstance()->GetResourceTexture("./../assets/textures/Wizard.png");
}

TMesh::~TMesh(){
}

void TMesh::BeginDraw(){
	// Bind and send the data to the VERTEX SHADER
	SendShaderData();
	// Bind and draw elements depending of how many vbos
	GLuint* elementsBuffer = m_mesh->GetElementBuffer();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *elementsBuffer);
	glDrawElements(GL_TRIANGLES, 10000, GL_UNSIGNED_INT, 0);
}

void TMesh::EndDraw(){
}

// PROVISIONAL FUNCTION
void TMesh::SetProgram(Program* prog){
	m_program = prog;
}

void TMesh::SendShaderData(){
	// If there is no Program, exit
	if(m_program == NULL) throw std::runtime_error("SHADER NOT ASSIGNED TO MESH");

    // --------------------------------------------------------ENVIAMOS LOS VERTICES
    // BIND VERTEX
    GLuint* vertexBuffer = m_mesh->GetVertexBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);

	// SEND THE VERTEX
	GLint posAttrib = glGetAttribLocation(m_program->GetProgramID(), "VertexPosition");
	glVertexAttribPointer(posAttrib,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	// --------------------------------------------------------ENVIAMOS LAS UV
	// BIND THE UV
    GLuint* uvBuffer = m_mesh->GetUvBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, *uvBuffer);

	// SEND THE UV
	GLint uvAttrib = glGetAttribLocation(m_program->GetProgramID(), "inUV");
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
	glEnableVertexAttribArray(uvAttrib);

	// --------------------------------------------------------ENVIAMOS LA MATRIZ DE MODELO
	// SEND THE MODEL/VIEW/MATRIX
	GLint viewUniform = glGetUniformLocation(m_program->GetProgramID(), "ModelViewMatrix");
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(m_stack.top()));

	// BIND THE NORMAL
	// GLuint* normalBuffer = m_mesh->GetNormalBuffer();
	// glBindBuffer(GL_ARRAY_BUFFER, *normalBuffer);

	// SEND THE NORMAL
	// GLint normalAttrib = glGetAttribLocation(m_program->GetProgramID(), "vertexNormal");
	// glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float)));
	// glEnableVertexAttribArray(normalAttrib);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureId());
		// Set our "myTextureSampler" sampler to use Texture Unit 0
	GLuint TextureID = glGetUniformLocation(m_program->GetProgramID(), "myTextureSampler");
	glUniform1i(TextureID, 0);
}
	