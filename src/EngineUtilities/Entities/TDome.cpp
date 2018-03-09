#include "TDome.h"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "../TOcularEngine/VideoDriver.h"

// Constructor
TDome::TDome(std::string meshPath, std::string texturePath)
 : TMesh(checkModel(meshPath), checkText(texturePath)) {}

// Destructor
TDome::~TDome(){ }

void setMaxAmbientLight(){
	Program* myProgram = VideoDriver::GetInstance()->GetProgramVector()[STANDARD_SHADER];
	GLint ambLocation = glGetUniformLocation(myProgram->GetProgramID(), "SpecialLight.AmbientLight");
	glUniform3fv(ambLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
}

void setBackAmbientLight(){
	Program* myProgram = VideoDriver::GetInstance()->GetProgramVector()[STANDARD_SHADER];

	toe::core::TOEvector3df aux = VideoDriver::GetInstance()->GetSceneManager()->GetAmbientLight();
	glm::vec3 ambientLight(aux.X, aux.Y, aux.Z);
	GLint ambLocation = glGetUniformLocation(myProgram->GetProgramID(), "SpecialLight.AmbientLight");
	glUniform3fv(ambLocation, 1, glm::value_ptr(ambientLight));
}

void TDome::BeginDraw(){
	// Bind and send the data to the VERTEX SHADER
    glDepthMask(GL_FALSE);
	TMesh::SendShaderData();
	setMaxAmbientLight();
    
	// Bind and draw elements depending of how many vbos
	GLuint elementsBuffer = m_mesh->GetElementBuffer();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBuffer);
	glDrawElements(GL_TRIANGLES, m_mesh->GetElementSize(), GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);
	setBackAmbientLight();

}

void TDome::EndDraw(){ }

std::string TDome::checkModel(std::string path){
	std::string toRet = path;
	if(path.compare("")==0) toRet = VideoDriver::GetInstance()->GetAssetsPath() + "/models/dome.obj";
	return toRet;
}

std::string TDome::checkText(std::string path){
	std::string toRet = path;
	if(path.compare("")==0) toRet = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/skydome.jpg";
	return toRet;
}

//./../assets/textures/skydome.jpg