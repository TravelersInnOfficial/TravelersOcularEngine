#include "TRect.h"
#include "../TOcularEngine/VideoDriver.h"

//STATIC PROPERTIES
int TRect::m_size = 0;
GLuint TRect::m_uvbo = 0;
GLuint TRect::m_vbo = 0;
TResourceTexture* TRect::m_texture = nullptr;
toe::core::TOEvector4df TRect::m_color = toe::core::TOEvector4df(0,0,0,1);

//CONSTRUCTOR
TRect::TRect(   
    toe::core::TOEvector2df size, 
    std::string texture,
    toe::core::TOEvector2df position){
    
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_uvbo);

    if(texture.compare("")!=0){
	    m_texture = TResourceManager::GetInstance()->GetResourceTexture(texture); 
    }

    m_program = TWOD_SHADER;
}

//DESCTRUCTOR
TRect::~TRect(){}

void TRect::SendShaderData(){
    Program* myProgram = VideoDriver::GetInstance()->GetProgram(m_program);
    glUseProgram(myProgram->GetProgramID());
 
    //2DTEST////////////////////
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
         
    GLuint vertexbuffer;
    // Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
    glGenBuffers(1, &vertexbuffer);
    // Los siguientes comandos le darán características especiales al 'vertexbuffer' 
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Darle nuestros vértices a  OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // 1rst attribute buffer : vértices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
        3,                  // tamaño
        GL_FLOAT,           // tipo
        GL_FALSE,           // normalizado?
        0,                    // Paso
        (void*)0            // desfase del buffer
    );
    // Dibujar el triángulo 
    glDrawArrays(GL_TRIANGLES, 0, 3); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
    glDisableVertexAttribArray(0);
    //2DTEST////////////////////
}

void TRect::BeginDraw(){
    SendShaderData();
    glDrawArrays(GL_TRIANGLES,0,m_size);
}

void TRect::EndDraw(){

}

