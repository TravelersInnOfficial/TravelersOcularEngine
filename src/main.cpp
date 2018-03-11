#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"

#include "EventHandler.h"

void CreateTree(TFCamera** myCamera, TFMesh** meshOne, TFMesh** meshTwo, TFMesh** meshThree, TFLight** light1, TFMesh** dom){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();

	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df rot = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df scale = toe::core::TOEvector3df(1.0f, 1.0f, 1.0f);
	toe::core::TOEvector4df color = toe::core::TOEvector4df(1.0f, 1.0f, 1.0f, 1.0f);
	float attenuation = 0.05f;
	std::string path = "";

	pos = toe::core::TOEvector3df(0, 0, -3);
	*myCamera = sm->AddCamera(pos, rot, true);

	//pos = toe::core::TOEvector3df(-1.5f, 0.0f, 0);
	//*meshOne = toe::AddCube(pos, rot, scale);
	//(*meshOne)->SetTexture("./../assets/textures/cube.png");

	pos = toe::core::TOEvector3df(-1.25f, 0.0f, 0.0f);
	rot = toe::core::TOEvector3df(0, 160, 0);
	path = "./../assets/models/Wizard.obj";
	*meshTwo = sm->AddMesh(pos, rot, scale, path);

	//pos = toe::core::TOEvector3df(1.5f, 0.0f, 0.0f);
	//path = "./../assets/models/potion.obj";
	//*meshThree = sm->AddMesh(pos, rot, scale, path);
	//(*meshThree)->SetTexture("./../assets/textures/potion.png");

	pos = toe::core::TOEvector3df(-1.0f, 0, -1.0f);
	color = toe::core::TOEvector4df(1.0f, 1.0f, 1.0f, 1.0f);
	*light1 = sm->AddLight(pos, rot, color, attenuation);

	*dom = (TFMesh*)sm->AddDome();
	
	//*light2 = sm->AddLight(pos, rot, color, attenuation);

	TFRect* rect1 = toe::Add2DRect(toe::core::TOEvector2df(10,10),toe::core::TOEvector2df(10,0));
	//rect1->SetWidth(20);
	//rect1->SetHeight(20);
	//rect1->SetPosX(20);
	//rect1->SetPosY(20);
	//rect1->SetPosition(20,20);
	//rect1->SetSize(20,20);
	toe::core::TOEvector2df newpos = toe::core::TOEvector2df(rect1->GetPosX() + rect1->GetWidth(),rect1->GetPosY() + rect1->GetHeight());
	TFRect* rect2 = toe::Add2DRect(toe::core::TOEvector2df(2,2),newpos);
	rect2->SetColor(0,1,0);

	TFSprite* sprite = toe::AddSprite("",toe::core::TOEvector2df(0,0));
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
	TFMesh* dom = nullptr;
	TFLight* light1 = nullptr;

	CreateTree(&myCamera, &meshOne, &meshTwo, &meshThree, &light1, &dom);
	
	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0.0f, 1.4f, 0.0f);
	meshTwo->AddBillboard(pos, "Wizard", 0.2f);

	VDriv->SetMouseVisibility(false);

	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	TFParticleSystem* ps = sm->AddParticleSystem(toe::core::TOEvector3df(1.25f,-0.5,0), toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df(1,1,1));

	while(!EventHandler::m_close){
		VDriv->Update();
		VDriv->Draw();
		ps->Update(0.16f);
		if(meshTwo != nullptr){
			meshTwo->SetTranslate(toe::core::TOEvector3df(EventHandler::xdist, EventHandler::ydist, EventHandler::zdist));
			meshTwo->SetRotation(toe::core::TOEvector3df(EventHandler::xdistGiro, EventHandler::ydistGiro, 0));
		}
	}

	VDriv->CloseWindow();
    return EXIT_SUCCESS;
}
