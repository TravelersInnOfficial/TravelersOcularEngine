#include "TFRect.h"
#include <GL/glew.h>
#include "./../../../EngineUtilities/Resources/Program.h"
#include "./../../VideoDriver.h"

TFRect::TFRect(toe::core::TOEvector2df position, toe::core::TOEvector2df size, float rotation){
/*
    toe::core::TOEvector2df* m_position = nullptr;
    toe::core::TOEvector2df* m_size = nullptr;
    float* m_rotation = nullptr;
    TColor* m_color = nullptr;
*/
    w_dims = VideoDriver::GetInstance()->GetWindowDimensions();

    m_position = toe::core::TOEvector2df((position.X*2 - w_dims.X) / w_dims.X , (position.Y*2 - w_dims.Y) / w_dims.Y);
    m_size = toe::core::TOEvector2df(m_position.X + (std::abs(size.X *2) / w_dims.X), m_position.Y + (std::abs(size.Y *2) / w_dims.Y));

    m_color.SetRGBA(0,0,0,1);

    m_InData.position = position;
    m_InData.size = size;
    m_InData.texture = "";

    m_VAO = 0;
    glGenVertexArrays( 1, &m_VAO );
    m_VBO = 0;
    glGenBuffers( 1, &m_VBO );
}

TFRect::~TFRect(){}

void TFRect::Erase(){
    VideoDriver::GetInstance()->GetSceneManager()->Delete2Delement(this);
    TFRect::~TFRect();
}

void TFRect::ToBkg(){
    VideoDriver::GetInstance()->GetSceneManager()->PushToBkg(this);
}

void TFRect::ToFront(){
     VideoDriver::GetInstance()->GetSceneManager()->PushToFront(this);
}

void TFRect::Draw() const{

    Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(m_program);

    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //https://open.gl/media/img/c2_dc.png Screen coordinates
    float vertices[] =
    {
        //first triangle
        //POSITION                          COLOR
        m_position.X, m_position.Y,   m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_size.X, m_position.Y,       m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_position.X, m_size.Y,       m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),

        //second triangle
        //POSITION                          COLOR
        m_size.X, m_position.Y,       m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_size.X, m_size.Y,           m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_position.X, m_size.Y,       m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA()
    };

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( m_VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    
    GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray(posAttrib);

    GLint colAttrib = glGetAttribLocation(myProgram->GetProgramID(), "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2*sizeof(float)));

    glBindBuffer( GL_ARRAY_BUFFER, 0 ); // Note that this is allowed, the call to glVertexAttribPointer registered m_VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray( 0 ); // Unbind m_VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	glBindVertexArray( m_VAO );


    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisable(GL_BLEND);
}

void TFRect::p_recalculate_size(){
    m_size = toe::core::TOEvector2df(m_position.X + (std::abs(m_InData.size.X *2) / w_dims.X), m_position.Y + (std::abs(m_InData.size.Y *2) / w_dims.Y));
}

void TFRect::SetPosition(float x, float y){
    m_position = toe::core::TOEvector2df((x*2 - w_dims.X) / w_dims.X , (y*2 - w_dims.Y) / w_dims.Y);
    m_InData.position.X = x;
    m_InData.position.Y = y;
    p_recalculate_size();
}

void TFRect::SetPosX(float x){
    m_position.X = (x*2 - w_dims.X) / w_dims.X;
    m_InData.position.X = x;
    p_recalculate_size();
}

void TFRect::SetPosY(float y){
    m_position.Y = (y*2 - w_dims.Y) / w_dims.Y;
    m_InData.position.Y = y;
    p_recalculate_size();
}

void TFRect::SetSize(float w, float h){
    m_size = toe::core::TOEvector2df(m_position.X + (std::abs(w *2) / w_dims.X), m_position.Y + (std::abs(h *2) / w_dims.Y));
    m_InData.size.X = w;
    m_InData.size.Y = h;
}

void TFRect::SetWidth(float w){
    m_size.X = m_position.X + (std::abs(w *2) / w_dims.X);
    m_InData.size.X = w;
}

void TFRect::SetHeight(float h){
    m_size.Y =  m_position.Y + (std::abs(h *2) / w_dims.Y);
    m_InData.size.Y = h;
}

void TFRect::SetTexture(std::string texture){
    m_InData.texture = "";
}