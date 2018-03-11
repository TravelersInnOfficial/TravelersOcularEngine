#include "TResourceMesh.h"
#include "./../Loaders/TObjectLoader.h"
#include "./../TResourceManager.h"
#include "./../TOcularEngine/VideoDriver.h"

#include <GL/glew.h>

TResourceMesh::TResourceMesh(std::string name){
	m_name = name;
	m_basicTexture = nullptr;
	m_basicMaterial = nullptr;
	m_vertices = std::vector<glm::vec3>();

	// Inicializamos los buffer
	m_vbo = 0;
	glGenBuffers(1, &m_vbo);

	m_ebo = 0;
	glGenBuffers(1, &m_ebo);

	m_uvbo = 0;
	glGenBuffers(1, &m_uvbo);

	m_nbo = 0;
	glGenBuffers(1, &m_nbo);

	LoadFile();
	if(m_basicTexture == nullptr){
		m_basicTexture = TResourceManager::GetInstance()->GetResourceTexture(VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_texture.png");
	}
}

TResourceMesh::TResourceMesh(){
	m_name = "";
	m_basicTexture = nullptr;
	m_basicMaterial = nullptr;
	m_vertices = std::vector<glm::vec3>();

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
	glDeleteBuffers(1, &m_vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_ebo);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_uvbo);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_nbo);
}

void TResourceMesh::AddTexture(TResourceTexture* texture){
	m_basicTexture = texture;
}

void TResourceMesh::AddMaterial(TResourceMaterial* material){
	m_basicMaterial = material;
}

bool TResourceMesh::LoadFile(){
	bool toRet = TObjectLoader::LoadObjAssimp(this, &m_vertices);
	SetLoaded(toRet);
	return toRet;
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

std::vector<glm::vec3> TResourceMesh::GetVerticesArray(){
	return m_vertices;
}