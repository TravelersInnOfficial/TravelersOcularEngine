#include "TFSprite.h"
#include <GL/glew.h>
#include "./../../../EngineUtilities/Resources/TResourceTexture.h"
#include "./../../../EngineUtilities/TResourceManager.h"
#include "./../../../EngineUtilities/Resources/Program.h"
#include "./../../VideoDriver.h"
#include "./../TOcularEngine/TOcularEngine.h"

TFSprite::TFSprite(std::string texture, TOEvector2df position, TOEvector2df size){
    w_dims = VideoDriver::GetInstance()->GetWindowDimensions();

    //Calculate position and size in OpenGL units
    m_position  = TOEvector2df((position.X*2 - w_dims.X) / w_dims.X , (position.Y*2 - w_dims.Y) / w_dims.Y);
    m_size      = TOEvector2df((size.X *2) / w_dims.X, (size.Y *2) / w_dims.Y);
    m_rotation    = 0;

    //Load the texture resource
    if(texture.compare("")==0) texture = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/invisible_texture.png";
	m_texture = TResourceManager::GetInstance()->GetResourceTexture(texture);
    m_texture_size = size;
    m_rect = TOEvector4df(0.0f, 0.0f,1.0f, 1.0f);       //initially the recangle is the whole texture size (0 to 1 OpenGL coordinates)
    m_mask_rect = TOEvector4df(0.0f, 0.0f,1.0f, 1.0f);  //initially the recangle is the whole texture size (0 to 1 OpenGL coordinates)

    //Shader program
    m_program = SPRITE_SHADER;

    //Save the position and size data in pixel units
    m_InData.position = position;
    m_InData.size = size;
    m_InData.texture = texture;

    //Bind buffers
    m_VBO = 0;
    glGenBuffers(1, &m_VBO);

    //Initial over color
    m_color.SetRGBA(1,1,1,1);

    //Initial texture scroll velocity
    scrollH = 0;
    scrollV = 0;
    std::string mask = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_texture.png";
    m_mask = TResourceManager::GetInstance()->GetResourceTexture(mask);
}

TFSprite::~TFSprite(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);   
    glDeleteBuffers(1, &m_VBO);
}

void TFSprite::SetRect(float x, float y, float w, float h){
    if(x < 0) x = 0;
    if(y < 0) y = 0;
    float sheetWidth = m_texture_size.X;                        //texture width
    float sheetHeight = m_texture_size.Y;                       //texture height
    float cellWidth = w;                                        //cell widht
    float cellHeight = h;                                       //cell height
    float left = x/sheetWidth;                                  //left texture uv point
    float top = y/sheetHeight;                                  //top texture uv point
    float cw = left + cellWidth/sheetWidth;                     //uv texture width
    float ch = top + cellHeight/sheetHeight;                    //uv texture height
    m_rect = TOEvector4df(left, top, cw, ch);
    m_mask_rect = TOEvector4df(left, top, cw, ch);
    SetSize(w,h);
}

void TFSprite::SetTextureRect(float x, float y, float w, float h){
    m_rect = TOEvector4df(x, y, w+x, h+y);
}

void TFSprite::SetTexture(std::string texture){
    if(texture.compare("")==0) texture = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/invisible_texture.png";
	m_texture = TResourceManager::GetInstance()->GetResourceTexture(texture);
    m_InData.texture = texture;
}

std::string TFSprite::GetTexture() const {return m_InData.texture;}

void TFSprite::Draw() const{
    Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(m_program);

    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Rotation calculation
    glm::mat2 rotationMatrix;
    float rotRadian = m_rotation * M_PI / 180.0f;
    rotationMatrix[0] = glm::vec2(cos(rotRadian), -sin(rotRadian));
    rotationMatrix[1] = glm::vec2(sin(rotRadian),  cos(rotRadian));

    glm::vec2 upLeftCorner(-m_size.X/2, m_size.Y/2);
    glm::vec2 upRightCorner(m_size.X/2, m_size.Y/2);
    glm::vec2 downLeftCorner(-m_size.X/2, -m_size.Y/2);
    glm::vec2 downRightCorner(m_size.X/2, -m_size.Y/2);

    upLeftCorner    = (rotationMatrix * upLeftCorner)       + glm::vec2(m_size.X/2, m_size.Y/2);
    upRightCorner   = (rotationMatrix * upRightCorner)      + glm::vec2(m_size.X/2, m_size.Y/2);
    downLeftCorner  = (rotationMatrix * downLeftCorner)     + glm::vec2(m_size.X/2, m_size.Y/2);
    downRightCorner = (rotationMatrix * downRightCorner)    + glm::vec2(m_size.X/2, m_size.Y/2);

    float vertices[] = {
//      X+RECT                              Y+RECT                              U+HORIZONTAL SCROLL V+VERTICAL SCROLL   U-MASK           V-MASK            COLOR(RGBA)
        m_position.X + downLeftCorner.x,    m_position.Y + downLeftCorner.y,    m_rect.X +scrollH,  m_rect.Y2+scrollV,  m_mask_rect.X ,  m_mask_rect.Y2,   m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_position.X + downRightCorner.x,   m_position.Y + downRightCorner.y,   m_rect.X2+scrollH,  m_rect.Y2+scrollV,  m_mask_rect.X2,  m_mask_rect.Y2,   m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_position.X + upLeftCorner.x,      m_position.Y + upLeftCorner.y,      m_rect.X +scrollH,  m_rect.Y+scrollV,   m_mask_rect.X ,  m_mask_rect.Y,    m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),

        m_position.X + downRightCorner.x,   m_position.Y + downRightCorner.y,   m_rect.X2+scrollH,  m_rect.Y2+scrollV,  m_mask_rect.X2 , m_mask_rect.Y2,   m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_position.X + upRightCorner.x,     m_position.Y + upRightCorner.y,     m_rect.X2+scrollH,  m_rect.Y+scrollV,   m_mask_rect.X2,  m_mask_rect.Y,    m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_position.X + upLeftCorner.x,      m_position.Y + upLeftCorner.y,      m_rect.X +scrollH,  m_rect.Y+scrollV,   m_mask_rect.X ,  m_mask_rect.Y,    m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA()
    };

    //Bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    //Position data
    GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 10*sizeof(float),  0);

    //Texture coords
    GLuint uvAttrib = glGetAttribLocation(myProgram->GetProgramID(), "TextureCoords");
    glEnableVertexAttribArray(uvAttrib);
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 10*sizeof(float), (const GLvoid*)(2 * sizeof(float)));
    
    //Mask coords
    GLuint uvMaskAttrib = glGetAttribLocation(myProgram->GetProgramID(), "MaskCoords");
    glEnableVertexAttribArray(uvMaskAttrib);
    glVertexAttribPointer(uvMaskAttrib, 2, GL_FLOAT, GL_FALSE, 10*sizeof(float), (const GLvoid*)(4 * sizeof(float)));
    
    //Load the texture 
	GLuint TextureID = glGetUniformLocation(myProgram->GetProgramID(), "uvMap");
	glUniform1i(TextureID, 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureId());
    
    //Load mask texture
    GLuint MaskID = glGetUniformLocation(myProgram->GetProgramID(), "myMask");
    glUniform1i(MaskID, 1);

    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_mask->GetTextureId());

    //Color attribute
    GLuint colAttrib = glGetAttribLocation(myProgram->GetProgramID(), "overColor");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 10*sizeof(float), (const GLvoid*)(6 * sizeof(float)));

    //Draw the elements
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Disable blend mode
    glDisable(GL_BLEND);
}

void TFSprite::ScrollH(float vel){
    scrollH += vel;
    if(scrollH > 1) scrollH -= 1.0f;
    else if(scrollH < 0) scrollH += 1.0f;
}

void TFSprite::ScrollV(float vel){
    scrollV += vel;
    if(scrollV > 1) scrollV -= 1.0f;
    else if(scrollV < 0) scrollV += 1.0f;
}

void TFSprite::SetScrollH(float value){
    int real = (int)value;
    scrollH = value - real;
}

void TFSprite::SetScrollV(float value){
    int real = (int)value;
    scrollV = value - real;
}

void TFSprite::SetMask(std::string mask_path){
    if(mask_path.compare("")!=0) m_mask = TResourceManager::GetInstance()->GetResourceTexture(mask_path);
}

float TFSprite::GetTextureHeight(){
    return m_texture_size.Y;
}
float TFSprite::GetTextureWidth(){
    return m_texture_size.X;
}
TOEvector2df TFSprite::GetTextureSize(){
    return m_texture_size;
}