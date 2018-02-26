#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"

void CreateTree(){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	
	toe::core::TOEvector3df cameraPos = toe::core::TOEvector3df(0, 0, -5);
	toe::core::TOEvector3df cameraRot = toe::core::TOEvector3df(0, 0, 0);
	sm->AddCamera(cameraPos, cameraRot, true);

	toe::core::TOEvector3df meshPos = toe::core::TOEvector3df(5.0f, 3.0f, 0);
	toe::core::TOEvector3df meshRot = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df meshScale = toe::core::TOEvector3df(0.3f, 0.3f, 0.3f);
	toe::AddCube(meshPos, meshRot, meshScale);

	meshPos = toe::core::TOEvector3df(0, 0, 0);
	meshRot = toe::core::TOEvector3df(0, 0, 0);
	meshScale = toe::core::TOEvector3df(1, 1, 1);
	std::string path = "./../assets/models/Wizard.obj";
	sm->AddMesh(meshPos, meshRot, meshScale, path);
}

int main(){
	VideoDriver* VDriv = toe::GetVideoDriver();
	VDriv->CreateWindow("Wizards&Warlocks",toe::core::TOEvector2df(800,600));

	CreateTree();

	VDriv->SetClearScreenColor(toe::core::TOEvector4df(0.7, 0.7, 1, 1));
	while(VDriv->Update()) VDriv->Draw();

    return EXIT_SUCCESS;
}