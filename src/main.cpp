#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"

#include "EventHandler.h"

void CreateTree(){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();

	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df rot = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df scale = toe::core::TOEvector3df(1.0f, 1.0f, 1.0f);
	toe::core::TOEvector4df color = toe::core::TOEvector4df(1.0f, 1.0f, 1.0f, 1.0f);
	float attenuation = 0.05f;
	std::string path = "";

	pos = toe::core::TOEvector3df(0, 0, 0);
	TFMesh* meshOne = nullptr;
	meshOne = toe::AddCube(pos, rot, scale);
	meshOne->SetTexture("./../assets/textures/cube.png");
	meshOne->SetInvisible();

	pos = toe::core::TOEvector3df(-1.25f, 0.0f, 0.0f);
	path = "./../assets/models/table.obj";
	TFMesh* meshTwo = sm->AddMesh(pos, rot, scale, path);

	pos = toe::core::TOEvector3df(-1.0f, 0, -1.0f);
	color = toe::core::TOEvector4df(1.0f, 1.0f, 1.0f, 1.0f);
	TFLight* light1 = sm->AddLight(pos, rot, color, attenuation);

	TFMesh* dom = (TFMesh*)sm->AddDome();

	pos = toe::core::TOEvector3df(0.0f, 1.4f, 0.0f);
	meshTwo->AddBillboard(pos, "Wizard", 0.2f);
	
	pos = toe::core::TOEvector3df(-.7f, 2.1f, 0.0f);
	meshOne->AddBillboard(pos, "Flechas para MOVER MESH");
	pos = toe::core::TOEvector3df(-1.0f, 1.9f, 0.0f);
	meshOne->AddBillboard(pos, "WASD para ROTAR MESH");
}

int main(){
	VideoDriver::m_assetsPath = "./../assets";
	EventHandler* handler = new EventHandler();	
	VideoDriver* VDriv = toe::GetVideoDriver();
	SceneManager* sceneManager = VDriv->GetSceneManager();
	
	VDriv->CreateWindows("TOE Demonstrative Application", VDriv->GetScreenResolution(), true);
	VDriv->SetClearScreenColor(toe::core::TOEvector4df(0.7, 0.7, 1, 1));
	VDriv->SetIODriver(handler);
	VDriv->SetMouseVisibility(false);

	CreateTree();
	TFCamera* myCamera = sceneManager->AddCamera();

	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	TFParticleSystem* ps = sm->AddParticleSystem(toe::core::TOEvector3df(1.25f,-0.5,0), toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df(1,1,1));
	
	handler->screenCenterX = VDriv->GetScreenResolution().X/2;
	handler->screenCenterY = VDriv->GetScreenResolution().Y/2;

	TFSprite* sprite = toe::AddSprite("",toe::core::TOEvector2df(VDriv->GetScreenResolution().X - 534/3.5f, 0), toe::core::TOEvector2df(534/3.5f,624/3.5f));
	sprite->SetTexture(VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_sprite.png");

	while(!EventHandler::m_close){
		VDriv->SetMouseVisibility(true);
		VDriv->Update();
		VDriv->Draw();
		VDriv->SetCursorPosition(VDriv->GetScreenResolution().X/2,VDriv->GetScreenResolution().Y/2);
		ps->Update(0.16f);
		myCamera->SetTranslate(toe::core::TOEvector3df(EventHandler::xdist, EventHandler::ydist, EventHandler::zdist));
		myCamera->SetRotation(toe::core::TOEvector3df(EventHandler::xdistGiro, EventHandler::ydistGiro, EventHandler::zdistGiro));
	}

	VDriv->CloseWindow();
    return EXIT_SUCCESS;
}
