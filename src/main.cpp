// PROVISONAL INCLUDES
#include "TNode.h"
#include "Entities/TEntity.h"
#include "Entities/TTransform.h"
#include "Entities/TMesh.h"
#include "Resources/Program.h"
#include "Entities/TCamera.h"
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TResourceManager.h"
#include "Resources/TResourceMesh.h"

TTransform* node1Rot;

void printMatrix(glm::mat4 mat){
	for (int i= 0; i<4; i++){
		for (int j = 0; j<4; j++)
			std::cout << mat[i][j] <<" ";

		std::cout << "\n";	
	}
	std::cout << "\n";
}

glm::mat4 GetTransformInTree(TNode* node){
	TNode* auxParent;
	glm::mat4 toReturn;

	auxParent = node->GetParent();
	toReturn = ((TTransform*)auxParent->GetEntity())->GetTransform();
	auxParent = auxParent->GetParent();

	while(auxParent != NULL){
		printMatrix(toReturn);
		toReturn = ((TTransform*)auxParent->GetEntity())->GetTransform() * toReturn;
		auxParent = auxParent->GetParent();
	}
	
	return toReturn;
}

void sendViewMatrix(Program* prog, glm::mat4 view){
	GLint uniView = glGetUniformLocation(prog->GetProgramID(), "ViewMatrix");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
}

TNode* InitializeTree(Program* prog){
	// MAIN MENU
	TTransform* aux = new TTransform();
	TNode* parent = new TNode(aux);
	//std::cout<<"PARENT: "<< parent << " CREADO\n";

	node1Rot = new TTransform();
	//aux->Rotate(1.0f, 0.0f, 0.0f, 90.0f);
	TNode* node1 = new TNode(parent, node1Rot);
	//std::cout<<"NODE1 : "<< node1 << " CREADO | Hijo de PARENT: " << node1->GetParent() << "\n";

	aux = new TTransform();
	//aux->Rotate(1.0f, 0.0f, 0.0f, 90.0f);
	//TNode* node2 = new TNode(parent, aux);
	//std::cout<<"NODE2 : "<< node2 << " CREADO | Hijo de PARENT: " << node2->GetParent() << "\n";

	aux = new TTransform();
	aux->Translate(0.0f, 0.0f, 0.0f);
	TNode* node3 = new TNode(node1, aux);
	//std::cout<<"NODE3 : "<< node3 << " CREADO | Hijo de  NODE1: " << node3->GetParent() << "\n";

	aux = new TTransform();
	aux->Translate(0.0f, 0.0f, 0.0f);
	//TNode* node4 = new TNode(node2, aux);
	//std::cout<<"NODE4 : "<< node4 << " CREADO | Hijo de  NODE2: " << node4->GetParent() << "\n";

	TMesh* mesh = new TMesh();
	/*TNode* nmesh1 = */ new TNode(node3, mesh);
	mesh->SetProgram(prog);
	//std::cout<<"nmesh1 : "<< nmesh1 << " CREADO | Hijo de  NODE3: " << nmesh1->GetParent() << "\n";

	/*TMesh* mesh2 = new TMesh();
	TNode* nmesh2 = new TNode(node4, mesh2);
	mesh2->SetProgram(prog);*/
	//std::cout<<"nmesh2 : "<< nmesh2 << " CREADO | Hijo de  NODE4: " << nmesh2->GetParent() << "\n";

	aux = new TTransform();
	aux->Rotate(1.0f, 0.0f, 0.0f, 0.0f);
	TNode* node5 = new TNode(parent, aux);

	aux = new TTransform();
	aux->Translate(0.0f, 0.0f, -5.0f);
	TNode* node6 = new TNode(node5, aux);
	
	TCamera* camera = new TCamera(true, -1.0f, 1.0f, -0.75f, 0.75f, 2.0f, 10.0f, prog);
	TNode* cameraNode = new TNode(node6, camera);

/**/
	glm::mat4 view = glm::mat4(1.0f);
	view = GetTransformInTree(cameraNode);
	sendViewMatrix(prog, view);

	//view = glm::lookAt( glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));
	//proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 1.0f, 100.0f);
	//proj = glm::frustum(-1.0f, 1.0f, -0.75f, 0.75f, 2.0f, 10.0f);
	//proj = glm::ortho(-1.0f, 1.0f, -0.75f, 0.75f, 1.0f, 10.0f);
/**/

	//std::cout<<"############################################################\n";

	return parent;
}

void addVertices(float x, float y){
	node1Rot->Rotate(0.0f, 1.0f, 0.0f, x);
	node1Rot->Rotate(1.0f, 0.0f, 0.0f, y);
}

int main(){
	sf::ContextSettings context = sf::ContextSettings(24, 8, 4, 3);
    sf::Window App(sf::VideoMode(800, 600, 32), "SFML OpenGL Test", sf::Style::Close, context);

	/// Iniciamos glew
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_TEXTURE_2D);
	// Habilidad el test de profundidad
	glEnable(GL_DEPTH_TEST);
	// Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
	glDepthFunc(GL_LESS);

	/// Creamos el Array de vertices del objeto
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	/// Cargamos los shaders para el progama
	std::map<std::string, GLenum> shaders = std::map<std::string, GLenum>();	
	shaders.insert(std::pair<std::string, GLenum>("../src/Shaders/VShader.glsl", GL_VERTEX_SHADER));
	shaders.insert(std::pair<std::string, GLenum>("../src/Shaders/FShader.glsl", GL_FRAGMENT_SHADER));
	
	// Creamos el programa y lo usamos
	Program* program = new Program(shaders);
	glUseProgram(program->GetProgramID());

	TNode* parent = InitializeTree(program);

	/// Bucle principal
	while (App.isOpen()){

        sf::Event event;
		while (App.pollEvent(event)){
            if (event.type == sf::Event::Closed) App.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)){
                App.close();
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)){
				addVertices(-2, 0);
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)){
				addVertices(2, 0);
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)){
				addVertices(0, -2);
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)){
				addVertices(0, 2);				
			}
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space)){
			}
        }
		//glDepthMask(true);
		glClearColor(0.7, 0.7, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        parent->Draw();
		App.display();
    }


	delete program;

    glDeleteVertexArrays(1, &vao);

	//std::cout << "Deleting TREE\n";
	delete parent;
	//	std::cout << "TREE DELETED\n";
    App.close();
    return EXIT_SUCCESS;
}