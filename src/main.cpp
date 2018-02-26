#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"

void CreateTree(TFCamera* myCamera, TFMesh* meshOne, TFMesh* meshTwo, TFMesh* meshThree){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df rot = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df scale = toe::core::TOEvector3df(1.0f, 1.0f, 1.0f);
	std::string path = "";

	pos = toe::core::TOEvector3df(0, 0, -5);
	myCamera = sm->AddCamera(pos, rot, true);

	pos = toe::core::TOEvector3df(-1.5f, 0.0f, 0);
	meshOne = toe::AddCube(pos, rot, scale);
	meshOne->SetTexture("./../assets/textures/cube.png");

	pos = toe::core::TOEvector3df(0.0f, 0.0f, 0.0f);
	path = "./../assets/models/Wizard.obj";
	meshTwo = sm->AddMesh(pos, rot, scale, path);

	pos = toe::core::TOEvector3df(1.5f, 0.0f, 0.0f);
	path = "./../assets/models/potion.obj";
	meshThree = sm->AddMesh(pos, rot, scale, path);
	meshThree->SetTexture("./../assets/textures/potion.png");
}

int main(){
	VideoDriver* VDriv = toe::GetVideoDriver();
	VDriv->CreateWindow("Wizards&Warlocks",toe::core::TOEvector2df(800,600));

	TFCamera* myCamera = nullptr;
	TFMesh* meshOne = nullptr;
	TFMesh* meshTwo = nullptr;
	TFMesh* meshThree = nullptr;

	CreateTree(myCamera, meshOne, meshTwo, meshThree);

	VDriv->SetClearScreenColor(toe::core::TOEvector4df(0.7, 0.7, 1, 1));
	while(VDriv->Update()) VDriv->Draw();

    return EXIT_SUCCESS;
}