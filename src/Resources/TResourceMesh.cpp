#include "TResourceMesh.h"
#include "./../Loaders/TObjectLoader.h"

TResourceMesh::TResourceMesh(std::string name){
	m_name = name;

	// Inicializamos el buffer
	m_vbo = 0;
	glGenBuffers(1, &m_vbo);

	m_ebo = 0;
	glGenBuffers(1, &m_ebo);

	m_uvbo = 0;
	glGenBuffers(1, &m_uvbo);

	m_nbo = 0;
	glGenBuffers(1, &m_nbo);

	LoadFile();
}

TResourceMesh::TResourceMesh(){

}

TResourceMesh::~TResourceMesh(){
	// Eliminamos el buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glDeleteBuffers(1, &m_vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_ebo);
}

std::vector<glm::vec3>* TResourceMesh::GetVertexVector(){
	return &m_vertex;
}
std::vector<glm::vec2>* TResourceMesh::GetUvVector(){
	return &m_textures;
}

std::vector<glm::vec3>* TResourceMesh::GetNormalVector(){
	return &m_normals;
}

void TResourceMesh::AddVertex(glm::vec3 vertex){
	m_vertex.push_back(glm::vec3(vertex));
}

void TResourceMesh::AddUv(glm::vec2 uv){
	m_textures.push_back(uv);
}

void TResourceMesh::AddNormal(glm::vec3 normal){
	m_normals.push_back(glm::vec3(normal));
}

void TResourceMesh::AddVertexIndex(unsigned int index){
	m_vertexIndex.push_back(index);
}

void TResourceMesh::ClearVertex(){
	m_vertex.clear();
}

void TResourceMesh::ClearUv(){
	m_textures.clear();
}

void TResourceMesh::ClearNormal(){
	m_normals.clear();
}

void TResourceMesh::ClearVertexIndex(){
	m_vertexIndex.clear();
}

bool TResourceMesh::LoadFile(){
	bool toRet = TObjectLoader::LoadObjAssimp(this);
	
	if(toRet){
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertex.size() * sizeof(glm::vec3), &m_vertex[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexIndex.size() * sizeof(unsigned int), &m_vertexIndex[0], GL_STATIC_DRAW);
	
		glBindBuffer(GL_ARRAY_BUFFER, m_uvbo);
		glBufferData(GL_ARRAY_BUFFER, m_textures.size()*sizeof(glm::vec2), &m_textures[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);
	}

	SetLoaded(toRet);
	return toRet;
}






GLuint* TResourceMesh::GetElementBuffer(){
	return &m_ebo;
}

GLuint* TResourceMesh::GetVertexBuffer(){
	return &m_vbo;
}

GLuint* TResourceMesh::GetUvBuffer(){
	return &m_uvbo;
}

GLuint* TResourceMesh::GetNormalBuffer(){
	return &m_nbo;
}

int TResourceMesh::GetVertexSize(){
	return m_vertex.size();
}