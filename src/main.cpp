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

void CreateTree(TFMesh* ms[]){
	SceneManager* sm = VideoDriver::GetInstance()->GetSceneManager();
	TOEvector3df pos = TOEvector3df(0, 0, 0);
	TOEvector3df rot = TOEvector3df(0, 180, 0);
	TOEvector3df scale = TOEvector3df(1.0f, 1.0f, 1.0f);
	TOEvector4df color = TOEvector4df(1.0f, 1.0f, 1.0f, 1.0f);
	float attenuation = 0.005f;
	std::string path = "";
	TFMesh* mesh = nullptr;
	TFLight* l = nullptr;

	// PAREDES ###################################################

	// FLOOR
	pos = TOEvector3df(0.0f, -2.0f, 0.0f);
	scale = TOEvector3df(50.0f, 0.25f, 50.0f);
	mesh = sm->AddMesh(pos, rot, scale, "");
	sceneObjects.push_back(mesh);

	// IZDA
	pos = TOEvector3df(-25.0f, 8.0f, 0.0f);
	scale = TOEvector3df(0.25f, 20.0f, 50.0f);
	mesh = sm->AddMesh(pos, rot, scale, "");
	sceneObjects.push_back(mesh);

	// DCHA
	pos = TOEvector3df(25.0f, 8.0f, 0.0f);
	scale = TOEvector3df(0.25f, 20.0f, 50.0f);
	mesh = sm->AddMesh(pos, rot, scale, "");
	sceneObjects.push_back(mesh);

	// BACK
	pos = TOEvector3df(0.0f, 8.0f, 25.0f);
	scale = TOEvector3df(50.0f, 20.0f, 0.25f);
	mesh = sm->AddMesh(pos, rot, scale, "");
	sceneObjects.push_back(mesh);

	// TEAPOTS ###################################################
	pos = TOEvector3df(-7.0f, -1.8f, 20.0f);
	scale = TOEvector3df(0.7f, 0.7f, 0.7f);
	mesh = sm->AddMesh(pos, rot, scale, "./../assets/models/teapot.obj");
	mesh->SetTexture("./../assets/textures/checkerboard_texture.jpg");
	mesh->SetBoundBox(true);
	sceneObjects.push_back(mesh);

	pos = TOEvector3df(0.0f, -1.8f, 20.0f);
	scale = TOEvector3df(0.55f, 0.55f, 0.55f);
	mesh = sm->AddMesh(pos, rot, scale, "./../assets/models/teapot.obj");
	mesh->SetTexture("./../assets/textures/teapot_texture1.jpg");
	mesh->SetBoundBox(true);
	sceneObjects.push_back(mesh);

	pos = TOEvector3df(7.0f, -1.8f, 20.0f);
	scale = TOEvector3df(0.4f, 0.4f, 0.4f);
	mesh = sm->AddMesh(pos, rot, scale, "./../assets/models/teapot.obj");
	mesh->SetTexture("./../assets/textures/teapot_texture2.jpg");

	// Room model 
	pos = TOEvector3df(-4,-1,0);
	scale = TOEvector3df(1,1,1);
	mesh = sm->AddMesh(pos, TOEvector3df(0,180,0), scale, "./../assets/models/room_thickwalls.obj");
	mesh->SetTexture("./../assets/textures/room.png");
	//mesh->SetBoundBox(true);
	sceneObjects.push_back(mesh);

	// DOME ###################################################
	sm->AddDome();

	/// SPRITES	###############################################
	// TOE MANUAL
	/*
	TFSprite* manual = toe::AddSprite("",TOEvector2df(0, 0), TOEvector2df(305,96));
	manual->SetTexture("./../assets/textures/toe_manual.png");*/
	
	std::vector<std::string> instructions;
	instructions.push_back("[ WASD ] move");
	instructions.push_back("[MOUSE ] aim");
	instructions.push_back("[ARROWS] move light box");
	instructions.push_back("[SPACE ] play/pause scene");
	instructions.push_back("[ENTER ] change shader");
	instructions.push_back("[ ESC  ] exit");

	float posX = 0;
	float posY = 0;
	for(int i = instructions.size()-1; i>=0;i--){
		TF2DText* ManTxt = toe::Add2DText(instructions[i],TOEvector2df(posX,posY));
		posY+= ManTxt->GetHeight();
	}
	// TIO LOGO
	TFSprite* logo = toe::AddSprite("",TOEvector2df(toe::GetVideoDriver()->GetScreenResolution().X - 534/3.5f, 0), TOEvector2df(534/3.5f,624/3.5f));
	logo->SetTexture("./../assets/textures/default_sprite.png");
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

		anims[0]->Translate(TOEvector3df(movex, 0, movez));
		anims[1]->Translate(TOEvector3df(movex, 0, movez));
		anims[0]->SetRotation(TOEvector3df(0, -angle, 0));
		anims[1]->SetRotation(TOEvector3df(0, -angle, 0));
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
	
	VDriv->CreateWindows("TOE Demonstrative Application", VDriv->GetScreenResolution(), true);
	//VDriv->CreateWindows("TOE Demonstrative Application", TOEvector2di(800,600), false);
	VDriv->SetClearScreenColor(TOEvector4df(0.1, 0.1, 0.3, 1));
	VDriv->SetIODriver(handler);
	VDriv->SetMouseVisibility(false);

	TFMesh* meshes[] = {nullptr, nullptr, nullptr, nullptr, nullptr};
	
	CreateTree(meshes);

	// Main camera
	TFCamera* myCamera = sm->AddCamera();

	handler->screenCenterX = VDriv->GetScreenResolution().X/2;
	handler->screenCenterY = VDriv->GetScreenResolution().Y/2;

	// PARTICLES
	TFParticleSystem* ps = sm->AddParticleSystem(TOEvector3df(-17,0,20), TOEvector3df(0,0,0), TOEvector3df(1,1,1));
	TFParticleSystem* ps1 = sm->AddParticleSystem(TOEvector3df(0,0,20), TOEvector3df(0,0,0), TOEvector3df(1,1,1));
	TFParticleSystem* ps2 = sm->AddParticleSystem(TOEvector3df(17,0,20), TOEvector3df(0,0,0), TOEvector3df(1,1,1));
	ps->SetManager(new ColoredParticle(true, false, false)); 
	//ps1->SetManager(new ColoredParticle(false, true, false));
	ps2->SetManager(new ColoredParticle(false, false, true));

	// SUZANNE
	TFMesh* mesh = sm->AddMesh(TOEvector3df(6.0f, 6.0f, 0.0f), TOEvector3df(0.0f, 0.0f, 0.0f), TOEvector3df(2.0f, 2.0f, 2.0f), "./../assets/models/suzanne.obj");
	mesh->AddBillboard(TOEvector3df(0.0f, 3.0f, 0.0f), "SUZANNE", 0.5f);
	sceneObjects.push_back(mesh);
	
	// CREATE ANIMATION

	float deltaTime = 0.0f;
	bool lastMain = true;

	while(!EventHandler::m_close){
		// EVENT HANDLER UPDATE
		handler->Update();

		// SHADOWS SCENE
		if(!EventHandler::ChangeMain){
			// called once
			if(lastMain){
			}
			
			lastMain = false;
		}
		else{
			// called once
			if(!lastMain){
			}
			// ROTATE MESH
			TOEvector3df rot = mesh->GetRotation();
			rot.Y += 0.5;
			mesh->SetRotation(rot);

			// UPDATE PARTICLES
			ps->Update(0.16f);
			ps1->Update(0.16f);
			ps2->Update(0.16f);


			lastMain = true;
		}

		// CHANGE ANIMATION
		if(EventHandler::KP_ENTER){
			//animations[0]->PlayAnimation("shoot2", 25);
			EventHandler::KP_ENTER = false;
		}

		//UpdatePlayer(animations, meshes, deltaTime, EventHandler::PlayerX, EventHandler::PlayerZ);
		
		// UPDATE CAMERA
		myCamera->SetRotation(TOEvector3df(EventHandler::xdistGiro, EventHandler::ydistGiro, EventHandler::zdistGiro));
		myCamera->SetTranslate(TOEvector3df(EventHandler::xdist, EventHandler::ydist, EventHandler::zdist));
		
		// UPDATE VDRIVE & PAINT
		VDriv->Update();
		VDriv->BeginDraw();
		VDriv->EndDraw();
		VDriv->SetCursorPosition(VDriv->GetScreenResolution().X/2,VDriv->GetScreenResolution().Y/2);

		// CHANGE SHADERS AND UPDATE TIME
		ChangeShader(EventHandler::shaderType);
		UpdateDelta(deltaTime);

		myCamera->LookAt(TOEvector3df(0.0f, 0.0f, 0.0f));
	}

	VDriv->CloseWindow();
    return EXIT_SUCCESS;
}
