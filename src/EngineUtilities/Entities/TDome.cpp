#include "TDome.h"
#include <GL/glew.h>
#include "../TOcularEngine/VideoDriver.h"

// String validation when calling father constructor
std::string getModel(){
	return VideoDriver::GetInstance()->GetAssetsPath() + "/models/dome.obj";
}

std::string checkText(std::string path){
	std::string toRet = path;
	if(path.compare("")==0) toRet = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_skydome.jpg";
	return toRet;
}

// Constructor
TDome::TDome(std::string texturePath)
 : TMesh( 	getModel(), 
			checkText(texturePath)) 
{
	// This shader draws without lights
	m_program = TEXT_SHADER;
	// @TODO: cambiar el nombre del shader a uno mas generico
}

// Destructor
TDome::~TDome(){ }

void TDome::BeginDraw(){
	// Bind and send the data to the VERTEX SHADER
    glDepthMask(GL_FALSE);
	SendShaderData();
    
	// Bind and draw elements depending of how many vbos
	GLuint elementsBuffer = m_mesh->GetElementBuffer();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBuffer);
	glDrawElements(GL_TRIANGLES, m_mesh->GetElementSize(), GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);

}

void TDome::EndDraw(){ }

void TDome::DrawShadow(){ }

void TDome::SendShaderData(){
	Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(m_program);

    // -------------------------------------------------------- ENVIAMOS LOS VERTICES
    // BIND VERTEX
    GLuint vertexBuffer = m_mesh->GetVertexBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// SEND THE VERTEX
	GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");
	glVertexAttribPointer(posAttrib,3, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	// -------------------------------------------------------- ENVIAMOS LAS UV
	// BIND THE UV
    GLuint uvBuffer = m_mesh->GetUvBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);

	// SEND THE UV
	GLuint uvAttrib = glGetAttribLocation(myProgram->GetProgramID(), "TextureCoords");
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
	glEnableVertexAttribArray(uvAttrib);

	// -------------------------------------------------------- ENVIAMOS LAS MATRICES
	// SEND THE MODELVIEWPROJECTION MATRIX
	glm::mat4 mvpMatrix = ProjMatrix * ViewMatrix * m_stack.top();
	GLint mvpLocation = glGetUniformLocation(myProgram->GetProgramID(), "MVP");
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

	// -------------------------------------------------------- ENVIAMOS LA TEXTURA
	TResourceTexture* currentTexture = nullptr;
	if(m_texture != nullptr) currentTexture = m_texture;
	else if(m_mesh != nullptr) currentTexture = m_mesh->GetTexture();

	if(currentTexture != nullptr){
		GLuint TextureID = glGetUniformLocation(myProgram->GetProgramID(), "uvMap");
		glUniform1i(TextureID, 0); 

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, currentTexture->GetTextureId());
	}
}
