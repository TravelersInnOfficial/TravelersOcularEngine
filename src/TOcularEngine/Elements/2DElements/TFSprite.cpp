#include "TFSprite.h"
#include <GL/glew.h>
#include "./../../../EngineUtilities/Resources/TResourceTexture.h"
#include "./../../../EngineUtilities/TResourceManager.h"
#include "./../../../EngineUtilities/Resources/Program.h"
#include "./../../VideoDriver.h"

TFSprite::TFSprite( std::string texture, toe::core::TOEvector2df position, toe::core::TOEvector2df size){
    w_dims = VideoDriver::GetInstance()->GetWindowDimensions();

    m_position = new toe::core::TOEvector2df((position.X*2 - w_dims.X) / w_dims.X , (position.Y*2 - w_dims.Y) / w_dims.Y);
    m_size = new toe::core::TOEvector2df(m_position->X + (std::abs(size.X *2) / w_dims.X), m_position->Y + (std::abs(size.Y *2) / w_dims.Y));

    if(texture.compare("")==0) texture = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_sprite.png";
	m_texture = TResourceManager::GetInstance()->GetResourceTexture(texture);

    m_program = SPRITE_SHADER;

    m_InData.position = position;
    m_InData.size = size;
    m_InData.rotation = 0.0f;

    m_VAO = 0;
	glGenBuffers(1, &m_VAO);

    m_VBO = 0;
    glGenBuffers(1, &m_VBO);
}

TFSprite::~TFSprite(){
    delete m_size;
    delete m_position;
}

void TFSprite::Draw() const{
    Program* myProgram = VideoDriver::GetInstance()->GetProgram(m_program);
	glUseProgram(myProgram->GetProgramID());

    float vertices[] = {
        //  X     Y     Z                        U     V
         m_position->X, m_position->Y, 0.0f,    -1.0f,  0.0f,//-1.0f, -1.0f,
         m_size->X, m_position->Y, 0.0f,         0.0f,  0.0f,
         m_position->X, m_size->Y, 0.0f,        -1.0f, -1.0f,//-1.0f, 0.0f,
         
         m_size->X, m_position->Y, 0.0f,         0.0f,  0.0f,//0.0f, -1.0f,
         m_size->X, m_size->Y, 0.0f,             0.0f, -1.0f, //0.0f, 0.0f,
         m_position->X, m_size->Y, 0.0f,        -1.0f, -1.0f
    };

    glBindVertexArray( m_VAO );

    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    //posicion
    GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float),  0);

    //textura
    GLuint uvAttrib = glGetAttribLocation(myProgram->GetProgramID(), "TextureCoords");
    glEnableVertexAttribArray(uvAttrib);
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (const GLvoid*)(3 * sizeof(float)));

    // Enviamos la textura del sprite
	GLuint TextureID = glGetUniformLocation(myProgram->GetProgramID(), "myTextureSampler");
	glUniform1i(TextureID, 0);

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureId());

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void TFSprite::p_recalculate_size(){
    m_size = new toe::core::TOEvector2df(m_position->X + (std::abs(m_InData.size.X *2) / w_dims.X), m_position->Y + (std::abs(m_InData.size.Y *2) / w_dims.Y));
}

void TFSprite::SetPosition(float x, float y){
    m_position = new toe::core::TOEvector2df((x*2 - w_dims.X) / w_dims.X , (y*2 - w_dims.Y) / w_dims.Y);
    m_InData.position.X = x;
    m_InData.position.Y = y;
    p_recalculate_size();
}

void TFSprite::SetPosX(float x){
    m_position->X = (x*2 - w_dims.X) / w_dims.X;
    m_InData.position.X = x;
    p_recalculate_size();
}

void TFSprite::SetPosY(float y){
    m_position->Y = (y*2 - w_dims.Y) / w_dims.Y;
    m_InData.position.Y = y;
    p_recalculate_size();
}

void TFSprite::SetSize(float w, float h){
    m_size = new toe::core::TOEvector2df(m_position->X + (std::abs(w *2) / w_dims.X), m_position->Y + (std::abs(h *2) / w_dims.Y));
    m_InData.size.X = w;
    m_InData.size.Y = h;
}

void TFSprite::SetWidth(float w){
    m_size->X = m_position->X + (std::abs(w *2) / w_dims.X);
    m_InData.size.X = w;
}

void TFSprite::SetHeight(float h){
    m_size->Y =  m_position->Y + (std::abs(h *2) / w_dims.Y);
    m_InData.size.Y = h;
}

void TFSprite::Rotate(float deg){ 
    m_rotation += deg; 
    m_InData.rotation += deg; 
}

void TFSprite::SetRotation(float deg){
    m_rotation = deg;
    m_InData.rotation = deg;
}

void TFSprite::SetTexture(std::string texture){
    if(texture.compare("")==0) texture = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_sprite.png";
	m_texture = TResourceManager::GetInstance()->GetResourceTexture(texture);
}