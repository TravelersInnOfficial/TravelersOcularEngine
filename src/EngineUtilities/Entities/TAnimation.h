#ifndef TANIMATION_H
#define TANIMATION_H

#include "TMesh.h"

class TAnimation: public TMesh{
public:
	TAnimation();
	~TAnimation();

	/**
	 * @brief Begin draw called on tree drawing
	 * 
	 */
	//void BeginDraw() override;

	/**
	 * @brief Set animation Paths of each frame 
	 * 
	 * @param frames: max frames
	 * @param paths: string array of paths
	 */
    void SetPaths(int frames, std::string paths[]);
    
	/**
	 * @brief Updates Animation depending of deltatime
	 * 
	 * @param deltatime: time between frames
	 */
	void UpdateAnimation(float deltatime);

private:
	// Animation data
	std::vector <TResourceMesh*> m_meshes;		// All resources of each frame of the animation
	int m_frames;								// Max frames of animation

	// Updating animation
    int m_actualFrame;							// Actual frame beeing drawn in the scene
    float m_animTime;							// Actual time of animation (0 - m_frames)
};

/*  INHERITED VARIABLES AND METHODS
public:
	void LoadMesh(std::string meshPath = "");
	void ChangeTexture(std::string texturePath = "");
	void SetBBVisibility(bool visible);

protected:
    TResourceMesh* 		m_mesh;
	TResourceTexture* 	m_texture;
	TResourceMaterial* 	m_material;
	bool m_visibleBB;
	bool m_drawingShadows;

	void SendShaderData();
	void DrawBoundingBox();	
	virtual	bool CheckClipping() override;	
	virtual	bool CheckOcclusion();
*/


#endif