#include "TAnimation.h"
#include <GL/glew.h>
#include "../TOcularEngine/VideoDriver.h"

// Constructor
TAnimation::TAnimation() : TMesh("","") {
    //m_meshes = std::vector<TResourceMesh*>();
	m_id = "";

    m_animTime = 0.0f;
	m_actualFrame = 0;
}

// Destructor
TAnimation::~TAnimation(){ }

void TAnimation::SetPaths(std::string ID, int frames, std::string paths[], int fps){
	m_id = ID;						// Change actual animation to this id
	AnimData data;
	m_anims[m_id] = data;			// add new animation

	// set animation data
    m_anims[m_id].frames = frames;
	m_anims[m_id].fps = fps;
    m_anims[m_id].meshes.clear();
	// add all paths to the animation vector
    for (int i = 0; i < frames; i++){
        m_anims[m_id].meshes.push_back(TResourceManager::GetInstance()->GetResourceMesh(paths[i]));
	}
	
	// Change actual mesh to the actual animation first frame
	m_mesh = m_anims[m_id].meshes[0];
}

void TAnimation::UpdateAnimation(float deltatime){
	// Update animation time
	m_animTime += deltatime;			// animTime tracks seconds of the animation

	// Total seconds of animation
	float max_duration = (float)m_anims[m_id].frames / (float)m_anims[m_id].fps;

	// Check if time is higher than max duration
	if(m_animTime > max_duration) m_animTime = 0.0f;
	
	// next frame to draw
	int nextFrame = m_animTime / max_duration * m_anims[m_id].frames;
	
	// If next frame is diferent from actual frame, set actual frame
	if(nextFrame != m_actualFrame){
		// Update animation mesh to correpondent
		m_mesh = m_anims[m_id].meshes[nextFrame];
		m_actualFrame = nextFrame;
	}

	//std::cout << " frames: "<< frames << " max_duration: "<< max_duration;
	//std::cout<< " Animation time: "<< m_animTime << " Frame: "<< nextFrame;
	//std::cout<< "\n";
}

void TAnimation::ChangeAnim(std::string ID, int fps){
	m_id = ID;
	m_anims[m_id].fps = fps;
	m_animTime = 0.0f;
}
