#ifndef TANIMATION_H
#define TANIMATION_H

#include "TMesh.h"

struct AnimData{
	int frames;								// Max frames of animation
	int fps;									// Speed of animation
	std::vector <TResourceMesh*> meshes;		// All resources of each frame of the animation

	AnimData() : frames(0), fps(0) {}
};

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
    void SetPaths(std::string ID, int frames, std::string paths[], int fps);
    
	/**
	 * @brief Updates Animation depending of deltatime
	 * 
	 * @param deltatime: time between frames
	 */
	void UpdateAnimation(float deltatime);

	/**
	 * @brief Play another animation in loop
	 * 
	 * @param ID: name of the animation
	 * @param fps: speed of animation
	 */
    void ChangeAnim(std::string ID, int fps);

	/**
	 * @brief Play another animation and queue last animation
	 * 
	 * @param ID: name of the animation
	 * @param fps: speed of animation
	 */
	void PlayAnim(std::string ID, int fps);

	/**
	 * @brief Get Actual Animation Frame
	 * 
	 * @return int: frame
	 */
	int GetActualFrame();
	
private:
	void LoadMesh(std::string meshPath = "");

	// Animation data
	std::string m_id;							// Id of the actual animation
	std::stack <std::string> m_queue;			// Queue of animation
	std::map<std::string, AnimData> m_anims;	// all animations availeables

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