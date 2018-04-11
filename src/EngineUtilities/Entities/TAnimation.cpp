#include "TAnimation.h"
#include <GL/glew.h>
#include "../TOcularEngine/VideoDriver.h"

// Constructor
TAnimation::TAnimation() : TMesh("","") {
    //m_meshes = std::vector<TResourceMesh*>();
    m_frames = -1;

    m_animTime = 0.0f;
	m_actualFrame = 0;
}

// Destructor
TAnimation::~TAnimation(){ }

/*
void TAnimation::BeginDraw(){
	if(m_mesh != nullptr && !m_drawingShadows && CheckClipping()){

		// Bind and send the data to the VERTEX SHADER
		SendShaderData();
		
		// Bind and draw elements depending of how many vbos
		GLuint elementsBuffer = m_mesh->GetElementBuffer();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBuffer);
		glDrawElements(GL_TRIANGLES, m_mesh->GetElementSize(), GL_UNSIGNED_INT, 0);

		if(m_visibleBB) DrawBoundingBox();
	}
}*/

void TAnimation::SetPaths(int frames, std::string paths[]){
    m_meshes.clear();
    m_frames = frames; 

    for (int i = 0; i < frames; i++){
        m_meshes.push_back(TResourceManager::GetInstance()->GetResourceMesh(paths[i]));
	}

	m_mesh = m_meshes[0];
}

void TAnimation::SetFrame(int frame){
	//if(frame >= 0 && frame < m_frames)
	m_mesh = m_meshes[frame];
}

void TAnimation::UpdateAnimation(float deltatime){
	m_animTime += deltatime;

	if(m_animTime >= m_frames){
		m_animTime = 0.0f;
	}
	
	int actualTime = (int)m_animTime;
	if(actualTime != m_actualFrame){
		SetFrame(actualTime);
		m_actualFrame = actualTime;
	}
}