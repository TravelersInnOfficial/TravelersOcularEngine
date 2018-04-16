#include "TAnimation.h"
#include <GL/glew.h>
#include "../TOcularEngine/VideoDriver.h"

// Constructor
TAnimation::TAnimation() : TMesh("","") {
	m_id = "";

    m_animTime = 0.0f;
	m_actualFrame = 0;
	m_boundMaster = nullptr;
}

// Destructor
TAnimation::~TAnimation(){ }

void TAnimation::SetPaths(std::string ID, int frames, std::string paths[], int fps){
	m_id = ID;					// Change actual animation to this id
	AnimData data;
	m_anims[ID] = data;			// add new animation

	// set animation data
    m_anims[ID].frames = frames;
	m_anims[ID].fps = fps;

    m_anims[ID].meshes.clear();
	// add all paths to the animation vector
    for (int i = 0; i < frames; i++){
        m_anims[ID].meshes.push_back(TResourceManager::GetInstance()->GetResourceMesh(paths[i]));
	}
	
	// Change actual mesh to the actual animation first frame
	m_mesh = m_anims[ID].meshes[0];
}

void TAnimation::UpdateAnimation(float deltatime){
	if(m_queue.size() > 0){
		// Update animation time
		m_animTime += deltatime;			// animTime tracks seconds of the animation
		
		// Total seconds of animation
		float max_duration = (float)m_anims[m_queue.top()].frames / (float)m_anims[m_queue.top()].fps;

		// Check if animation is over
		if(m_animTime > max_duration) {
			m_animTime = 0.0f;

			// If this animation is not the last of the stack, play the next one
			if(m_queue.size() > 1){
				m_queue.pop();

				// If this animation has an animation master, we change the time to sync both animations
				if(m_boundMaster!=nullptr) m_animTime = m_boundMaster->GetAnimTime();
			}
		}
		
		// Next frame to draw
		int nextFrame = m_animTime / max_duration * m_anims[m_queue.top()].frames;
		
		// If next frame is diferent from actual frame, set actual frame
		if(nextFrame != m_actualFrame){
			// Update animation mesh to correpondent
			m_mesh = m_anims[m_queue.top()].meshes[nextFrame];
			m_actualFrame = nextFrame;
		}
	}
}

void TAnimation::ChangeAnim(std::string ID, int fps){
	// Find if exists animation, then change the looping animation
	if (m_anims.find(ID) != m_anims.end()){
		m_id = ID;
		m_anims[ID].fps = fps;
		m_animTime = 0.0f;

		m_queue.empty();
		m_queue.push(ID);
	}
}


void TAnimation::PlayAnim(std::string ID, int fps){
	// Find if exists animation, then play once the animation
	if (m_anims.find(ID) != m_anims.end()){
		m_id = ID;
		m_anims[ID].fps = fps;
		m_animTime = 0.0f;

		m_queue.push(ID);
	}
}

void TAnimation::BindSyncAnimMaster(TAnimation* master){
	m_boundMaster = master;
}

int TAnimation::GetActualFrame(){
	return m_actualFrame;
}

float TAnimation::GetAnimTime(){
	return m_animTime;
}