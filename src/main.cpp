#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"
void CreateTree(TFCamera** myCamera, TFMesh** meshOne, TFMesh** meshTwo, TFMesh** meshThree, TFLight** light1, TFLight** light2){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df rot = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df scale = toe::core::TOEvector3df(1.0f, 1.0f, 1.0f);
	std::string path = "";

	pos = toe::core::TOEvector3df(0, 0, -5);
	*myCamera = sm->AddCamera(pos, rot, true);

	pos = toe::core::TOEvector3df(-1.5f, 0.0f, 0);
	*meshOne = toe::AddCube(pos, rot, scale);
	(*meshOne)->SetTexture("./../assets/textures/cube.png");

	pos = toe::core::TOEvector3df(0.0f, 0.0f, 0.0f);
	path = "./../assets/models/Wizard.obj";
	*meshTwo = sm->AddMesh(pos, rot, scale, path);

	pos = toe::core::TOEvector3df(1.5f, 0.0f, 0.0f);
	path = "./../assets/models/potion.obj";
	*meshThree = sm->AddMesh(pos, rot, scale, path);
	(*meshThree)->SetTexture("./../assets/textures/potion.png");

	toe::core::TOEvector3df lightPos = toe::core::TOEvector3df(0.0f, 0.0f, 0.0f);
	toe::core::TOEvector3df lightRot = toe::core::TOEvector3df(0.0f, 0.0f, 0.0f);
	toe::core::TOEvector4df    color = toe::core::TOEvector4df(1.0f, 1.0f, 1.0f, 1.0f);
	float intensity = 1.0f;
	*light1 = sm->AddLight(lightPos, lightRot, color, intensity);
}

int main(){
	VideoDriver* VDriv = toe::GetVideoDriver();
	VDriv->CreateWindow("Wizards&Warlocks",toe::core::TOEvector2df(800,600));
	VDriv->SetClearScreenColor(toe::core::TOEvector4df(0.7, 0.7, 1, 1));

	TFCamera* myCamera = nullptr;
	TFMesh* meshOne = nullptr;
	TFMesh* meshTwo = nullptr;
	TFMesh* meshThree = nullptr;
	TFLight* light1 = nullptr;
	TFLight* light2 = nullptr;

	CreateTree(&myCamera, &meshOne, &meshTwo, &meshThree, &light1, &light2);

	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0.0f, 1.5f, 0.0f);
	meshOne->AddBillboard(pos, "cube");
	meshTwo->AddBillboard(pos, "mage");
	//meshThree->AddBillboard(pos, "potion");

	while(VDriv->Update()){
		VDriv->Draw();
		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0,VDriv->GetTime()/10,0);
		meshOne->SetRotation(rotation);
		meshTwo->SetRotation(rotation);
		meshThree->SetRotation(rotation);
		if(meshTwo != nullptr) meshTwo->SetTranslate(toe::core::TOEvector3df(VideoDriver::xdist, 0.0f, -VideoDriver::zdist));
	}

    return EXIT_SUCCESS;
}