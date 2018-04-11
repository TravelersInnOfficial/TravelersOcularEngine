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

void CreateTree(TFMesh* ms[], TFLight* ls[], TFLight*& shL){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df rot = toe::core::TOEvector3df(0, 180, 0);
	toe::core::TOEvector3df scale = toe::core::TOEvector3df(1.0f, 1.0f, 1.0f);
	toe::core::TOEvector4df color = toe::core::TOEvector4df(1.0f, 1.0f, 1.0f, 1.0f);
	float attenuation = 0.005f;
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

	// Room model 
	pos = toe::core::TOEvector3df(-2,-1,0);
	scale = toe::core::TOEvector3df(1,1,1);
	mesh = sm->AddMesh(pos, toe::core::TOEvector3df(0,180,0), scale, "./../assets/models/room_thickwalls.obj");
	mesh->SetTexture("./../assets/textures/room.png");
	//mesh->SetBoundBox(true);
	sceneObjects.push_back(mesh);

	// LUCES ###################################################
	scale = toe::core::TOEvector3df(0.5f, 0.5f, 0.5f);
	rot = toe::core::TOEvector3df(0, 0, 0);

	// R
	pos = toe::core::TOEvector3df(0.0f, 0.0f, 0.0f);
	color = toe::core::TOEvector4df(1.0f, 0.0f, 0.0f, 1.0f);
	ls[0] = l = sm->AddLight(pos, rot, color, attenuation);

	ms[0] = sm->AddMesh();
	ms[0]->CreateSphere();
	pos = toe::core::TOEvector3df(0.0f, 1.0f, 0.0f);
	ms[0]->AddBillboard(pos, "LIGHT SOURCE", 0.35f);
	ms[0]->SetTexture("./../assets/textures/red.png");
	ms[0]->AddChild(l);
	sceneObjects.push_back(ms[0]);

	// G
	pos = toe::core::TOEvector3df(0.0f, 0.0f, 0.0f);
	color = toe::core::TOEvector4df(0.0f, 1.0f, 0.0f, 1.0f);
	ls[1] = l = sm->AddLight(pos, rot, color, attenuation);
	
	ms[1] = sm->AddMesh();
	ms[1]->CreateSphere();
	pos = toe::core::TOEvector3df(0.0f, 1.0f, 0.0f);
	ms[1]->AddBillboard(pos, "SPHERE2", 0.35f);
	ms[1]->AddChild(l);
	sceneObjects.push_back(ms[1]);

	// B
	pos = toe::core::TOEvector3df(0.0f, 0.0f, 0.0f);
	color = toe::core::TOEvector4df(0.0f, 0.0f, 1.0f, 1.0f);
	ls[2] = l = sm->AddLight(pos, rot, color, attenuation);
	
	ms[2] = sm->AddMesh();
	ms[2]->CreateSphere();
	pos = toe::core::TOEvector3df(0.0f, 1.0f, 0.0f);
	ms[2]->AddBillboard(pos, "SPHERE3", 0.35f);
	ms[2]->AddChild(l);
	sceneObjects.push_back(ms[2]);
	
	// STATIC BUT DYNAMIC LIGHT
	pos = toe::core::TOEvector3df(0.0f,5.0f,0.0f);
	color = toe::core::TOEvector4df(1.0f, 0.6f, 0.0f, 1.0f);
	shL = sm->AddLight(pos, rot, color, attenuation);
	shL->SetBoundBox(true);	

	// DOME ###################################################
	sm->AddDome();
	sm->AddDynamicLight(shL);
}

void CreateAnimations(TFAnimation*& anim){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();

	toe::core::TOEvector3df pos = toe::core::TOEvector3df(0, 1, -6);
	toe::core::TOEvector3df rot = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df scale = toe::core::TOEvector3df(2.0f, 2.0f, 2.0f);

	anim = sm->AddAnimation(pos, rot, scale);

	std::string paths[] = {
		"./../assets/models/genius/genius_01.obj",
		"./../assets/models/genius/genius_02.obj",
		"./../assets/models/genius/genius_03.obj",
		"./../assets/models/genius/genius_04.obj",
		"./../assets/models/genius/genius_05.obj",
		"./../assets/models/genius/genius_06.obj",
		"./../assets/models/genius/genius_07.obj",
		"./../assets/models/genius/genius_08.obj",
		"./../assets/models/genius/genius_09.obj",
		"./../assets/models/genius/genius_10.obj",
		"./../assets/models/genius/genius_11.obj",
		"./../assets/models/genius/genius_12.obj",
		"./../assets/models/genius/genius_13.obj",
		"./../assets/models/genius/genius_14.obj",
		"./../assets/models/genius/genius_15.obj",
		"./../assets/models/genius/genius_16.obj",
		"./../assets/models/genius/genius_17.obj",
		"./../assets/models/genius/genius_18.obj",
		"./../assets/models/genius/genius_19.obj",
		"./../assets/models/genius/genius_20.obj",
		"./../assets/models/genius/genius_21.obj",
		"./../assets/models/genius/genius_22.obj",
		"./../assets/models/genius/genius_23.obj",
		"./../assets/models/genius/genius_24.obj",
		"./../assets/models/genius/genius_25.obj",
		"./../assets/models/genius/genius_26.obj",
		"./../assets/models/genius/genius_27.obj",
		"./../assets/models/genius/genius_28.obj",
		"./../assets/models/genius/genius_29.obj",
		"./../assets/models/genius/genius_30.obj",
	};

	anim->SetAnimationPaths(30, paths);
	anim->SetBoundBox(true);
	anim->SetTexture("./../assets/textures/red.png");
		
}

void RotateLights(const toe::core::TOEvector3df& rot, TFMesh* l1, TFMesh* l2, TFMesh* l3){
	float radius = 12.0f;
	float height = 8.0f;
	float x = sin(glm::radians(-rot.Y)) * radius;
	float z = cos(glm::radians(-rot.Y)) * radius;
	l1->SetTranslate(toe::core::TOEvector3df(x, height, z));

	x = sin(glm::radians(-rot.Y + 360.0f / 3.0f)) * radius;
	z = cos(glm::radians(-rot.Y + 360.0f / 3.0f)) * radius;
	l2->SetTranslate(toe::core::TOEvector3df(x, height, z));

	x = sin(glm::radians(-rot.Y + 360.0f / 1.5f)) * radius;
	z = cos(glm::radians(-rot.Y + 360.0f / 1.5f)) * radius;
	l3->SetTranslate(toe::core::TOEvector3df(x, height, z));
}

int main(){
	VideoDriver::m_assetsPath = "./../assets";
	EventHandler* handler = new EventHandler();	
	VideoDriver* VDriv = toe::GetVideoDriver();
	SceneManager* sm = VDriv->GetSceneManager();
	
	VDriv->CreateWindows("TOE Demonstrative Application", VDriv->GetScreenResolution(), false);
	VDriv->SetClearScreenColor(toe::core::TOEvector4df(0.1, 0.1, 0.3, 1));
	VDriv->SetIODriver(handler);
	VDriv->SetMouseVisibility(false);

	TFMesh* meshes[] = {nullptr, nullptr, nullptr};
	TFLight* lights[] = {nullptr, nullptr, nullptr};
	TFLight* shadowLight = nullptr;
	
	CreateTree(meshes, lights, shadowLight);

	// CREATE ANIMATION
	//TFAnimation* animation = nullptr;
	//CreateAnimations(animation);

	TFCamera* myCamera = sm->AddCamera();

	handler->screenCenterX = VDriv->GetScreenResolution().X/2;
	handler->screenCenterY = VDriv->GetScreenResolution().Y/2;

	// PARTICLES
	TFParticleSystem* ps = sm->AddParticleSystem(toe::core::TOEvector3df(-17,0,20), toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df(1,1,1));
	TFParticleSystem* ps1 = sm->AddParticleSystem(toe::core::TOEvector3df(0,0,20), toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df(1,1,1));
	TFParticleSystem* ps2 = sm->AddParticleSystem(toe::core::TOEvector3df(17,0,20), toe::core::TOEvector3df(0,0,0), toe::core::TOEvector3df(1,1,1));
	ps->SetManager(new ColoredParticle(true, false, false)); 
	//ps1->SetManager(new ColoredParticle(false, true, false));
	ps2->SetManager(new ColoredParticle(false, false, true));

	// TOE MANUAL
	TFSprite* manual = toe::AddSprite("",toe::core::TOEvector2df(0, 0), toe::core::TOEvector2df(305,96));
	manual->SetTexture("./../assets/textures/toe_manual.png");

	// TIO LOGO
	TFSprite* logo = toe::AddSprite("",toe::core::TOEvector2df(VDriv->GetScreenResolution().X - 534/3.5f, 0), toe::core::TOEvector2df(534/3.5f,624/3.5f));
	logo->SetTexture("./../assets/textures/default_sprite.png");

	// SUZANNE
	TFMesh* mesh = sm->AddMesh(toe::core::TOEvector3df(6.0f, 6.0f, 0.0f), toe::core::TOEvector3df(0.0f, 0.0f, 0.0f), toe::core::TOEvector3df(2.0f, 2.0f, 2.0f), "./../assets/models/suzanne.obj");
	mesh->AddBillboard(toe::core::TOEvector3df(0.0f, 3.0f, 0.0f), "SUZANNE", 0.5f);
	sceneObjects.push_back(mesh);

	// INIT MODELS
	shadowLight->SetTranslate(toe::core::TOEvector3df(EventHandler::xlight, EventHandler::ylight, EventHandler::zlight));
	RotateLights(mesh->GetRotation(), meshes[0], meshes[1], meshes[2]);
	shadowLight->SetActive(true);

	while(!EventHandler::m_close){
		// EVENT HANDLER UPDATE
		handler->Update();
		//animation->Update(0.16f);

		if(EventHandler::ChangeMain){
			// ROTATE MESH
			toe::core::TOEvector3df rot = mesh->GetRotation();
			rot.Y += 0.5;
			mesh->SetRotation(rot);

			// ROTATE LIGHTS
			RotateLights(rot, meshes[0], meshes[1], meshes[2]);

			// UPDATE PARTICLES
			ps->Update(0.16f);
			ps1->Update(0.16f);
			ps2->Update(0.16f);


			////
			shadowLight->SetActive(false);
			lights[0]->SetActive(true);
			lights[1]->SetActive(true);
			lights[2]->SetActive(true);
		}else{
			shadowLight->SetActive(true);
			lights[0]->SetActive(false);
			lights[1]->SetActive(false);
			lights[2]->SetActive(false);
		}
		shadowLight->SetTranslate(toe::core::TOEvector3df(EventHandler::xlight, EventHandler::ylight, EventHandler::zlight));
		
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
