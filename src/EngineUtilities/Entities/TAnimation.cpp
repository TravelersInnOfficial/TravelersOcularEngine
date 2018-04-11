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

void TAnimation::SetPaths(int frames, std::string paths[]){
    m_meshes.clear();
    m_frames = frames; 

    for (int i = 0; i < frames; i++){
        m_meshes.push_back(TResourceManager::GetInstance()->GetResourceMesh(paths[i]));
	}

	m_mesh = m_meshes[0];
}

void TAnimation::UpdateAnimation(float deltatime){
	// Update animation time
	m_animTime += deltatime;

	// Check if time is higher than max frame
	if(m_animTime >= m_frames){
		m_animTime = 0.0f;
	}
	
	// If (int)time is diferent from actual frame, set actual frame
	int actualTime = (int)m_animTime;
	if(actualTime != m_actualFrame){
		// Update animation mesh to correpondent
		m_mesh = m_meshes[actualTime];
		m_actualFrame = actualTime;
	}
}