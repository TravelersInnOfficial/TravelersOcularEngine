#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"

#include "EventHandler.h"
#include "ColoredParticle.h"

#include <glm/gtc/matrix_transform.hpp>
#include <ShaderTypes.h>
#include <vector>

std::vector<TFMesh*> sceneObjects;
int currentShader = 0;

void ChangeShader(int newShader){
	if(newShader != currentShader){
		currentShader = newShader;
		for(int i = 0; i < sceneObjects.size(); i++){
			if(currentShader == 0) sceneObjects.at(i)->SetProgram(STANDARD_SHADER);
			if(currentShader == 1) sceneObjects.at(i)->SetProgram(BARREL_SHADER);
			if(currentShader == 2) sceneObjects.at(i)->SetProgram(DISTORSION_SHADER);
			if(currentShader == 3) sceneObjects.at(i)->SetProgram(FISHEYE_SHADER);
		}
	}
}

void CreateTree(TFMesh*& m1, TFMesh*& m2, TFMesh*& m3){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df rot = toe::core::TOEvector3df(0, 180, 0);
	toe::core::TOEvector3df scale = toe::core::TOEvector3df(1.0f, 1.0f, 1.0f);
	toe::core::TOEvector4df color = toe::core::TOEvector4df(1.0f, 1.0f, 1.0f, 1.0f);
	float attenuation = 0.0001f;
	std::string path = "";
	TFMesh* mesh = nullptr;
	TFLight* l = nullptr;

	// PAREDES ###################################################

	// FLOOR
	pos = toe::core::TOEvector3df(0.0f, -2.0f, 0.0f);
	scale = toe::core::TOEvector3df(50.0f, 0.25f, 50.0f);
	mesh = sm->AddMesh(pos, rot, scale, "");
	sceneObjects.push_back(mesh);

	// IZDA
	pos = toe::core::TOEvector3df(-25.0f, 8.0f, 0.0f);
	scale = toe::core::TOEvector3df(0.25f, 20.0f, 50.0f);
	mesh = sm->AddMesh(pos, rot, scale, "");
	sceneObjects.push_back(mesh);

	// DCHA
	pos = toe::core::TOEvector3df(25.0f, 8.0f, 0.0f);
	scale = toe::core::TOEvector3df(0.25f, 20.0f, 50.0f);
	mesh = sm->AddMesh(pos, rot, scale, "");
	sceneObjects.push_back(mesh);

	// BACK
	pos = toe::core::TOEvector3df(0.0f, 8.0f, 25.0f);
	scale = toe::core::TOEvector3df(50.0f, 20.0f, 0.25f);
	mesh = sm->AddMesh(pos, rot, scale, "");
	sceneObjects.push_back(mesh);

	// TEAPOTS ###################################################
	pos = toe::core::TOEvector3df(-7.0f, -1.8f, 10.0f);
	scale = toe::core::TOEvector3df(0.7f, 0.7f, 0.7f);
	mesh = sm->AddMesh(pos, rot, scale, "./../assets/models/teapot.obj");
	mesh->SetTexture("./../assets/textures/checkerboard_texture.jpg");
	mesh->SetBoundBox(true);
	sceneObjects.push_back(mesh);

	pos = toe::core::TOEvector3df(0.0f, -1.8f, 10.0f);
	scale = toe::core::TOEvector3df(0.55f, 0.55f, 0.55f);
	mesh = sm->AddMesh(pos, rot, scale, "./../assets/models/teapot.obj");
	mesh->SetTexture("./../assets/textures/teapot_texture1.jpg");
	mesh->SetBoundBox(true);
	sceneObjects.push_back(mesh);

	pos = toe::core::TOEvector3df(7.0f, -1.8f, 10.0f);
	scale = toe::core::TOEvector3df(0.4f, 0.4f, 0.4f);
	mesh = sm->AddMesh(pos, rot, scale, "./../assets/models/teapot.obj");
	mesh->SetTexture("./../assets/textures/teapot_texture2.jpg");
	mesh->SetBoundBox(true);
	sceneObjects.push_back(mesh);

	// LUCES ###################################################
	scale = toe::core::TOEvector3df(0.5f, 0.5f, 0.5f);
	rot = toe::core::TOEvector3df(0, 0, 0);

	// R
	pos = toe::core::TOEvector3df(0.0f, 0.0f, 0.0f);
	color = toe::core::TOEvector4df(1.0f, 0.0f, 0.0f, 1.0f);
	l = sm->AddLight(pos, rot, color, attenuation);

	m1 = sm->AddMesh();
	m1->CreateSphere();
	pos = toe::core::TOEvector3df(0.0f, 1.0f, 0.0f);
	m1->AddBillboard(pos, "RED LIGHT SOURCE", 0.35f);
	m1->AddChild(l);
	sceneObjects.push_back(m1);

	// G
	pos = toe::core::TOEvector3df(0.0f, 0.0f, 0.0f);
	color = toe::core::TOEvector4df(0.0f, 1.0f, 0.0f, 1.0f);
	l = sm->AddLight(pos, rot, color, attenuation);
	
	m2 = sm->AddMesh();
	m2->CreateSphere();
	pos = toe::core::TOEvector3df(0.0f, 1.0f, 0.0f);
	m2->AddBillboard(pos, "GREEN LIGHT SOURCE", 0.35f);
	m2->AddChild(l);
	sceneObjects.push_back(m2);

	// B
	pos = toe::core::TOEvector3df(0.0f, 0.0f, 0.0f);
	color = toe::core::TOEvector4df(0.0f, 0.0f, 1.0f, 1.0f);
	l = sm->AddLight(pos, rot, color, attenuation);
	
	m3 = sm->AddMesh();
	m3->CreateSphere();
	pos = toe::core::TOEvector3df(0.0f, 1.0f, 0.0f);
	m3->AddBillboard(pos, "BLUE LIGHT SOURCE", 0.35f);
	m3->AddChild(l);
	sceneObjects.push_back(m3);
	
	// DOME ###################################################
	sm->AddDome();
}

int main(){
	VideoDriver::m_assetsPath = "./../assets";
	EventHandler* handler = new EventHandler();	
	VideoDriver* VDriv = toe::GetVideoDriver();
	SceneManager* sm = VDriv->GetSceneManager();
	
	VDriv->CreateWindows("TOE Demonstrative Application", VDriv->GetScreenResolution(), true);
	VDriv->SetClearScreenColor(toe::core::TOEvector4df(0.7, 0.7, 1, 1));
	VDriv->SetIODriver(handler);
	VDriv->SetMouseVisibility(false);

	TFMesh* lr = nullptr;
	TFMesh* lg = nullptr;
	TFMesh* lb = nullptr;

	CreateTree(lr, lg, lb);

	TFCamera* secondCamera = sm->AddCamera(toe::core::TOEvector3df(0,3,-20));
	TFCamera* myCamera = sm->AddCamera();

	handler->screenCenterX = VDriv->GetScreenResolution().X/2;
	handler->screenCenterY = VDriv->GetScreenResolution().Y/2;

	// PARTICLES
	TFParticleSystem* ps = sm->AddParticleSystem(toe::core::TOEvector3df(-17,0,20), toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df(1,1,1));
	TFParticleSystem* ps1 = sm->AddParticleSystem(toe::core::TOEvector3df(0,0,20), toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df(1,1,1));
	TFParticleSystem* ps2 = sm->AddParticleSystem(toe::core::TOEvector3df(17,0,20), toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df(1,1,1));
	ps->SetManager(new ColoredParticle(true, false, false)); 
	ps1->SetManager(new ColoredParticle(false, true, false));
	ps2->SetManager(new ColoredParticle(false, false, true));
	
	// TOE MANUAL
	TFSprite* manual = toe::AddSprite("",toe::core::TOEvector2df(0, 0), toe::core::TOEvector2df(305,96));
	manual->SetTexture("./../assets/textures/toe_manual.png");

	// TIO LOGO
	TFSprite* logo = toe::AddSprite("",toe::core::TOEvector2df(VDriv->GetScreenResolution().X - 534/3.5f, 0), toe::core::TOEvector2df(534/3.5f,624/3.5f));
	logo->SetTexture("./../assets/textures/default_sprite.png");

	// SUZANNE
	TFMesh* mesh = sm->AddMesh(toe::core::TOEvector3df(0.0f, 6.0f, 0.0f), toe::core::TOEvector3df(0.0f, 0.0f, 0.0f), toe::core::TOEvector3df(2.0f, 2.0f, 2.0f), "./../assets/models/suzanne.obj");
	mesh->AddBillboard(toe::core::TOEvector3df(0.0f, 3.0f, 0.0f), "SUZANNE", 0.5f);
	sceneObjects.push_back(mesh);

	while(!EventHandler::m_close){
		// EVENT HANDLER UPDATE
		handler->Update();

		// ROTATE MESH
		toe::core::TOEvector3df rot = mesh->GetRotation();
		rot.Y += 0.5;
		mesh->SetRotation(rot);

		// ROTATE LIGHTS
		float x = sin(glm::radians(-rot.Y)) * 6.0f;
		float z = cos(glm::radians(-rot.Y)) * 6.0f;
		lr->SetTranslate(toe::core::TOEvector3df(x, 6.0f, z));

		x = sin(glm::radians(-rot.Y + 360.0f / 3.0f)) * 6.0f;
		z = cos(glm::radians(-rot.Y + 360.0f / 3.0f)) * 6.0f;
		lg->SetTranslate(toe::core::TOEvector3df(x, 6.0f, z));

		x = sin(glm::radians(-rot.Y + 360.0f / 1.5f)) * 6.0f;
		z = cos(glm::radians(-rot.Y + 360.0f / 1.5f)) * 6.0f;
		lb->SetTranslate(toe::core::TOEvector3df(x, 6.0f, z));

		// UPDATE PARTICLES
		ps->Update(0.16f);
		ps1->Update(0.16f);
		ps2->Update(0.16f);
		
		// UPDATE CAMERA
		myCamera->SetRotation(toe::core::TOEvector3df(EventHandler::xdistGiro, EventHandler::ydistGiro, EventHandler::zdistGiro));
		myCamera->SetTranslate(toe::core::TOEvector3df(EventHandler::xdist, EventHandler::ydist, EventHandler::zdist));
		
		// UPDATE VDRIVE & PAINT
		VDriv->Update();
		VDriv->BeginDraw();
		VDriv->EndDraw();
		VDriv->SetCursorPosition(VDriv->GetScreenResolution().X/2,VDriv->GetScreenResolution().Y/2);

		ChangeShader(EventHandler::shaderType);
	}

	VDriv->CloseWindow();
    return EXIT_SUCCESS;
}
