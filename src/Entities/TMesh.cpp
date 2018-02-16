#include "TMesh.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <iostream>
#include <chrono>

TMesh::TMesh(){
	// TEMPORAL VERTICES AND ELEMENTS
	/*std::vector<float> vertices {
		 0.0f, 0.0f,  0.5f, 1.0f, 0.0f, 0.0f,  // Vertice 0 (X, Y)
		-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,  // Vertice 1 (X, Y)
		 0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f,  // Vertice 2 (X, Y)

		 0.0f, 0.0f,  0.5f, 1.0f, 0.0f, 0.0f,  // Vertice 0 (X, Y)
		-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,  // Vertice 1 (X, Y)
		-1.0f, 0.0f,  0.5f, 1.0f, 1.0f, 0.0f   // Vertice 3 (X, Y)
	};*/

	std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f
    };

	// Definimos los elementos (los vertices en este caso), que vamos a usar
	elements = {
		0,1,2,		// Vertices 0, 1, 2
		0,1,3		// Vertices 0, 2, 3
	};

	// MOST IMPORTANT LINE (1 hour to find this error)
	m_program = NULL;

	// Create vertex buffer for [vec3 vertexPosition, vec3 normalDirection, vec2 UVCoordinate]
	m_vbo = 0;
	glGenBuffers(1, &m_vbo);

	m_ebo = 0;
	glGenBuffers(1, &m_ebo);
	
	// Send vbo all of the vertices data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	// **This can be done is multiple ways**
	// ONE possible way is having a vertex array with all the information per vertex
	// [vec3 vertexPosition, vec3 normalDirection, vec2 UVCoordinate]
	// and send information with an offset 

	// Another possibility is creating 3 buffers one for each vector but needs 
	// its custom buffer data, and glVertexAttribPointer (with previous binding)
	
	// Send ebo all index of the faces (3 vertices)
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(float), &elements[0], GL_STATIC_DRAW);
}

TMesh::~TMesh(){
	//std::cout << "Deleting MESH: "<< this << "\n";
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glDeleteBuffers(1, &m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	
	glDeleteBuffers(1, &m_ebo);
}

void TMesh::BeginDraw(){
    // Send all attributes and uniforms to shader
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	SendShaderData();

	// Bind and draw elements depending of how many vbos
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	//glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);   

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TMesh::EndDraw(){
	// This method is empty
}

// PROVISIONAL FUNCTION
void TMesh::SetProgram(Program* prog){
	m_program = prog;
}

void TMesh::SendShaderData(){
	// If there is no Program, exit
	if(m_program == NULL){
		throw std::runtime_error("SHADER NOT ASSIGNED TO MESH");
	}

	// vertex position
	GLint posAttrib = glGetAttribLocation(m_program->GetProgramID(), "VertexPosition");
	glVertexAttribPointer(posAttrib,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	// vertex normal
	/*
	GLint normalAttrib = glGetAttribLocation(m_program->GetProgramID(), "vertexNormal");
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(normalAttrib);*/

	// uv texture
	GLint colorAttrib = glGetAttribLocation(m_program->GetProgramID(), "VertexColor");
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(colorAttrib);

	GLint viewUniform = glGetUniformLocation(m_program->GetProgramID(), "ModelViewMatrix");
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(m_stack.top()));
	//glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(m_stack.top()));
}

/*  CUBE VERTICES EXAMPLE

	std::vector<float> vertices {
		-1.000000f, -1.000000f,  1.000000f,
		-1.000000f,  1.000000f,  1.000000f,
		-1.000000f, -1.000000f, -1.000000f,
		-1.000000f,  1.000000f, -1.000000f,
		 1.000000f, -1.000000f,  1.000000f,
		 1.000000f,  1.000000f,  1.000000f,
		 1.000000f, -1.000000f, -1.000000f,
		 1.000000f,  1.000000f, -1.000000f
	};


	f 2//1 3//1 1//1
	f 4//2 7//2 3//2
	f 8//3 5//3 7//3
	f 6//4 1//4 5//4
	f 7//5 1//5 3//5
	f 4//6 6//6 8//6
	f 2//1 4//1 3//1
	f 4//2 8//2 7//2
	f 8//3 6//3 5//3
	f 6//4 2//4 1//4
	f 7//5 5//5 1//5
	f 4//6 2//6 6//6
	

	vn -1.0000 0.0000 0.0000
	vn 0.0000 0.0000 -1.0000
	vn 1.0000 0.0000 0.0000
	vn 0.0000 0.0000 1.0000
	vn 0.0000 -1.0000 0.0000
	vn 0.0000 1.0000 0.0000

	elements {
		2, 3, 1,
		4, 7, 3,
		8, 5, 7,
		6, 1, 5,
		7, 1, 3,
		4, 6, 8,
		2, 4, 3,
		4, 8, 7,
		8, 6, 5,
		6, 2, 1,
		7, 5, 1,
		4, 2, 6
	};
*/	