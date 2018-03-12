#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"

#include "EventHandler.h"

void CreateTree(){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df rot = toe::core::TOEvector3df(0, 180, 0);
	toe::core::TOEvector3df scale = toe::core::TOEvector3df(1.0f, 1.0f, 1.0f);
	toe::core::TOEvector4df color = toe::core::TOEvector4df(1.0f, 1.0f, 1.0f, 1.0f);
	float attenuation = 0.000001f;
	std::string path = "";
	TFMesh* mesh = nullptr;

	// MAGO ###################################################
	pos = toe::core::TOEvector3df(2.00f, 0.0f, 0.0f);
	path = "./../assets/models/Wizard.obj";
	mesh = sm->AddMesh(pos, rot, scale, path);
	pos = toe::core::TOEvector3df(0.0f, 1.4f, 0.0f);
	mesh->AddBillboard(pos, "Wizard", 0.2f);

	// PAREDES ###################################################
	pos = toe::core::TOEvector3df(0.00f, 1.2f, 1.0f);
	scale = toe::core::TOEvector3df(20.0f, 5.0f, 0.1f);
	path = "";
	mesh = sm->AddMesh(pos, rot, scale, path);
	pos = toe::core::TOEvector3df(0.0f, 1.4f, 0.0f);
	mesh->AddBillboard(pos, "Wizard", 0.2f);

	// LUCES ###################################################
	scale = toe::core::TOEvector3df(0.5f, 0.5f, 0.5f);
	pos = toe::core::TOEvector3df(-3.0f, 0, 0);
	color = toe::core::TOEvector4df(1.0f, 0.0f, 0.0f, 1.0f);
	sm->AddLight(pos, rot, color, attenuation);
	mesh = sm->AddMesh(pos);

	pos = toe::core::TOEvector3df(0.0f, 0, 0);
	color = toe::core::TOEvector4df(0.0f, 1.0f, 0.0f, 1.0f);
	sm->AddLight(pos, rot, color, attenuation);
	mesh = sm->AddMesh(pos);

	pos = toe::core::TOEvector3df(3.0f, 0, 0);
	color = toe::core::TOEvector4df(0.0f, 0.0f, 1.0f, 1.0f);
	sm->AddLight(pos, rot, color, attenuation);
	mesh = sm->AddMesh(pos);

	// OTROS ###################################################
	sm->AddDome();
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
