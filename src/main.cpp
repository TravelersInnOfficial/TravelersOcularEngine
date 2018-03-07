#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"

#include "EventHandler.h"

void CreateTree(TFCamera** myCamera, TFMesh** meshOne, TFMesh** meshTwo, TFMesh** meshThree, TFLight** light1, TFLight** light2){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df rot = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df scale = toe::core::TOEvector3df(1.0f, 1.0f, 1.0f);
	toe::core::TOEvector4df color = toe::core::TOEvector4df(1.0f, 1.0f, 1.0f, 1.0f);
	float intensity = 1.0f;
	std::string path = "";

	pos = toe::core::TOEvector3df(0, 0, -3);
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

	pos = toe::core::TOEvector3df(-5, 0, -5);
	color = toe::core::TOEvector4df(0.8f, 0.8f, 0.8f, 1.0f);
	*light1 = sm->AddLight(pos, rot, color, intensity);

	//pos = toe::core::TOEvector3df(10, 0, 0);
	//color = toe::core::TOEvector4df(0.0f, 0.0f, 1.0f, 1.0f);
	//*light2 = sm->AddLight(pos, rot, color, intensity);
}

int main(){
	VideoDriver::m_assetsPath = "./../assets";
	VideoDriver* VDriv = toe::GetVideoDriver();
	VDriv->CreateWindows("Wizards & Warlocks", toe::core::TOEvector2df(800,600));
	VDriv->SetClearScreenColor(toe::core::TOEvector4df(0.7, 0.7, 1, 1));
    EventHandler* handler = new EventHandler();	
	VDriv->SetIODriver(handler);

	TFCamera* myCamera = nullptr;
	TFMesh* meshOne = nullptr;
	TFMesh* meshTwo = nullptr;
	TFMesh* meshThree = nullptr;
	TFLight* light1 = nullptr;
	TFLight* light2 = nullptr;

	CreateTree(&myCamera, &meshOne, &meshTwo, &meshThree, &light1, &light2);

	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0.0f, 1.65f, 0.0f);
	meshOne->AddBillboard(pos, "Cube");
	meshTwo->AddBillboard(pos, "Wizard", 0.2f);
	meshThree->AddBillboard(pos, "Potion");

	VDriv->SetMouseVisibility(false);

	meshTwo->SetRotation(toe::core::TOEvector3df(0,0,0));

	while(!EventHandler::m_close){
		handler->UpdateMousePosition(0, 0);
		VDriv->Update();
		VDriv->Draw();
		if(meshTwo != nullptr){
			meshTwo->SetTranslate(toe::core::TOEvector3df(EventHandler::xdist, EventHandler::ydist, EventHandler::zdist));
			meshTwo->SetRotation(toe::core::TOEvector3df(EventHandler::xdistGiro, EventHandler::ydistGiro, EventHandler::zdist));
		}
	}

	VDriv->CloseWindow();
    return EXIT_SUCCESS;
}