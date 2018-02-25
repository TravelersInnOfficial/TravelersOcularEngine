#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"

void CreateTree(){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	
	toe::core::vector3df cameraPos = toe::core::vector3df(0, 0, -5);
	toe::core::vector3df cameraRot = toe::core::vector3df(0, 0, 0);
	sm->AddCamera(cameraPos, cameraRot, true);

	toe::core::vector3df meshPos = toe::core::vector3df(0, 0, 0);
	toe::core::vector3df meshRot = toe::core::vector3df(0, 0, 0);
	toe::core::vector3df meshScale = toe::core::vector3df(1, 1, 1);
	std::string path = "./../assets/models/Wizard.obj";
	sm->AddMesh(meshPos, meshRot, meshScale, path);

	toe::AddCube();
}

int main(){
	VideoDriver* VDriv = toe::GetVideoDriver();
	VDriv->CreateWindow("Wizards&Warlocks",toe::core::vector2df(800,600));

	CreateTree();

	VDriv->SetClearScreenColor(toe::core::vector4df(0.7, 0.7, 1, 1));
	while(VDriv->Update()) VDriv->Draw();

    return EXIT_SUCCESS;
}