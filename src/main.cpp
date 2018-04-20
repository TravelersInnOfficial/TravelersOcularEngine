#include "TOcularEngine/TOcularEngine.h"
#include "TOcularEngine/VideoDriver.h"
#include "TOcularEngine/SceneManager.h"

#include "EventHandler.h"
#include "ColoredParticle.h"

#include <glm/gtc/matrix_transform.hpp>
#include <ShaderTypes.h>
#include <vector>

#include <thread>
#include <chrono>

#include "animation_string.h"

std::vector<TFMesh*> sceneObjects;
int currentShader = 0;
bool movingPlayer = true;

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

	pos = toe::core::TOEvector3df(-7.0f, -1.8f, 20.0f);
	scale = toe::core::TOEvector3df(0.7f, 0.7f, 0.7f);
	mesh = sm->AddMesh(pos, rot, scale, "./../assets/models/teapot.obj");
	mesh->SetTexture("./../assets/textures/checkerboard_texture.jpg");
	mesh->SetBoundBox(true);
	sceneObjects.push_back(mesh);

	pos = toe::core::TOEvector3df(0.0f, -1.8f, 20.0f);
	scale = toe::core::TOEvector3df(0.55f, 0.55f, 0.55f);
	mesh = sm->AddMesh(pos, rot, scale, "./../assets/models/teapot.obj");
	mesh->SetTexture("./../assets/textures/teapot_texture1.jpg");
	mesh->SetBoundBox(true);
	sceneObjects.push_back(mesh);

	pos = toe::core::TOEvector3df(7.0f, -1.8f, 20.0f);
	scale = toe::core::TOEvector3df(0.4f, 0.4f, 0.4f);
	mesh = sm->AddMesh(pos, rot, scale, "./../assets/models/teapot.obj");
	mesh->SetTexture("./../assets/textures/teapot_texture2.jpg");

	// Room model 
	pos = toe::core::TOEvector3df(-4,-1,0);
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

	/// SPRITES	###############################################
	// TOE MANUAL
	TFSprite* manual = toe::AddSprite("",toe::core::TOEvector2df(0, 0), toe::core::TOEvector2df(305,96));
	manual->SetTexture("./../assets/textures/toe_manual.png");

	// TIO LOGO
	TFSprite* logo = toe::AddSprite("",toe::core::TOEvector2df(toe::GetVideoDriver()->GetScreenResolution().X - 534/3.5f, 0), toe::core::TOEvector2df(534/3.5f,624/3.5f));
	logo->SetTexture("./../assets/textures/default_sprite.png");
}

void CreateAnimations(TFAnimation* anims[], TFMesh* ms[]){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();

	toe::core::TOEvector3df rot = toe::core::TOEvector3df(0, 0, 0);
	toe::core::TOEvector3df scale = toe::core::TOEvector3df(2.0f, 2.0f, 2.0f);

	// MAGE ANIMATION
	toe::core::TOEvector3df pos = toe::core::TOEvector3df(-4, 1, -12);
	anims[0] = sm->AddAnimation(pos, rot, scale);
	anims[1] = sm->AddAnimation(pos, rot, scale);

	// BILLBOARDS 
	pos.Y += 2;
	pos.X += -1;
	ms[3] = sm->AddMesh(pos);
	ms[3]->CreateSphere();

	pos.X += 2;
	ms[4] = sm->AddMesh(pos);
	ms[4]->CreateSphere();

	pos = toe::core::TOEvector3df(0.0f, 1.0f, 0.0f);
	ms[3]->AddBillboard(pos, "0", 0.35f);
	ms[4]->AddBillboard(pos, "0", 0.35f);
	
	// OTHER ANIMATION
	pos = toe::core::TOEvector3df(4, 1, 12);
	anims[2] = sm->AddAnimation(pos, rot, scale);

	int size = sizeof(walk)/sizeof(walk[0]);
	anims[0]->SetAnimationPaths("topwalk", size , walk, 25);
	anims[2]->SetAnimationPaths("topwalk", size , walk, 25);
	
	size = sizeof(shoot1)/sizeof(shoot1[0]);
	anims[0]->SetAnimationPaths("shoot1", size, shoot1);
	//anims[2]->SetAnimationPaths("shoot1", size, shoot1);

	size = sizeof(shoot2)/sizeof(shoot2[0]);
	//anims[0]->SetAnimationPaths("", size, shoot2);
	
	size = sizeof(topidle)/sizeof(topidle[0]);
	anims[0]->SetAnimationPaths("topiddle", size, topidle);

	size = sizeof(botwalk)/sizeof(botwalk[0]);
	anims[1]->SetAnimationPaths("botwalk", size, botwalk);

	size = sizeof(botidle)/sizeof(botidle[0]);
	anims[1]->SetAnimationPaths("botiddle", size, botidle);

	//anims[0]->SetBoundBox(true);
	//anims[1]->SetBoundBox(true);
	anims[2]->SetBoundBox(true);

	anims[0]->SetTexture("./../assets/textures/wizard.png");
	anims[1]->SetTexture("./../assets/textures/wizard.png");
	anims[2]->SetTexture("./../assets/textures/wizard.png");

	// PLAY ANIMATION
	//anims[0]->PlayAnimation("topiddle");
	//anims[1]->PlayAnimation("botiddle");

	//anims[0]->PlayAnimation("topwalk");
	//anims[1]->PlayAnimation("botwalk");
	//anims[2]->PlayAnimation("topwalk");
	
	// SYNC ANIMATIONS
	anims[0]->BindSyncAnimation(anims[1]);
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

void UpdateDelta(float &deltaTime){
	using namespace std::chrono_literals;
	using clk = std::chrono::high_resolution_clock;
	static auto t = clk::now();

	// DECLARAMOS SPF y FPS
	constexpr auto fps = 200.0f;
	constexpr auto spf = 1000000000ns / fps;

	// CALCULAMOS DELTA TIME ANTES DE ESPERAR Y ESPERAMOS
	auto passed = clk::now() - t;
	if (passed < spf){
		auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(spf - passed - 100us);
		std::this_thread::sleep_for(ns);
	}

	// CALCULAMOS DELTA TIME
	passed = clk::now() - t;
	std::chrono::duration<double, std::milli> milisecondsPassed = passed;
	deltaTime = milisecondsPassed.count() / 1000.0f;
	if(deltaTime > 1.0f) deltaTime = 0.02f;

	// GUARDAMOS LA T
	t = clk::now();

	// Esta cutremente aqui, SOLO ES PARA PRUEBAS
	std::string myFps = std::to_string(int(1/(deltaTime)));
	VideoDriver::GetInstance()->SetWindowName(myFps);
}

void UpdatePlayer(TFAnimation* anims[], TFMesh* meshes[], float deltaT, int px, int pz){

	// UPDATE ANIMATIONS
	anims[0]->Update(deltaT);			// called 60 times per second aprox
	anims[1]->Update(deltaT);			// called 60 times per second aprox
	anims[2]->Update(deltaT);			// called 60 times per second aprox
	
	if(px != 0 || pz != 0){

		if(!movingPlayer){
			// Is moving
			anims[0]->ChangeAnimation("topwalk");
			anims[1]->ChangeAnimation("botwalk");
			movingPlayer = true;
		}
	
		float angle = 0.0f;
		
		if(px == 0){
			if(pz == +1) angle = 180.0f;
			if(pz == -1) angle = 0.0f;
		}
		else if (px == 1){
			if(pz == -1) angle = 45.0f;
			if(pz ==  0) angle = 90.0f; 
			if(pz == +1) angle = 135.0f;
		}
		else{
			if(pz == +1) angle = 225.0f;
			if(pz ==  0) angle = 270.0f; 
			if(pz == -1) angle = 315.0f;
		}

		float speed = 0.1f;
		float movex = sin(glm::radians(angle)) * speed;
		float movez = -cos(glm::radians(angle)) * speed;

		anims[0]->Translate(toe::core::TOEvector3df(movex, 0, movez));
		anims[1]->Translate(toe::core::TOEvector3df(movex, 0, movez));
		anims[0]->SetRotation(toe::core::TOEvector3df(0, -angle, 0));
		anims[1]->SetRotation(toe::core::TOEvector3df(0, -angle, 0));
	}
	else{
		if(movingPlayer){
			// Is not moving
			anims[0]->ChangeAnimation("topiddle");
			anims[1]->ChangeAnimation("botiddle");

			movingPlayer = false;
		}
	}

	// UPDATE BILLBOARDS
	meshes[3]->SetBillboardText(std::to_string(anims[0]->GetAnimationFrame()));
	meshes[4]->SetBillboardText(std::to_string(anims[1]->GetAnimationFrame()));
	//meshes[4]->SetBillboardText(std::to_string(movingPlayer));
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

	TFMesh* meshes[] = {nullptr, nullptr, nullptr, nullptr, nullptr};
	TFLight* lights[] = {nullptr, nullptr, nullptr};
	TFLight* shadowLight = nullptr;
	
	CreateTree(meshes, lights, shadowLight);

	// Main camera
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

	// SUZANNE
	TFMesh* mesh = sm->AddMesh(toe::core::TOEvector3df(6.0f, 6.0f, 0.0f), toe::core::TOEvector3df(0.0f, 0.0f, 0.0f), toe::core::TOEvector3df(2.0f, 2.0f, 2.0f), "./../assets/models/suzanne.obj");
	mesh->AddBillboard(toe::core::TOEvector3df(0.0f, 3.0f, 0.0f), "SUZANNE", 0.5f);
	sceneObjects.push_back(mesh);
	
	// CREATE ANIMATION
	TFAnimation* animations[] = {nullptr, nullptr, nullptr};
	CreateAnimations(animations, meshes);

	float deltaTime = 0.0f;
	bool lastMain = true;

	// INIT Lights position
	RotateLights(mesh->GetRotation(), meshes[0], meshes[1], meshes[2]);

	while(!EventHandler::m_close){
		// EVENT HANDLER UPDATE
		handler->Update();

		// SHADOWS SCENE
		if(!EventHandler::ChangeMain){
			// called once
			if(lastMain){
			}

			//// TOGGLE LIGHTS
			shadowLight->SetActive(true);
			lights[0]->SetActive(false);
			lights[1]->SetActive(false);
			lights[2]->SetActive(false);
			
			lastMain = false;
		}
		// ROTATING LIGHTS SCENE
		else{
			// called once
			if(!lastMain){
			}
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

			//// TOGGLE LIGHTS
			shadowLight->SetActive(false);
			lights[0]->SetActive(true);
			lights[1]->SetActive(true);
			lights[2]->SetActive(true);

			lastMain = true;
		}

		// CHANGE ANIMATION
		if(EventHandler::KP_ENTER){
			animations[0]->PlayAnimation("shoot1", 25);
			EventHandler::KP_ENTER = false;
		}

		UpdatePlayer(animations, meshes, deltaTime, EventHandler::PlayerX, EventHandler::PlayerZ);

		// TRANSLATE SHADOW LIGHT
		shadowLight->SetTranslate(toe::core::TOEvector3df(EventHandler::xlight, EventHandler::ylight, EventHandler::zlight));
		
		// UPDATE CAMERA
		myCamera->SetRotation(toe::core::TOEvector3df(EventHandler::xdistGiro, EventHandler::ydistGiro, EventHandler::zdistGiro));
		myCamera->SetTranslate(toe::core::TOEvector3df(EventHandler::xdist, EventHandler::ydist, EventHandler::zdist));
		
		// UPDATE VDRIVE & PAINT
		VDriv->Update();
		VDriv->BeginDraw();
		VDriv->EndDraw();
		VDriv->SetCursorPosition(VDriv->GetScreenResolution().X/2,VDriv->GetScreenResolution().Y/2);

		// CHANGE SHADERS AND UPDATE TIME
		ChangeShader(EventHandler::shaderType);
		UpdateDelta(deltaTime);
	}

	VDriv->CloseWindow();
    return EXIT_SUCCESS;
}
