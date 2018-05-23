#ifndef TANIMATION_H
#define TANIMATION_H

/**
 * @brief Animation class which inherites TMesh and manages internal mesh.
 * 
 * @file TAnimation.h
 */

#include "TMesh.h"

struct AnimData{
	int frames;								// frames - Maximo de frames de la animacion
	int fps;								// fps - Velocidad de la animacion
	std::vector <TResourceMesh*> meshes;	// meshess - Todos los recursos de cada frame de la animacion

	/**
	 * @brief	- Constructor del struct AnimData donde inicializamos sus variables a 0 
	 */
	AnimData() : frames(0), fps(0) {}
};

class TAnimation: public TMesh{
public:
	TAnimation();
	~TAnimation();

	/**
	 * @brief Set animation Paths of each frame 
	 * 
	 * @param frames: max frames
	 * @param paths: string array of paths
	 */
    void SetPaths(std::string ID, int frames, const std::vector<std::string> &paths, int fps);
    
	/**
	 * @brief Updates Animation depending of deltatime
	 * 
	 * @param deltatime: time between frames
	 */
	void UpdateAnimation(float deltatime);

	/**
	 * @brief Plays a new animation in loop
	 * 
	 * @param ID: name of the animation
	 * @param fps: speed of animation
	 */
    void ChangeAnim(std::string ID, int fps);

	/**
	 * @brief Plays a new animation and removes last animation
	 * 
	 * @param ID: name of the animation
	 * @param fps: speed of animation
	 */
	void PlayAnim(std::string ID, int fps);

	/**
	 * @brief Plays a new animation and queue last animation
	 * 
	 * @param ID: name of the animation
	 * @param fps: speed of animation
	 */
	void PlayAnimAbove(std::string ID, int fps);

	/**
	 * @brief After playing an animation, this will take the time from the sync one
	 * 
	 * @param master 
	 */
	void BindSyncAnimMaster(TAnimation* master);

	/**
	 * @brief Get Actual Animation Frame
	 * 
	 * @return int: frame
	 */
	int GetActualFrame();

	/**
	 * @brief Get Actual Animation Time
	 * 
	 * @return float: time
	 */
	float GetAnimTime();

	/**
	 * @brief Get Actual Animation Name
	 * 
	 * @return std::string: id
	 */
	std::string GetActualAnimation();
	
	
private:
	void LoadMesh(std::string meshPath = "");

	// Animation data
	std::map<std::string, AnimData> m_anims;	// m_anims - All animations availeables

	// Updating animation
    int m_actualFrame;							// m_actualFrame - Actual frame beeing drawn in the scene
    float m_animTime;							// m_animTime - Actual time of animation (0 - m_frames)
	std::vector <std::string> m_queue;			// m_boundMaster - Queue of animation
	TAnimation* m_boundMaster;
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