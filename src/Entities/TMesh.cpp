#include "TMesh.h"

#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include "../TOcularEngine/VideoDriver.h"

TMesh::TMesh(std::string meshPath, std::string texturePath){
	LoadMesh(meshPath);
	ChangeTexture(texturePath);
	m_program = STANDARD_SHADER;
}

TMesh::~TMesh(){
}

void TMesh::LoadMesh(std::string meshPath){
	if(meshPath == "") meshPath = "./../assets/models/cube.obj";
	m_mesh = TResourceManager::GetInstance()->GetResourceMesh(meshPath);
}

void TMesh::ChangeTexture(std::string texturePath){
	if(texturePath != "") m_texture = TResourceManager::GetInstance()->GetResourceTexture(texturePath);
	else m_texture = nullptr;
}

void TMesh::BeginDraw(){
	// Bind and send the data to the VERTEX SHADER
	SendShaderData();
	// Bind and draw elements depending of how many vbos
	GLuint elementsBuffer = m_mesh->GetElementBuffer();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBuffer);
	glDrawElements(GL_TRIANGLES, m_mesh->GetElementSize(), GL_UNSIGNED_INT, 0);
}

void TMesh::EndDraw(){
}

void TMesh::SendShaderData(){
	Program* myProgram = VideoDriver::GetInstance()->GetProgram(m_program);

    // --------------------------------------------------------ENVIAMOS LOS VERTICES
    // BIND VERTEX
    GLuint vertexBuffer = m_mesh->GetVertexBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// SEND THE VERTEX
	GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");
	glVertexAttribPointer(posAttrib,3, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	// --------------------------------------------------------ENVIAMOS LAS NORMALS
	// BIND THE NORMALS
    GLuint normalBuffer = m_mesh->GetNormalBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);

	// SEND THE NORMALS
	GLuint normAttrib = glGetAttribLocation(myProgram->GetProgramID(), "VertexNormal");
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
	glEnableVertexAttribArray(normAttrib);

	// --------------------------------------------------------ENVIAMOS LAS UV
	// BIND THE UV
    GLuint uvBuffer = m_mesh->GetUvBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);

	// SEND THE UV
	GLuint uvAttrib = glGetAttribLocation(myProgram->GetProgramID(), "TextureCoords");
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
	glEnableVertexAttribArray(uvAttrib);

	// --------------------------------------------------------ENVIAMOS LAS MATRICES
	// SEND THE MODELVIEW MATRIX
	glm::mat4 modelView = ViewMatrix * m_stack.top();
	GLint mvLocation = glGetUniformLocation(myProgram->GetProgramID(), "ModelViewMatrix");
	glUniformMatrix4fv(mvLocation, 1, GL_FALSE, glm::value_ptr(modelView));

	// SEND THE MODELVIEWPROJECTION MATRIX
	glm::mat4 mvpMatrix = ProjMatrix * modelView;
	GLint mvpLocation = glGetUniformLocation(myProgram->GetProgramID(), "MVP");
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	// SEND THE NORMAL MATRIX
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(modelView));
	GLint normalMLocation = glGetUniformLocation(myProgram->GetProgramID(), "NormalMatrix");
	glUniformMatrix3fv(normalMLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	// --------------------------------------------------------ENVIAMOS LA TEXTURA
	TResourceTexture* currentTexture = nullptr;
	if(m_texture != nullptr){
		currentTexture = m_texture;
	}else if(m_mesh!=nullptr){
		currentTexture = m_mesh->GetTexture();
	}

	if(currentTexture!=nullptr){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, currentTexture->GetTextureId());
		GLuint TextureID = glGetUniformLocation(myProgram->GetProgramID(), "myTextureSampler");
		glUniform1i(TextureID, 0);
	}
}
