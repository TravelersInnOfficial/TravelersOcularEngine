#include <iostream>
#include "TNode.h"
#include "Entities/TEntity.h"
#include "Entities/TTransform.h"
#include "Entities/TMesh.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

//#include <iostream>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLuint LoadShader(const char *shaderFile, GLenum type)
{
    std::ifstream in(shaderFile);
    std::string src= "";
    std::string line="";
    while(std::getline(in,line))
    	src += line + "\n";
    std::cout << src;
    
    const char* source = src.c_str();
	//GLint compiled;
    GLuint shaderID = glCreateShader(type);
    glShaderSource(shaderID,1,&source,NULL);
    glCompileShader(shaderID);
    
	if(!shaderID)
    {
        std::cerr << "Could not compile the shader";
        return 0;
    }

    GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
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

GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{	
	// Creamos el programa y le añadimos los shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// no es necesario porque no se escribe en mas de un buffer
	//glBindFragDataLocation(shaderProgram, 0, "outColor");

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

int main() 
{
    sf::Window App(sf::VideoMode(600, 600, 32), "SFML OpenGL Test", sf::Style::Close);

	// Iniciamos glew
	glewExperimental = GL_TRUE;
	glewInit();

	// Creamos el Array de vertices del objeto
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
	
	// Definimos los vertices del objeto
	float vertices[] = {
		 0.0f,  0.5f, 0.5f,  // Vertice 0 (X, Y)
		-0.5f, -0.5f, 0.1f,  // Vertice 1 (X, Y)
		 0.5f, -0.5f, 1.0f,  // Vertice 2 (X, Y)
		 1.0f,  0.5f, 0.1f   // Vertice 3 (X, Y)
	};

	// Definimos el buffer de vertices del objeto
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Definimos los elementos (los vertices en este caso), que vamos a usar
	GLuint elements[] = {
		0,1,2,		// Vertices 0, 1, 2
		0,2,3		// Vertices 0, 2, 3
	};

	// Definimos el buffer de elementos del objeto
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Cargamos los shaders
	GLuint vs = LoadShader("../src/Shaders/VShader.glsl", GL_VERTEX_SHADER);
	GLuint fs = LoadShader("../src/Shaders/FShader.glsl", GL_FRAGMENT_SHADER);
	
	// Creamos el programa y lo usamos
	GLuint program = CreateProgram(vs, fs);
	
	// Empezamos a usar los shaders en el programa
	glUseProgram(program);

	GLint posAttrib = glGetAttribLocation(program, "position");
	//glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLint colorAttrib = glGetAttribLocation(program, "vertexColor");
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorAttrib, 1, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(colorAttrib);

	glm::mat4 transfMat = glm::mat4(1.0f);
	transfMat = glm::rotate(transfMat, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	GLint transUniform = glGetUniformLocation(program, "transform");
	glUniformMatrix4fv(transUniform, 1, GL_FALSE, glm::value_ptr(transfMat));

	/*
	GLint posAttrib = glGetAttribLocation(program, "VertexPosition");
	GLint normalAttrib = glGetAttribLocation(program, "VertexNormal");
	GLint textAttrib = glGetAttribLocation(program, "TextureCoords");
	
	glVertexAttribPointer(posAttrib,    4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(textAttrib,   2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(normalAttrib);
	glEnableVertexAttribArray(textAttrib);
	*/
	
	/*
	GLdouble h = 0.0f;
    GLdouble v = 0.0f;
    GLdouble l = 0.0f;
	*/

	// Activamos el z buffer
	glEnable(GL_DEPTH_TEST);

	glClearDepth(1.f);

    while (App.isOpen())
    {
        sf::Event event;
		while (App.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                App.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)){
                App.close();
			}
        }

        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

		/*
        glLoadIdentity();
        glRotated(l,0.0f,0.0f,0.2f);
        glRotated(h,0.2f,0.0f,0.0f);
        glRotated(v,0.0f,0.2f,0.0f);
		*/

		//drawCube();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glFlush();

        App.display();       
    }

	glDeleteProgram(program);
    glDeleteShader(fs);
    glDeleteShader(vs);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    App.close();

    return EXIT_SUCCESS;
}


/*
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
*/