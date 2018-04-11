#ifndef TANIMATION_H
#define TANIMATION_H

#include "TMesh.h"

class TAnimation: public TMesh{
public:
	TAnimation();
	~TAnimation();

	//void BeginDraw() override;
    void SetPaths(int frames, std::string paths[]);
    void SetFrame(int frame = 0);
    void UpdateAnimation(float deltatime);

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
	virtual	bool CheckOclusion();
*/

private:
    std::vector <TResourceMesh*> m_meshes;
    int m_frames;

    int m_actualFrame;
    float m_animTime;
};

#endif