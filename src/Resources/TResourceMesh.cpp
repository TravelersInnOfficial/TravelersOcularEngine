#include "TResourceMesh.h"

TResourceMesh::TResourceMesh(std::string name){
	m_name = name;

	// Inicializamos el buffer
	m_vbo = 0;
	glGenBuffers(1, &m_vbo);

	m_ebo = 0;
	glGenBuffers(1, &m_ebo);

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

bool TResourceMesh::LoadFile(){
	bool toRet = TObjLoader::LoadObjAssimp(m_name, &m_vertex, &m_textures, &m_normals, &m_vertexIndex);
	if(toRet){
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertex.size() * sizeof(glm::vec3), &m_vertex[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexIndex.size() * sizeof(unsigned int), &m_vertexIndex[0], GL_STATIC_DRAW);
	}
	return toRet;
}

GLuint* TResourceMesh::GetElementBuffer(){
	return &m_ebo;
}

GLuint* TResourceMesh::GetVertexBuffer(){
	return &m_vbo;
}

int TResourceMesh::GetVertexSize(){
	return m_vertex.size();
}