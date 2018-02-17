#include "TResourceTexture.h"
#include "../Loaders/TTextureLoader.h"

TResourceTexture::TResourceTexture(std::string name){
	m_name = name;
	LoadFile();
}

TResourceTexture::TResourceTexture(){
	
}

TResourceTexture::~TResourceTexture(){

}

bool TResourceTexture::LoadFile(){
	bool toRet = TTextureLoader::LoadTexture(m_name, &m_imageData, &m_width, &m_height);
	SetLoaded(toRet);

	if(toRet){
		// glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// glBufferData(GL_ARRAY_BUFFER, m_vertex.size() * sizeof(glm::vec3), &m_vertex[0], GL_STATIC_DRAW);
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		// glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexIndex.size() * sizeof(unsigned int), &m_vertexIndex[0], GL_STATIC_DRAW);
	}

	return toRet;
}