#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"
static TFMesh* mes;
void CreateTree(){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	
	toe::core::vector3df cameraPos = toe::core::vector3df(0, 0, -5);
	toe::core::vector3df cameraRot = toe::core::vector3df(0, 0, 0);
	sm->AddCamera(cameraPos, cameraRot, true);

	toe::core::vector3df meshPos = toe::core::vector3df(0, 0, 0);
	toe::core::vector3df meshRot = toe::core::vector3df(0, 0, 0);
	toe::core::vector3df meshScale = toe::core::vector3df(1, 1, 1);
	std::string path = "./../assets/models/Wizard.obj";
	mes = sm->AddMesh(meshPos, meshRot, meshScale, path);

	toe::core::vector3df lightPos = toe::core::vector3df(0, 0, 0);
	toe::core::vector3df lightRot = toe::core::vector3df(0, 0, 0);
	toe::core::vector4df    color = toe::core::vector4df(0.8f, 0.8f, 0.8f, 0.0f);;
	sm->AddLight(lightPos, lightRot, color, 0.8f);
}

int main(){
	VideoDriver* VDriv = toe::GetVideoDriver();
	VDriv->CreateWindow("Wizards&Warlocks",toe::core::vector2df(800,600));

	CreateTree();

	VDriv->SetClearScreenColor(toe::core::vector4df(0.2, 0.2, 0.2, 1));
	while(VDriv->Update()) {
		VDriv->Draw();
		mes->SetRotation(toe::core::vector3df(0, VideoDriver::zdist, 0));
	}
    return EXIT_SUCCESS;
}