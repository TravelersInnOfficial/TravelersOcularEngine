// PROVISONAL INCLUDES
#include "TNode.h"
#include "Entities/TEntity.h"
#include "Entities/TTransform.h"
#include "Entities/TMesh.h"
#include "Resources/Program.h"
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TResourceManager.h"
#include "Resources/TResourceMesh.h"

TNode* node3;

TNode* InitializeTree(Program* prog){
	// MAIN MENU
	TTransform* aux = new TTransform();
	TNode* parent = new TNode(aux);
	//std::cout<<"PARENT: "<< parent << " CREADO\n";

	aux = new TTransform();
	aux->Rotate(1.0f, 0.0f, 0.0f, 90.0f);
	TNode* node1 = new TNode(parent, aux);
	//std::cout<<"NODE1 : "<< node1 << " CREADO | Hijo de PARENT: " << node1->GetParent() << "\n";

	aux = new TTransform();
	aux->Rotate(1.0f, 0.0f, 0.0f, 90.0f);
	TNode* node2 = new TNode(parent, aux);
	//std::cout<<"NODE2 : "<< node2 << " CREADO | Hijo de PARENT: " << node2->GetParent() << "\n";

	aux = new TTransform();
	aux->Translate(0.0f, 0.0f, 0.0f);
	node3 = new TNode(node1, aux);
	//std::cout<<"NODE3 : "<< node3 << " CREADO | Hijo de  NODE1: " << node3->GetParent() << "\n";

	aux = new TTransform();
	aux->Translate(0.0f, 0.0f, 0.0f);
	TNode* node4 = new TNode(node2, aux);
	//std::cout<<"NODE4 : "<< node4 << " CREADO | Hijo de  NODE2: " << node4->GetParent() << "\n";

	TMesh* mesh = new TMesh();
	TNode* nmesh1 = new TNode(node3, mesh);
	mesh->SetProgram(prog);
	//std::cout<<"nmesh1 : "<< nmesh1 << " CREADO | Hijo de  NODE3: " << nmesh1->GetParent() << "\n";

	/*TMesh* mesh2 = new TMesh();
	TNode* nmesh2 = new TNode(node4, mesh2);
	mesh2->SetProgram(prog);*/
	//std::cout<<"nmesh2 : "<< nmesh2 << " CREADO | Hijo de  NODE4: " << nmesh2->GetParent() << "\n";

	//std::cout<<"############################################################\n";

	return parent;
}

void addVertices(float x, float y, GLuint uniView){/*
	glm::mat4 view = glm::lookAt( glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(5 * sin(glm::radians(x)), y, 50*cos(glm::radians(x))), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	// Definimos los vertices del objeto
	//std::cout << "###########################################################\n";
	//std::cout << "Dibujamos los nuevos vertices\n";*/


	TTransform* trans = (TTransform*) node3->GetEntity();
	trans->Translate(y, 0.0f, 0.0f);
}

void printMatrix(glm::mat4 mat){
	for (int i= 0; i<4; i++){
		for (int j = 0; j<4; j++)
			std::cout << mat[i][j] <<" ";

		std::cout << "\n";	
	}
	std::cout << "\n";
}

int main(){
    sf::Window App(sf::VideoMode(800, 600, 32), "SFML OpenGL Test", sf::Style::Close);

	/// Iniciamos glew
	glewExperimental = GL_TRUE;
	glewInit();
	
	glEnable( GL_DEPTH_TEST ); 		// enable depth-testing
	glDepthFunc( GL_LESS );		 	// depth-testing interprets a smaller value as "closer"

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

	glm::mat4 view = glm::mat4(1.0f);
	//glm::mat4 view = glm::lookAt( glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));
	GLint uniView = glGetUniformLocation(program->GetProgramID(), "ViewMatrix");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = glm::mat4(1.0f);
	//glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10.0f);
	//glm::mat4 proj = glm::frustum(-400.0f, 400.0f, -300.0f, 300.0f, 0.1f, 10.0f);
	//glm::mat4 proj = glm::frustum(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 10.0f);
	//glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 10.0f);
	
	GLint uniProj = glGetUniformLocation(program->GetProgramID(), "ProjectionMatrix");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	TNode* parent = InitializeTree(program);
	
	float x, y;
	x = 0;
	y = 1.0f;
	
	/// Bucle principal
	while (App.isOpen()){
        sf::Event event;
		while (App.pollEvent(event)){
            if (event.type == sf::Event::Closed) App.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)){
                App.close();
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)){
				x -= 1.0f;
				std::cout << "x: " << x << " y: " << y << "\n"; 
				addVertices(x, y, uniView);
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)){
				x += 1.0f;
				std::cout << "x: " << x << " y: " << y << "\n"; 
				addVertices(x, y, uniView);
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)){
				y -= 0.05f;				
				std::cout << "x: " << x << " y: " << y << "\n"; 
				addVertices(x, y, uniView);
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)){
				y += 0.05f;
				std::cout << "x: " << x << " y: " << y << "\n"; 
				addVertices(x, y, uniView);				
			}
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space)){
				addVertices(x, y, uniView);
			}
        }

        glClearColor(0.1, 0.1, 0.1, 0.1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        parent->Draw();
		App.display();
    }


	delete program;

    glDeleteVertexArrays(1, &vao);
	
	TResourceMesh* newModel = new TResourceMesh("../assets/models/cube.obj");
	delete newModel;

	//std::cout << "Deleting TREE\n";
	delete parent;
	//	std::cout << "TREE DELETED\n";
    App.close();
    return EXIT_SUCCESS;
}