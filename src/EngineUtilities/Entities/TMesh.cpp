#include "TMesh.h"

#include "../TOcularEngine/VideoDriver.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

TMesh::TMesh(std::string meshPath, std::string texturePath){
	m_mesh = nullptr;
	m_texture = nullptr;
	m_material = nullptr;
	m_visibleBB = false;

	LoadMesh(meshPath);
	ChangeTexture(texturePath);
	m_program = STANDARD_SHADER;
}

TMesh::~TMesh(){ }

void TMesh::LoadMesh(std::string meshPath){
	if(meshPath.compare("")==0) meshPath = VideoDriver::GetInstance()->GetAssetsPath() + "/models/cube.obj";
	m_mesh = TResourceManager::GetInstance()->GetResourceMesh(meshPath);
}

void TMesh::ChangeTexture(std::string texturePath){
	if(texturePath.compare("")!=0) m_texture = TResourceManager::GetInstance()->GetResourceTexture(texturePath);
	else m_texture = nullptr;
}

void TMesh::SetBBVisibility(bool visible){
	m_visibleBB = visible;
}

void TMesh::BeginDraw(){
	if(m_mesh != nullptr && CheckClipping()){
		// Bind and send the data to the VERTEX SHADER
		SendShaderData();
		// Bind and draw elements depending of how many vbos
		GLuint elementsBuffer = m_mesh->GetElementBuffer();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBuffer);
		glDrawElements(GL_TRIANGLES, m_mesh->GetElementSize(), GL_UNSIGNED_INT, 0);

		// Draw bounding box
		if(m_visibleBB)DrawBoundingBox();
	}
}

void TMesh::EndDraw(){
}

void TMesh::SendShaderData(){
	Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(m_program);

	// -------------------------------------------------------- ENVIAMOS EL TIME
	float time = VideoDriver::GetInstance()->GetTime();
	GLint timeLocation = glGetUniformLocation(myProgram->GetProgramID(), "uTime");
	glUniform1f(timeLocation, time/1000);

    // -------------------------------------------------------- ENVIAMOS LOS VERTICES
    // BIND VERTEX
    GLuint vertexBuffer = m_mesh->GetVertexBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// SEND THE VERTEX
	GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");
	glVertexAttribPointer(posAttrib,3, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	// -------------------------------------------------------- ENVIAMOS LAS NORMALS
	// BIND THE NORMALS
    GLuint normalBuffer = m_mesh->GetNormalBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);

	// SEND THE NORMALS
	GLuint normAttrib = glGetAttribLocation(myProgram->GetProgramID(), "VertexNormal");
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
	glEnableVertexAttribArray(normAttrib);

	// -------------------------------------------------------- ENVIAMOS LAS UV
	// BIND THE UV
    GLuint uvBuffer = m_mesh->GetUvBuffer();
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);

	// SEND THE UV
	GLuint uvAttrib = glGetAttribLocation(myProgram->GetProgramID(), "TextureCoords");
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
	glEnableVertexAttribArray(uvAttrib);

	// -------------------------------------------------------- ENVIAMOS LAS MATRICES
	// SEND THE MODEL MATRIX
	GLint mmLocation = glGetUniformLocation(myProgram->GetProgramID(), "ModelMatrix");
	glUniformMatrix4fv(mmLocation, 1, GL_FALSE, glm::value_ptr(m_stack.top()));

	// SEND THE VIEW MATRIX
	GLint vLocation = glGetUniformLocation(myProgram->GetProgramID(), "ViewMatrix");
	glUniformMatrix4fv(vLocation, 1, GL_FALSE, glm::value_ptr(ViewMatrix));

	GLint v2Location = glGetUniformLocation(myProgram->GetProgramID(), "ViewMatrix2");
	glUniformMatrix4fv(v2Location, 1, GL_FALSE, glm::value_ptr(ViewMatrix));

	// SEND THE MODELVIEW MATRIX
	glm::mat4 modelView = ViewMatrix * m_stack.top();
	GLint mvLocation = glGetUniformLocation(myProgram->GetProgramID(), "ModelViewMatrix");
	glUniformMatrix4fv(mvLocation, 1, GL_FALSE, glm::value_ptr(modelView));

	// SEND THE PROJECTION MATRIX
	glm::mat4 pMatrix = ProjMatrix;
	GLint pLocation = glGetUniformLocation(myProgram->GetProgramID(), "ProjectionMatrix");
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(pMatrix));

	// SEND THE MODELVIEWPROJECTION MATRIX
	glm::mat4 mvpMatrix = ProjMatrix * modelView;
	GLint mvpLocation = glGetUniformLocation(myProgram->GetProgramID(), "MVP");
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	// SEND THE NORMAL MATRIX (ROTAMOS LAS NORMALES)
	glm::mat3 normalMatrix = m_stack.top();
	normalMatrix = glm::transpose(glm::inverse(normalMatrix));
	GLint normalMLocation = glGetUniformLocation(myProgram->GetProgramID(), "NormalMatrix");
	glUniformMatrix3fv(normalMLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	// -------------------------------------------------------- ENVIAMOS LA TEXTURA
	TResourceTexture* currentTexture = nullptr;
	if(m_texture != nullptr) currentTexture = m_texture;
	else if(m_mesh != nullptr) currentTexture = m_mesh->GetTexture();

	if(currentTexture != nullptr){
		GLuint TextureID = glGetUniformLocation(myProgram->GetProgramID(), "myTextureSampler");
		glUniform1i(TextureID, 0); 

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, currentTexture->GetTextureId());
	}

	// -------------------------------------------------------- ENVIAMOS EL MATERIAL
	TResourceMaterial* currentMaterial = nullptr;
	if(m_material != nullptr) currentMaterial = m_material;
	if(currentMaterial == nullptr) currentMaterial = m_mesh->GetMaterial();

	if(currentMaterial != nullptr){
		GLuint shininess = glGetUniformLocation(myProgram->GetProgramID(), "Material.Shininess");
		glUniform1f(shininess, currentMaterial->GetShininess());

		GLuint diffuse = glGetUniformLocation(myProgram->GetProgramID(), "Material.Diffuse");
		glUniform3fv(diffuse, 1, glm::value_ptr(currentMaterial->GetColorDifuse()));

		GLuint specular = glGetUniformLocation(myProgram->GetProgramID(), "Material.Specular");
		glUniform3fv(specular, 1, glm::value_ptr(currentMaterial->GetColorSpecular()));

		GLuint ambient = glGetUniformLocation(myProgram->GetProgramID(), "Material.Ambient");
		glUniform3fv(ambient, 1, glm::value_ptr(currentMaterial->GetColorAmbient()));
	}

}

// Funcion basada en https://en.wikibooks.org/wiki/OpenGL_Programming/Bounding_box
void TMesh::DrawBoundingBox() {
	Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(BB_SHADER);
	/*
	if (mesh->vertices.size() == 0)
		return;
	*/

	// Cube 1x1x1, centered on origin
	GLfloat vertices[] = {
		-0.5, -0.5, -0.5, 1.0,
		0.5, -0.5, -0.5, 1.0,
		0.5,  0.5, -0.5, 1.0,
		-0.5,  0.5, -0.5, 1.0,
		-0.5, -0.5,  0.5, 1.0,
		0.5, -0.5,  0.5, 1.0,
		0.5,  0.5,  0.5, 1.0,
		-0.5,  0.5,  0.5, 1.0,
	};
	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort elements[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 4, 1, 5, 2, 6, 3, 7
	};
	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glm::mat4 transform = glm::scale(glm::mat4(1), m_mesh->GetSize());

	// Apply object's transformation matrix 
	glm::mat4 m = ProjMatrix * ViewMatrix * m_stack.top() * transform;
	GLuint uniform_m = glGetUniformLocation(myProgram->GetProgramID(), "MVP");
	glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(m));

	// Send light color
	GLuint linecolor = glGetUniformLocation(myProgram->GetProgramID(), "LineColor");
	glUniform3fv(linecolor, 1, glm::value_ptr(glm::vec3(0.3f, 0.7f, 1.0f)));

	// Send each vertex data
	GLuint attribute_v_coord = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glEnableVertexAttribArray(attribute_v_coord);

	glVertexAttribPointer(
		attribute_v_coord,  // attribute
		4,                  // number of elements per vertex, here (x,y,z,w)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4*sizeof(GLushort)));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8*sizeof(GLushort)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(attribute_v_coord);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &ibo_elements);
}

bool TMesh::CheckClipping(){
	bool output = false;
	glm::vec3 center = m_mesh->GetCenter();
	glm::vec3 size = m_mesh->GetSize();

	glm::mat4 mvpMatrix = ProjMatrix * ViewMatrix * m_stack.top();
	// Comprobamos el cliping con los 8 puntos 

	for(int i=-1; i<=0 && !output; i++){
		// +X -X
		for(int j=-1; j<=0 && !output; j++){
			// +Y -Y
			for(int k=-1; k<=0 && !output; k++){
				// +Z -Z
				glm::vec3 point = center + glm::vec3(size.x/2.0f * Sign(i), size.y/2.0f * Sign(j), size.z/2.0f * Sign(k));
				glm::vec4 mvpPoint = mvpMatrix * glm::vec4(point.x, point.y, point.z, 1.0f);

				output = CheckClippingPoint(mvpPoint);
			}
		}
	}


	return output;
}

int TMesh::Sign(float v){
	if(v>=0) return 1;
	else return -1;
}