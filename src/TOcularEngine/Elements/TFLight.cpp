#include "TFLight.h"
#include "./../VideoDriver.h"

TFLight::TFLight(toe::core::TOEvector3df position, toe::core::TOEvector3df rotation, toe::core::TOEvector4df color, float intensity) : TFNode(){
	CreateEstructure();
	
	TTransform* t = (TTransform*) m_positionNode->GetEntity();
	t->Translate(position.X, position.Y, position.Z);

	t = (TTransform*) m_rotationNode->GetEntity();
	t->Rotate(rotation.X, rotation.Y, rotation.Z);

	glm::vec4 glmColor = glm::vec4(color.X, color.Y, color.X2, color.Y2);
	TColor myColor = TColor(glmColor);
	TLight* light = new TLight(myColor, intensity);
	m_entityNode->SetEntity(light);
}

TFLight::~TFLight(){

}

void TFLight::CreateEstructure(){
	TTransform* pos = new TTransform();
	TTransform* rot = new TTransform();

	m_rotationNode = new TNode(rot);
	m_positionNode = new TNode(m_rotationNode, pos);
	m_entityNode = new TNode();
	m_entityNode->SetParent(m_positionNode);
}

void TFLight::SetColor(toe::core::TOEvector4df color){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	glm::vec4 glmColor = glm::vec4(color.X, color.Y, color.X2, color.Y2);
	TColor myColor = TColor(glmColor);
	myEntity->SetColor(myColor);
}

void TFLight::SetIntensity(float intensity){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetIntensity(intensity);
}

toe::core::TOEvector4df TFLight::GetColor(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	glm::vec4 myColor = myEntity->GetColor().GetRGBA();
	toe::core::TOEvector4df toRetColor = toe::core::TOEvector4df(myColor.x, myColor.y, myColor.z, myColor.w);
	return toRetColor;
}

float TFLight::GetIntensity(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetIntensity();
}

void TFLight::SetActive(bool active){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	myEntity->SetActive(active);
}

bool TFLight::GetActive(){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();
	return myEntity->GetActive();
}

void TFLight::DrawLight(int num){
	TLight* myEntity = (TLight*) m_entityNode->GetEntity();

	if(myEntity->GetActive()){
		Program* myProgram = VideoDriver::GetInstance()->GetProgramVector()[STANDARD_SHADER];
		std::string str = "Light["+std::to_string(num)+"].";
		std::string aux = "";

		glm::vec3 location = m_entityNode->GetTraslation();
		aux = str +"Position";
		GLint lightPLocation = glGetUniformLocation(myProgram->GetProgramID(), aux.c_str());
		glUniform3fv(lightPLocation, 1, glm::value_ptr(location));

		toe::core::TOEvector4df color = GetColor() * GetIntensity();
		glm::vec3 diffuse = glm::vec3(color.X, color.Y, color.X2);
		aux = str +"Diffuse";
		GLint diffLocation = glGetUniformLocation(myProgram->GetProgramID(), aux.c_str());
		glUniform3fv(diffLocation, 1, glm::value_ptr(diffuse));

		glm::vec3 specular = glm::vec3(color.X, color.Y, color.X2);
		aux = str +"Specular";
		GLint specLocation = glGetUniformLocation(myProgram->GetProgramID(), aux.c_str());
		glUniform3fv(specLocation, 1, glm::value_ptr(specular));
	}
}