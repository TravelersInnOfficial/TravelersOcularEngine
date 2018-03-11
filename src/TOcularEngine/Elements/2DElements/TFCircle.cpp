#include "TFCircle.h"
#include "TFDrawable.h"
#include <GL/glew.h>

TFCircle::TFCircle(toe::core::TOEvector2df position){
	m_position = toe::core::TOEvector2df(0,0);
}

TFCircle::~TFCircle(){}

void TFCircle::Draw() const{
    //EL CERO ESTA EN EL CENTRO DE LA PANTALLA (0.0f, 0.0f, 0.0f)
    //ESQUINA INFERIOR IZQUIERDA (-1.0f, -1.0f, 0.0f)
    GLfloat vertices[] =
    {
        -1.0f, -1.0f, 0.0f, // Left
        -0.5f, -1.0f, 0.0f, // Right
        -0.75f,  -0.5f, 0.0f  // Top
    };
    
    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, 0 ); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray( 0 ); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	
	//glUseProgram( shaderProgram );
	//glUseProgram(GetProgram(TWOD_SHADER)->GetProgramID());
	glBindVertexArray( VAO );
    glDrawArrays( GL_TRIANGLES, 0, 3 );
}