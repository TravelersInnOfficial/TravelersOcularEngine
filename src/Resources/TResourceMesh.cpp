#include "TResourceMesh.h"

TResourceMesh::TResourceMesh(std::string name){
	m_name = name;

	// Inicializamos el buffer
	m_vbo = 0;
	glGenBuffers(1, &m_vbo);

	LoadFile();
}

TResourceMesh::TResourceMesh(){

}

TResourceMesh::~TResourceMesh(){
	// Eliminamos el buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glDeleteBuffers(1, &m_vbo);
}

bool TResourceMesh::LoadFile(){
	bool toRet = TObjLoader::LoadObj(m_name, &m_vertex, &m_textures, &m_normals);
	if(toRet){
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertex.size() * sizeof(glm::vec3), &m_vertex[0], GL_STATIC_DRAW);
	}
	return toRet;
}

GLuint* TResourceMesh::GetVertexBuffer(){
	return &m_vbo;
}