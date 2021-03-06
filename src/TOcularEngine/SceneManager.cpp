#include "SceneManager.h"
#include "VideoDriver.h"
#include "./../EngineUtilities/Entities/TEntity.h"
#include "./../EngineUtilities/Entities/TTransform.h"
#include "./../EngineUtilities/TNode.h"
#include "./../EngineUtilities/TRoom.h"

#include <algorithm>    // std::find
#include <limits>		// std::numeric_limits<T>::max

// GLEW AND GLM
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

SceneManager::SceneManager(){
	// Empezamos con un nodo que va a hacer de raiz
	TTransform* myTransform = new TTransform();
	m_SceneTreeRoot = new TNode(myTransform);

	// Inicializamos las variables del SceneManager
	m_ambientLight = glm::vec3(0.25f);
	m_main_camera = nullptr;
	m_numshadowlights = 0;
	m_sendLights = true;
	m_currentRoom = -1;
	m_dome = nullptr;
	m_vao = 0;
}

SceneManager::~SceneManager(){
	// Eliminamos los objetos de la escena
	ClearElements();

	// ELiminamos el buffer de vertices
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_vao);
}

TFCamera* SceneManager::AddCamera(TOEvector3df position, TOEvector3df rotation, bool perspective){
	TFCamera* toRet = nullptr;
	// Creamos una camera
	toRet = new TFCamera(position, rotation, perspective);
	// Lo anyadimos al vector de camaras
	m_cameras.push_back(toRet);
	// Lo ligamos a la raiz del arbol
	toRet->Attach(m_SceneTreeRoot);
	m_main_camera = toRet;
	return toRet;
}

TFLight* SceneManager::AddLight(TOEvector3df position, TOEvector3df rotation, TOEvector4df color, float attenuation){
	TFLight* toRet = nullptr;
	// Creamos la luz
	toRet = new TFLight(position, rotation, color, attenuation);
	// La anyadimos al vector de luces
	m_lights.push_back(toRet);
	// La ligamos a la raiz del arbol
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

TFMesh* SceneManager::AddMesh(TOEvector3df position, TOEvector3df rotation, TOEvector3df scale, std::string meshPath){
	// En el caso de pasar una cadena vacia vamos a cargar un cubo
	if(meshPath.compare("")==0) meshPath = VideoDriver::GetInstance()->GetAssetsPath() + "/models/cube.obj";

	TFMesh* toRet = nullptr;
	// Creamos el mesh
	toRet = new TFMesh(position, rotation, scale, meshPath);
	// Lo anyadimos al vector de objetos
	m_objects.push_back(toRet);
	// LO ligamos a la raiz del arbol
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

TFDome* SceneManager::AddDome(TOEvector3df position, std::string texturePath){
	if(m_dome == nullptr){
		// Creamos el DOme
		TFDome* toRet = new TFDome(position, TOEvector3df(0.0f,0.0f,0.0f), TOEvector3df(50.0f,50.0f,50.0f), texturePath);
		m_dome = toRet;
		// Lo anyadimos como primer elemento en la raiz del arbol
		m_dome->AttachFirst(m_SceneTreeRoot);	
	}
	// En el caso de que ya exista simplemente le cambiamos la textura
	else if(texturePath.compare("") != 0) m_dome->SetTexture(texturePath);
	return m_dome;
}

TFAnimation* SceneManager::AddAnimation(TOEvector3df position, TOEvector3df rotation, TOEvector3df scale){
	TFAnimation* toRet = nullptr;
	// Creamos la animacion
	toRet = new TFAnimation(position, rotation, scale);
	// La anyadimos al vector de objetos
	m_objects.push_back(toRet);
	// Lo ligamos a la raiz del arbol
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

TFRect* SceneManager::Add2DRect(TOEvector2df position, TOEvector2df size, float rotation){
	// Creamos el rectangulo 2D
	TFRect* toRet = new TFRect(position, size, rotation);
	// Lo anyadimos al vector de elementos 2D en el fondo
	m_bkg2Delems.push_back(toRet);
	return toRet;
}

TF2DText* SceneManager::Add2DText(std::string text, TOEvector2df position){
	// Creamos el texto 2D
	TF2DText* toRet = new TF2DText(text, position);
	// Lo anyadimos al vector de elementos 2D en el fondo
	m_bkg2Delems.push_back(toRet);
	return toRet;
}

TFSprite* SceneManager::AddSprite(std::string texture, TOEvector2df position, TOEvector2df size){
	// Creamos el sprite
	TFSprite* toRet =  new TFSprite(texture, position, size);
	// LO anyadimos al vector de elementos 2D en el fondo
	m_bkg2Delems.push_back(toRet);
	return toRet;
}

TFParticleSystem* SceneManager::AddParticleSystem(TOEvector3df position, TOEvector3df rotation, TOEvector3df scale){
	TFParticleSystem* toRet = nullptr;
	// Creamos un sistema de particulas
	toRet = new TFParticleSystem(position, rotation, scale);
	// Lo anyadimos al vector de objetos
	m_objects.push_back(toRet);
	// Lo ligamos a la raiz del arbol de escena
	toRet->Attach(m_SceneTreeRoot);
	return toRet;
}

TFRoom* SceneManager::AddRoom(TOEvector3df position, TOEvector3df rotation, TOEvector3df scale){
	TFRoom* toRet = nullptr;
	// Creamos una habitacion
	toRet = new TFRoom(position, rotation, scale);
	// La anyadimos al vector de habitaciones
	m_rooms.push_back(toRet);
	return toRet;
}

void SceneManager::PushToBkg(TFDrawable* obj){
	// Busca el objeto dentro del vector de elemtos 2D
	std::vector<TFDrawable*>::iterator it = m_2Delems.begin();
	for(; it!=m_2Delems.end(); ++it){
		if(*it == obj){
			// En el caso de encontrarlo lo cambiamos al vector de elementos2D en el fondo
			m_bkg2Delems.push_back(*it);
			m_2Delems.erase(it);
			break;
		}
	}
}

void SceneManager::PushToFront(TFDrawable* obj){
	// Busca el objeto dentro del vector de elemtnso 2D en el fondo
	std::vector<TFDrawable*>::iterator it = m_bkg2Delems.begin();
	for(; it!=m_bkg2Delems.end(); ++it){
		if(*it == obj){
			// En el caso de encontrarlo lo movemos al otro vector de elementos 2D
			m_2Delems.push_back(*it);
			m_bkg2Delems.erase(it);
			break;
		}
	}
}

void SceneManager::Delete2Delement(TFDrawable* elem){
	bool find = false;

	// Buscamos el objeto en ambos vectores de elementos 2D
	// En caso de encontrarlo lo eliminamos
	std::vector<TFDrawable*>::iterator it = m_2Delems.begin();
	for(; it != m_2Delems.end(); ++it){
		if(*it == elem){ 
			m_2Delems.erase(it);
			delete elem;

			find = true;
			break;
		}
	}
	if(!find){
		it = m_bkg2Delems.begin();
		for(; it != m_bkg2Delems.end(); ++it){
			if(*it == elem){ 
				m_bkg2Delems.erase(it);
				delete elem;

				break;
			}
		}
	}
}

bool SceneManager::DeleteCamera(TFCamera* cam){
	bool toRet = false;
	// Buscamos la camera en el vector de cameras
	std::vector<TFCamera*>::iterator it = m_cameras.begin();
	for(; it != m_cameras.end() && !toRet; ++it){
		if(*it == cam){
			// EN el caso de encontrarla la eliminamos
			if(cam == m_main_camera) m_main_camera = nullptr;
			delete cam;
			m_cameras.erase(it);
			toRet = true;
		}
	}
	return toRet;
}

bool SceneManager::DeleteLight(TFLight* light){
	bool toRet = false;
	// Buscamos la luz en el vector de luces
	std::vector<TFLight*>::iterator it = m_lights.begin();
	for(; it!= m_lights.end() && !toRet; ++it){
		if(*it == light){
			// EN el caso de encontrarla la eliminamos
			m_lights.erase(it);
			delete light;
			toRet = true;
		}
	}

	// En el caso de no encontrarla la buscamos en las luces de las habitaciones
	it = m_lightRooms.begin();
	for(; it!=m_lightRooms.end() && !toRet; ++it){
		if(*it == light){
			// La eliminamos
			DeleteRoomLight(light);
			m_lightRooms.erase(it);
			delete light;
			toRet = true;
		}
	}

	return toRet;
}

void SceneManager::DeleteRoomLight(TFNode* light){
	// ELiminamos la luz del vector de luces de las habitacaiones
	int size = m_rooms.size();
	for(int i=0; i<size; i++){
		// QUita la luz de las habitaciones que la contengan
		m_rooms[i]->DeleteLight(light);
	}
}


bool SceneManager::DeleteMesh(TFNode* node){
	bool toRet = false;

	// Busca el mesh en el vector de objetos
	std::vector<TFNode*>::iterator it = m_objects.begin();
	for(; it!= m_objects.end() && !toRet; ++it){
		if(*it == node){
			// En el caso de encontrarlo lo eliminamos
			m_objects.erase(it);
			delete node;
			toRet = true;
		}
	}
	return toRet;
}

bool SceneManager::DeleteRoom(TFNode* node){
	bool toRet = false;

	// Buscamos la habitacion en el vector de habitaciones
	std::vector<TFRoom*>::iterator it = m_rooms.begin();
	for(; it != m_rooms.end() && !toRet; ++it){
		if(*it == node){
			// En el caso de encontrarlo lo eliminamos
			m_rooms.erase(it);
			delete node;
			toRet = true;
		}
	}
	return toRet;
}

bool SceneManager::DeleteAnimation(TFNode* node){
	bool toRet = false;
	// Buscamos la animacion en el vector de objetos
	int size = m_objects.size();
	for(int i=0; i<size; i++){
		if(node == m_objects[i]){
			// EN el caso de encontrarlo lo eliminamos
			m_objects.erase(m_objects.begin() + i);
			delete node;
			toRet = true;
		}
	}

	return toRet;
}

void SceneManager::SetAmbientLight(TOEvector3df ambientLight){
	m_ambientLight = glm::vec3(ambientLight.X, ambientLight.Y, ambientLight.Z);
}

void SceneManager::SetAmbientLight(float ambientLight){
	m_ambientLight = glm::vec3(ambientLight, ambientLight, ambientLight);
}

TOEvector3df SceneManager::GetAmbientLight(){
	return TOEvector3df(m_ambientLight.x, m_ambientLight.y, m_ambientLight.z);
}

void SceneManager::SetMainCameraData(){
	if(m_main_camera!=nullptr){
		TEntity::SetViewMatrixPtr( glm::inverse(m_main_camera->m_entityNode->GetTransformMatrix()) );
	}
}

TNode* SceneManager::GetRootNode(){
	return m_SceneTreeRoot;
}

TFCamera* SceneManager::GetMainCamera(){
	return m_main_camera;
}

void SceneManager::ChangeMainCamera(TFCamera* camera){
	// En el caso de que se pase un nullptr vamos a querer poner la siguiente camara
	// es por eso que vamos tanto a buscar si esta la camera pasada como la main camera
	int cameraPos = -1;
	int mainCameraPos = -1;
	int size = m_cameras.size();
	for(int i=0; i<size; i++){
		TFCamera* current = m_cameras[i];
		// Buscamos la main Camera
		if(current == m_main_camera){
			mainCameraPos = i;
			// En el caso de que no haya camara pasada podemos salir del bucle
			if(camera == nullptr) break;
		}
		// Buscamos la Camara pasada, si es nullptr nunca se encontrara
		if(current == camera){
			cameraPos = -1;
			break;	// Como ya hemos encontrado la camara podemos salir
		}
	}

	// En el caso de que no se haya encontrado la camara o era nullptr
	if(cameraPos == -1){
		cameraPos = mainCameraPos + 1;
		// En el caso de que nos pasemos volvemos al principio
		if(cameraPos == size) cameraPos = 0;
	}
	m_main_camera = m_cameras[cameraPos];
}

void SceneManager::InitScene(){
	glGenVertexArrays(1, &m_vao); // CREAMOS EL ARRAY DE VERTICES PARA LOS OBJETOS
	glBindVertexArray(m_vao);
}

void SceneManager::Update(){
	// MOVE DOME WITH CAMERA
	if(m_main_camera != nullptr && m_dome != nullptr){
		TOEvector3df position = m_main_camera->GetTranslation();
		m_dome->SetTranslate(position);
	}
}

void SceneManager::Draw(){
	unsigned int currentFrame = TEntity::currentFrame;
	currentFrame++;
	if(currentFrame == std::numeric_limits<unsigned int>::max()) currentFrame = 0;
	TEntity::currentFrame = currentFrame;

	// Select active camera and set view and projection matrix
	SetMainCameraData();

	// Draw into frame for shadows
	DrawSceneShadows();

	// Draw frame into window
	int width = VideoDriver::GetInstance()->GetWindowDimensions().X;
	int height = VideoDriver::GetInstance()->GetWindowDimensions().Y;

	// Draw into window
	glViewport(0,0,width,height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// IMPORTANT CLEAR COLOR
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// ENABLE BACK FACE CULLING
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

	// Actualizamos la habitacion actual
	UpdateCurrentRoom();

	// Send lights position to shader
	SendLights();

	// Draw all of the elements in tree
    m_SceneTreeRoot->Draw();
    
	// Pintar aqui las habitaciones
	DrawRooms();

	// Draw debug lines
	DrawAllLines();
}

void SceneManager::UpdateCurrentRoom(){
	int value = -1;

	if(m_main_camera != nullptr){
		// Lo primero es saber cual de todas las habitaciones esta mas cerca de la mainCamera
		TOEvector3df camPos = m_main_camera->GetTranslation();
		float minDistance =  std::numeric_limits<float>::max();

		// Miramos entre todas las habitaciones de cual se encuentra mas cerca
		int size = m_rooms.size();
		for(int i=0; i<size; i++){
			TFRoom* currentRoom = m_rooms[i];
			float currentDistance = currentRoom->GetDistance(camPos);
			if(currentDistance < minDistance){
				minDistance = currentDistance;
				value = i;
			}
		}
	}

	m_currentRoom = value;
}

int SceneManager::SendRoomLights(int value){
	if(m_main_camera != nullptr){
		// Una vez aqui ya se habra visto cual es la habitacion mas cercana a la camara
		if(m_currentRoom != -1){
			// Enviamos las luces de las habitaciones
			value = m_rooms[m_currentRoom]->DrawLights(value, 1);
		}
	}

	// Volvemos a poner al valor inicial los valores de clipping
	TEntity::ResetClippingVariables();
	// Volvemos a poner al valor inicial los booleanos de las habitacions
	int size = m_rooms.size();
	for(int i=0; i<size; i++){
		m_rooms[i]->SetLightsSend(false);
	}

	return value;
}

void SceneManager::DrawRooms(){
	if(m_main_camera != nullptr){
		// Una vez aqui ya se habra visto cual es la habitacion mas cercana a la camara
		if(m_currentRoom != -1){
			// Procedemos a pintar la habitacion mas cercana
			m_rooms[m_currentRoom]->Draw();
		} 

		// Reseteamos las variables de pintado
		int size = m_rooms.size();
		for(int i=0; i<size; i++){
			m_rooms[i]->SetDrawed(false);
		}

	}
}

void SceneManager::DrawBkg2DElements(){
	//DRAW 2D ELEMENTS AFTER THE 3D SCENE
	for(int i = 0; i<m_bkg2Delems.size(); i++) m_bkg2Delems[i]->Draw();
}

void SceneManager::Draw2DElements(){
	//DRAW 2D ELEMENTS AT THE END OF DRAWING
	for(int i = 0; i< m_2Delems.size(); i++) m_2Delems[i]->Draw();
}

void SceneManager::DrawBoundingBoxes(bool draw){
	int size = m_objects.size();
	for(int i = size - 1; i>=0 ; i--){
		m_objects[i]->SetBoundBox(draw);
	}
}

void SceneManager::DrawLine(TOEvector3df start, TOEvector3df end, TOEvector3df color){
	// Anyadimos al vector de floats todoso los valores de los dos puntos
	vertexVector.push_back(start.X); 
	vertexVector.push_back(start.Y); 
	vertexVector.push_back(start.Z);
	vertexVector.push_back(1.0f);

	vertexVector.push_back(end.X); 
	vertexVector.push_back(end.Y); 
	vertexVector.push_back(end.Z);
	vertexVector.push_back(1.0f);
}

void SceneManager::ChangeShader(SHADERTYPE shader, ENTITYTYPE entity){
	// Cambiamos el shader que utilizan los objetos
	int size = m_objects.size();
	for(int i=0; i<size; i++){
		TFNode* currentNode = m_objects[i];
		currentNode->SetProgram(shader, entity);
	}
}

void SceneManager::SetClipping(bool value){
	TEntity::m_checkClipping = value;
}

void SceneManager::SetSendLights(bool value){
	m_sendLights = value;
}

void SceneManager::ClearElements(){
	// Eliminamos las camaras
	int size = m_cameras.size();
	for(int i = size - 1; i >= 0; i--){
		delete m_cameras[i];
	}
	m_cameras.clear();
	
	// Eliminamos las luces
	size = m_lights.size();
	for(int i = size - 1; i >= 0; i--){
		delete m_lights[i];
	}
	m_lights.clear();

	// ELiminamos los objetos
	size = m_objects.size();
	for(int i = size - 1; i>=0; i--){
		delete m_objects[i];
	}
	m_objects.clear();

	// ELiminamos las habitaciones
	size = m_rooms.size();
	for(int i = size -1; i>=0; i--){
		delete m_rooms[i];
	}
	m_rooms.clear();

	// ELiminamos los objetos 2D del fondo
	size = m_bkg2Delems.size();
	for (int i = size -1; i>=0; i--) delete m_bkg2Delems[i];
	m_bkg2Delems.clear();

	// ELiminamos los objetos 2D
	size = m_2Delems.size();
	for(int i = size - 1; i>=0; i--) delete m_2Delems[i];
	m_2Delems.clear();

	// ELiminamos el DOme
	if(m_dome != nullptr) delete m_dome;
	m_dome = nullptr;
	
	// Eliminamos el arbol
	delete m_SceneTreeRoot;
	m_SceneTreeRoot = nullptr;
}

void SceneManager::RecalculateLightPosition(){
	// Recalculamos la posiciones de las luces
	GLint size = m_lights.size();
	for(int i = 0; i < size; i++) m_lights[i]->CalculateLocation();
}

void SceneManager::RecalculateShadowLightsNumber(){
	m_numshadowlights = 0;
	GLint size = m_lights.size();
	for(int i = 0; i < size; i++){
		if(m_lights[i] != nullptr && m_lights[i]->GetActive() && m_lights[i]->GetShadowsState()) m_numshadowlights++;
	}
}

void SceneManager::SendLights(){
	// Change light last position
	RecalculateLightPosition();
	RecalculateShadowLightsNumber();
	
	VideoDriver* vd = VideoDriver::GetInstance();

	// SEND ALL LIGHTS TO ALL SHADERS
	vd->SetShaderProgram(BARREL_SHADER);
	SendLightsToShader();
	SendShadowLightsToShader();

	vd->SetShaderProgram(FISHEYE_SHADER);
	SendLightsToShader();
	SendShadowLightsToShader();

	vd->SetShaderProgram(DISTORSION_SHADER);
	SendLightsToShader();
	SendShadowLightsToShader();

	vd->SetShaderProgram(STANDARD_SHADER);
	SendLightsToShader();
	SendShadowLightsToShader();
}

void SceneManager::SendShadowLightsToShader(){
	// Gets the programs
	VideoDriver* vd = VideoDriver::GetInstance();

	int size = 0;
	if(m_sendLights){
		size = SendLightMVP();
	}
	GLuint progID = vd->GetProgram(vd->GetCurrentProgram())->GetProgramID();
	glUniform1i(glGetUniformLocation(progID, "nshadowlights"), size);
}


void SceneManager::SendLightsToShader(){
	// Gets the Programs
	VideoDriver* vd = VideoDriver::GetInstance();
	GLuint programID = vd->GetProgram(vd->GetCurrentProgram())->GetProgramID();

	// Sends the Ambient Light
	GLint ambLocation = glGetUniformLocation(programID, "AmbientLight");
	glUniform3fv(ambLocation, 1, &m_ambientLight[0]);

	// Draw all lights
	int size = 0;
	if(m_sendLights){
		size = m_lights.size();

		int i=0;
    	while(i < size){ 
    		m_lights[i]->DrawLight(i);
    		i++;
    	}
    	size = SendRoomLights(i);
	}

    // Send size of lights
	GLuint nlightspos = glGetUniformLocation(programID, "nlights");
	glUniform1i(nlightspos, size);
}

int SceneManager::SendLightMVP(){
	int mvpIndex = 0;
	GLint size = m_lights.size();
	for(int i = 0; i < size; i++){
		if(m_lights[i] != nullptr && m_lights[i]->GetActive() && m_lights[i]->GetShadowsState()){
			m_lights[i]->DrawLightMVP(mvpIndex);
			mvpIndex++;
		}
	}
	return mvpIndex;
}

void SceneManager::ResetManager(){
	// Elimianmos los objetos del arbol
	ClearElements();
	// Creamos una raiz del arbol nueva
	TTransform* myTransform = new TTransform();
	m_SceneTreeRoot = new TNode(myTransform);
	m_main_camera = nullptr;
}

// PRIVATE FUNCTIONS
bool SceneManager::Light2Room(TFNode* node){
	// Buscamos la luz en el vector de luces
	int size = m_lights.size();
	for(int i = 0; i<size; i++){
		if(m_lights[i] == node){
			// EN el caso de encontrarla pasamos la luz del vector de luces al de luces de las habitaciones
			m_lightRooms.push_back(m_lights[i]);
			m_lights.erase(m_lights.begin() + i);
			return true;
		}
	}

	return false;		// La luz no se ha encontrado entre las del arbol de escen
}

void SceneManager::DrawAllLines(){
	Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(BB_SHADER);

	// Full buffer of all vertices
	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, vertexVector.size()*sizeof(GLfloat), &vertexVector[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Apply object's transformation matrix
	glm::mat4 m = TEntity::ProjMatrix * TEntity::ViewMatrix;
	GLuint uniform_m = glGetUniformLocation(myProgram->GetProgramID(), "MVP");
	glUniformMatrix4fv(uniform_m, 1, GL_FALSE, &m[0][0]);

	// Send light color
	GLuint linecolor = glGetUniformLocation(myProgram->GetProgramID(), "LineColor");
	//glUniform3f(linecolor, color.X, color.Y, color.Z);
	glUniform3f(linecolor, 1.0f, 1.0f, 0.0f);

	// Send each vertex data
	GLuint attribute_v_coord = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");	
	glEnableVertexAttribArray(attribute_v_coord);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glVertexAttribPointer(
		attribute_v_coord,  // attribute
		4,                  // number of elements per vertex, here (x,y,z,w)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
	);
	
	// Send shader
	glDrawArrays(GL_LINES, 0, vertexVector.size());

	glDisableVertexAttribArray(attribute_v_coord);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo_vertices);
	vertexVector.clear();
}

void SceneManager::DrawSceneShadows(){
	if(m_sendLights){
		// Set shadow program
		VideoDriver::GetInstance()->SetShaderProgram(SHADOW_SHADER);
	
		// Update lights position
		RecalculateLightPosition();
	
		// Calculate the shadow map
		for(int i = 0; i < m_lights.size(); i++){
			TFLight* toCheck = m_lights[i];
			if(toCheck != nullptr){
				// Caulculamos si esta activa y tiene sombras
				// Si esta activa y necesita sombra, las pintamos
				// Se pintan desde el SceneTreeRot en el buffer vinculado en
				// La funcion CalculateShadowTexture y con la MVP calculada
				// Tambien en esa funcion
				if(toCheck->CalculateShadowTexture(i)) m_SceneTreeRoot->DrawShadows();
			}
		}
	}
}