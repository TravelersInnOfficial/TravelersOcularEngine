#include "TFRect.h"
#include <GL/glew.h>
#include "./../../../EngineUtilities/Resources/Program.h"
#include "./../../VideoDriver.h"
#include <cmath>  

TFRect::TFRect(toe::core::TOEvector2df size, toe::core::TOEvector2df position, float rotation){
    //std::cout<<"TRect \t in params\n";
    //std::cout<<"size ("<<size.X<<","<<size.Y<<")\n";
    //std::cout<<"postion ("<<position.X<<","<<position.Y<<")\n";
    //std::cout<<"rotation: "<<rotation <<"\n";
    w_dims = VideoDriver::GetInstance()->GetWindowDimensions();

    m_size = toe::core::TOEvector2df(std::abs(size.X * 10) / w_dims.X, std::abs(size.Y * 10) / w_dims.Y);
    m_position = toe::core::TOEvector2df((position.X - w_dims.X) / w_dims.X , (position.Y - w_dims.Y) / w_dims.Y);
    m_rotation = rotation;
    //std::cout<<"TRect \t private params\n";
    //std::cout<<"m_size ("<<m_size.X<<","<<m_size.Y<<")\n";
    //std::cout<<"m_postion ("<<m_position.X<<","<<m_position.Y<<")\n";
    //std::cout<<"m_rotation: "<<m_rotation <<"\n";
    //0,0 en la esquina inferior izquierda


}

TFRect::~TFRect(){}

void TFRect::Draw() const{

    Program* myProgram = VideoDriver::GetInstance()->GetProgram(m_program);
    glUseProgram(myProgram->GetProgramID());


    //https://open.gl/media/img/c2_dc.png Screen coordinates
    float vertices[] =
    {
        //first triangle
        m_position.X, m_position.Y, 0.0f,
        m_position.X + m_size.X, m_position.Y, 0.0f,
        m_position.X, m_position.Y + m_size.Y, 0.0f,

        //second triangle
        m_position.X + m_size.X, m_position.Y, 0.0f,
        m_position.X + m_size.X, m_position.Y + m_size.Y, 0.0f,
        m_position.X, m_position.Y + m_size.Y, 0.0f

    };
    
    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    
    GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray(posAttrib);

    glBindBuffer( GL_ARRAY_BUFFER, 0 ); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray( 0 ); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	glBindVertexArray( VAO );
    glDrawArrays(GL_TRIANGLES, 0, 6);
}