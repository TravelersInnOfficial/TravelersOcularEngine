#include "TResourceMesh.h"
#include "./../Loaders/TObjectLoader.h"
#include "./../TResourceManager.h"
#include "./../TOcularEngine/VideoDriver.h"

#include <GL/glew.h>

TResourceMesh::TResourceMesh(std::string name){
	// Inicializamos las variables
	m_name = name;
	m_basicTexture = nullptr;
	m_specularMap = nullptr;
	m_bumpMap = nullptr;
	m_basicMaterial = nullptr;

	m_center = glm::vec3(0,0,0);
	m_size = glm::vec3(1,1,1);

	// Inicializamos los buffer
	m_vbo = 0;
	glGenBuffers(1, &m_vbo);

	m_ebo = 0;
	glGenBuffers(1, &m_ebo);

	m_uvbo = 0;
	glGenBuffers(1, &m_uvbo);

	m_nbo = 0;
	glGenBuffers(1, &m_nbo);

	// Cargamos el mesh
	LoadFile();
	// En el caso de que no tenga textura le ponemos una textura blanca por defecto
	if(m_basicTexture == nullptr){
		m_basicTexture = TResourceManager::GetInstance()->GetResourceTexture(VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_texture.png");
	}
	// En el caso de que no tenga mapa de especulares le ponemos una textura blanca por defecto
	if(m_specularMap == nullptr){
		m_specularMap = TResourceManager::GetInstance()->GetResourceTexture(VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_texture.png");
	}
	// En el caso de que no tenga mapa de normales le ponemos por defecto una textura azul (para que no se alteren las normales del objeto)
	if(m_bumpMap == nullptr){
		m_bumpMap = TResourceManager::GetInstance()->GetResourceTexture(VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_bump.png");
	}
}

TResourceMesh::TResourceMesh(){
	// Inicializamos las variables
	m_name = "";
	m_basicTexture = nullptr;
	m_basicMaterial = nullptr;
	m_center = glm::vec3(0,0,0);
	m_size = glm::vec3(0,0,0);

	// Inicializamos los buffer
	m_vbo = 0;
	glGenBuffers(1, &m_vbo);

	m_ebo = 0;
	glGenBuffers(1, &m_ebo);

	m_uvbo = 0;
	glGenBuffers(1, &m_uvbo);

	m_nbo = 0;
	glGenBuffers(1, &m_nbo);
}

TResourceMesh::~TResourceMesh(){
	// Eliminamos el buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteBuffers(1, &m_uvbo);
	glDeleteBuffers(1, &m_nbo);
}

void TResourceMesh::AddBumpMap(TResourceTexture* texture){
	m_bumpMap = texture;
}

void TResourceMesh::AddSpecularMap(TResourceTexture* texture){
	m_specularMap = texture;
}

void TResourceMesh::AddTexture(TResourceTexture* texture){
	m_basicTexture = texture;
}

void TResourceMesh::AddMaterial(TResourceMaterial* material){
	m_basicMaterial = material;
}

bool TResourceMesh::LoadFile(){
	// Cargamos el material haciendo uso de la carga binaria
	// Para utilizar esta carga hemos tenido que tratar de antemano los obj
	bool toRet = TObjectLoader::LoadObjBinary(this);
	SetLoaded(toRet);
	return toRet;
}

TResourceTexture* TResourceMesh::GetBumpMap(){
	return m_bumpMap;
}

TResourceTexture* TResourceMesh::GetSpecularMap(){
	return m_specularMap;
}

TResourceTexture* TResourceMesh::GetTexture(){
	return m_basicTexture;
}

TResourceMaterial* TResourceMesh::GetMaterial(){
	return m_basicMaterial;
}

GLuint TResourceMesh::GetElementBuffer(){
	return m_ebo;
}

GLuint TResourceMesh::GetVertexBuffer(){
	return m_vbo;
}

GLuint TResourceMesh::GetUvBuffer(){
	return m_uvbo;
}

GLuint TResourceMesh::GetNormalBuffer(){
	return m_nbo;
}

void TResourceMesh::SetElementSize(int value){
	m_elementSize = value;
}

int TResourceMesh::GetElementSize(){
	return m_elementSize;
}

void TResourceMesh::SetSize(glm::vec3 size){
	m_size = size;
}

void TResourceMesh::SetCenter(glm::vec3 center){
	m_center = center;
}

glm::vec3 TResourceMesh::GetSize(){
 	return m_size;
}

glm::vec3 TResourceMesh::GetCenter(){
	return m_center;
}
