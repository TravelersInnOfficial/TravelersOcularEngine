#include <iostream>
#include "TNode.h"
#include "Entities/TEntity.h"
#include "Entities/TTransform.h"
#include "Entities/TMesh.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TResourceManager.h"
#include "Resources/TResourceMesh.h"

GLuint LoadShader(const char *shaderFile, GLenum type){
    std::ifstream in(shaderFile);
    std::string src = "";
    std::string line = "";
    while(std::getline(in,line)) src += line + "\n";
    std::cout << src;
    
    const char* source = src.c_str();
	//GLint compiled;
    GLuint shaderID = glCreateShader(type);
    glShaderSource(shaderID,1,&source,NULL);
    glCompileShader(shaderID);
    
	if(!shaderID){
        std::cerr << "Could not compile the shader";
        return 0;
    }

    GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE){
		std::string msg("Compile failure in shader:\n");

        GLint infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteShader(shaderID); shaderID = 0;
        throw std::runtime_error(msg);
	}

    return shaderID;
}

GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader){
	// Creamos el programa y le añadimos los shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// No es necesario porque no se escribe en mas de un buffer
	//glBindFragDataLocation(shaderProgram, 0, "outColor");
	// insert location binding code here
	//glBindAttribLocation(shaderProgram, 0, "position");
	//glBindAttribLocation(shaderProgram, 1, "vertexColor");

	// Se linkea el programa a los shaders
	glLinkProgram(shaderProgram);

	// Liberamos los shaders una vez unidos
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	// SE COMPRUEBA SI LINKEA BIEN
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::string msg("Program linking failure: ");

        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        msg += strInfoLog;
        delete[] strInfoLog;

        glDeleteProgram(shaderProgram); shaderProgram = 0;
        throw std::runtime_error(msg);
    }

	return shaderProgram;
}

TNode* InitializeTree(){
	// MAIN MENU
	TTransform* aux = new TTransform();
	TNode* parent = new TNode(aux);
	std::cout<<"PARENT: "<< parent << " CREADO\n";

	aux = new TTransform();
	aux->Rotate(0, 1, 0, 90);
	TNode* node1 = new TNode(parent, aux);
	std::cout<<"NODE1 : "<< node1 << " CREADO | Hijo de PARENT: " << node1->GetParent() << "\n";

	aux = new TTransform();
	aux->Translate(10, 0, 0);
	TNode* node2 = new TNode(parent, aux);
	std::cout<<"NODE2 : "<< node2 << " CREADO | Hijo de PARENT: " << node2->GetParent() << "\n";

	aux = new TTransform();
	aux->Translate(15, 0, 0);
	TNode* node3 = new TNode(node1, aux);
	std::cout<<"NODE3 : "<< node3 << " CREADO | Hijo de  NODE1: " << node3->GetParent() << "\n";

	aux = new TTransform();
	aux->Translate(0, 0, -10);
	TNode* node4 = new TNode(node1, aux);
	std::cout<<"NODE4 : "<< node4 << " CREADO | Hijo de  NODE1: " << node4->GetParent() << "\n";

	TMesh* mesh = new TMesh();
	TNode* mesh1 = new TNode(node3, mesh);
	std::cout<<"mesh1 : "<< mesh1 << " CREADO | Hijo de  NODE3: " << mesh1->GetParent() << "\n";

	std::cout<<"############################################################\n";

	return parent;
}

GLuint program = 0;

/// Definimos los vertices del objeto
std::vector<float> vertices {
	 0.0f,  0.5f,  1.0f, 0.0f, 0.0f,  // Vertice 0 (X, Y)
	-0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Vertice 1 (X, Y)
	 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Vertice 2 (X, Y)
	-1.0f,  0.5f,  1.0f, 1.0f, 0.0f   // Vertice 3 (X, Y)
};

// Definimos los elementos (los vertices en este caso), que vamos a usar
std::vector<GLuint> elements {
	0,1,2,		// Vertices 0, 1, 2
	0,1,3		// Vertices 0, 2, 3
};

GLuint buffers[3];

void printData(bool bol){
	if (bol){
		std::cout << "Vertices:";
		for (int i= 0; i<vertices.size(); i++){
			if(i%5 == 0)
				std::cout << "\n";

			std::cout << vertices[i] <<" ";
		}
		std::cout << "\n";
	}
	else{
		std::cout << "Elements:";
		for (int i= 0; i<elements.size(); i++){
			if(i%5 == 0)
				std::cout << "\n";

			std::cout << elements[i] <<" ";
		}
		std::cout << "\n";
	}
}

void sendAtributes2Shader(GLuint prog){
	// posicion
	GLint posAttrib = glGetAttribLocation(prog, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	// color
	GLint colorAttrib = glGetAttribLocation(prog, "vertexColor");
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(colorAttrib);

	// enviamos al uniform del shader la transformacion
	//glm::mat4 transfMat = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 transfMat = glm::mat4(1.0f);
	GLint viewUniform = glGetUniformLocation(prog, "transform");
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(transfMat));
}

void addVertices(){
	// Definimos los vertices del objeto
	/*std::vector<float> auxvertices{
		1.0f,  0.5f, 1.0f, 1.0f, 0.0f	// Vertice 2 (X, Y)
	};
	std::copy(begin(auxvertices), end(auxvertices), std::back_inserter(vertices));*/

	std::vector<float> vertices2{
		 1.0f,  0.5f,  0.0f, 1.0f, 0.0f,  // Vertice 0 (X, Y)
		 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Vertice 1 (X, Y)
		 1.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Vertice 2 (X, Y)
		 0.0f,  0.5f,  0.0f, 1.0f, 0.0f   // Vertice 3 (X, Y)
	};

	// Definimos el buffer de vertices del objeto
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(float), &vertices2[0], GL_STATIC_DRAW);

	/*// Definimos los elementos (los vertices en este caso), que vamos a usar
	std::vector<GLuint> auxelements {
		0,2,4		// Vertices 0, 1, 2
	};
	std::copy(begin(auxelements), end(auxelements), std::back_inserter(elements));

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), &elements[0], GL_STATIC_DRAW);*/

	std::cout << "###########################################################\n";
	std::cout << "Dibujamos los nuevos vertices\n";

	printData(true);
	printData(false);
}

void updateProgram(){
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	sendAtributes2Shader(program);
	glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);	
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	sendAtributes2Shader(program);
	glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);	
}

int main(){
    sf::Window App(sf::VideoMode(600, 600, 32), "SFML OpenGL Test", sf::Style::Close);

	printData(true);

	/// Iniciamos glew
	glewExperimental = GL_TRUE;
	glewInit();
	
	glEnable( GL_DEPTH_TEST ); 		// enable depth-testing
	glDepthFunc( GL_LESS );		 	// depth-testing interprets a smaller value as "closer"

	/// Creamos el Array de vertices del objeto
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	// Generamos el buffer de vertices del objeto
	glGenBuffers(3, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

	// Generamos el buffer de elementos del objeto
	//GLuint ebo;
	//glGenBuffers(1, &ebo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), &elements[0], GL_STATIC_DRAW);

	/// Cargamos los shaders
	GLuint vs = LoadShader("../src/Shaders/VShader.glsl", GL_VERTEX_SHADER);
	GLuint fs = LoadShader("../src/Shaders/FShader.glsl", GL_FRAGMENT_SHADER);
	
	// Creamos el programa y lo usamos
	program = CreateProgram(vs, fs);

	// Empezamos a usar los shaders en el programa
	glUseProgram(program);

	/// Obtenemos los atributos del shader
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	sendAtributes2Shader(program);
	
	/// Bucle principal
	while (App.isOpen()){
        sf::Event event;
		while (App.pollEvent(event)){
            if (event.type == sf::Event::Closed) App.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)){
                App.close();
			}
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space)){
                addVertices();
				//rotateModel(viewUniform);
			}
        }

        glClearColor(0.1, 0.1, 0.1, 0.1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		updateProgram();
        App.display();       
    }

	glDeleteProgram(program);
    glDeleteShader(fs);
    glDeleteShader(vs);

    glDeleteBuffers(3, buffers);
    glDeleteVertexArrays(1, &vao);

    App.close();
	TResourceMesh* newModel = new TResourceMesh("assets/models/cube.obj");

    return EXIT_SUCCESS;
}