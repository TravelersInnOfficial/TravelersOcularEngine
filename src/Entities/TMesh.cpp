#include "TMesh.h"
#include <GL/glew.h>

TMesh::TMesh(){

}

TMesh::~TMesh(){}

void TMesh::BeginDraw(){
    // Dibujar malla
	/*GLint viewUniform = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(m_stack));*/
}

void TMesh::EndDraw(){}