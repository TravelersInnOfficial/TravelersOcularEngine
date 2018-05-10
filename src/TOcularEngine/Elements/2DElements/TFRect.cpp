#include "TFRect.h"
#include <GL/glew.h>
#include "./../../../EngineUtilities/TResourceManager.h"
#include "./../../../EngineUtilities/Resources/Program.h"
#include "./../../VideoDriver.h"

TFRect::TFRect(TOEvector2df position, TOEvector2df size, float rotation){
    w_dims = VideoDriver::GetInstance()->GetWindowDimensions();

    m_position = TOEvector2df((position.X*2 - w_dims.X) / w_dims.X , (position.Y*2 - w_dims.Y) / w_dims.Y);
    m_size = TOEvector2df((std::abs(size.X *2) / w_dims.X), (std::abs(size.Y *2) / w_dims.Y));
    m_rotation = 0;
    m_color.SetRGBA(0,0,0,1);
    
    m_mask_size = size;
    std::string mask = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_texture.png";
    m_mask = TResourceManager::GetInstance()->GetResourceTexture(mask);
    m_mask_rect = TOEvector4df(0.0f, 0.0f,1.0f, 1.0f);

    m_InData.position = position;
    m_InData.size = size;
    m_InData.texture = "";

    m_VBO = 0;
    glGenBuffers( 1, &m_VBO );
}

TFRect::~TFRect(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);   
    glDeleteBuffers(1, &m_VBO);
}

void TFRect::Erase(){
    std::cout<<"Erase TFRect"<<std::endl;
}

void TFRect::Draw() const{

    Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(m_program);

    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
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

    //https://open.gl/media/img/c2_dc.png Screen coordinates
    float vertices[] =
    {
        //first triangle
        //POSITION                                                              U-MASK V-MASK                       COLOR
        m_position.X + downLeftCorner.x,    m_position.Y + downLeftCorner.y,    m_mask_rect.X ,  m_mask_rect.Y2,    m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_position.X + downRightCorner.x,   m_position.Y + downRightCorner.y,   m_mask_rect.X2,  m_mask_rect.Y2,    m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_position.X + upLeftCorner.x,      m_position.Y + upLeftCorner.y,      m_mask_rect.X ,  m_mask_rect.Y,     m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),

        //second triangle
        //POSITION                                                              U-MASK V-MASK                      COLOR
        m_position.X + downRightCorner.x,   m_position.Y + downRightCorner.y,   m_mask_rect.X2 , m_mask_rect.Y2,   m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_position.X + upRightCorner.x,     m_position.Y + upRightCorner.y,     m_mask_rect.X2,  m_mask_rect.Y,    m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA(),
        m_position.X + upLeftCorner.x,      m_position.Y + upLeftCorner.y,      m_mask_rect.X ,  m_mask_rect.Y,    m_color.GetR(), m_color.GetG(), m_color.GetB(), m_color.GetA()
    };

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    
    GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray(posAttrib);

    //mask coords
    GLuint uvMaskAttrib = glGetAttribLocation(myProgram->GetProgramID(), "MaskCoords");
    glEnableVertexAttribArray(uvMaskAttrib);
    glVertexAttribPointer(uvMaskAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const GLvoid*)(2 * sizeof(float)));

    GLint colAttrib = glGetAttribLocation(myProgram->GetProgramID(), "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4*sizeof(float)));

    // Enviamos la mascara si tiene
    GLuint MaskID = glGetUniformLocation(myProgram->GetProgramID(), "myMask");
    glUniform1i(MaskID, 1);

    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_mask->GetTextureId());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisable(GL_BLEND);
}

void TFRect::SetWidth(float w){
    m_size.X = (std::abs(w *2) / w_dims.X);
    m_InData.size.X = w;

    float x = m_mask_size.Y - w;
    float y = 0;
    float sheetWidth = m_mask_size.X;                           //texture width
    float sheetHeight = m_mask_size.Y;                          //texture height
    float cellWidth = w;                                        //cell widht
    float cellHeight = sheetHeight;                             //cell height
    float left = x/sheetWidth;                                  //left texture uv point
    float top = y/sheetHeight;                                  //top texture uv point
    float cw = left + cellWidth/sheetWidth;                     //uv texture width
    float ch = top + cellHeight/sheetHeight;                    //uv texture height
    m_mask_rect = TOEvector4df(left, top, cw, ch);
}

void TFRect::SetHeight(float h){
    m_size.Y =  (std::abs(h *2) / w_dims.Y);
    m_InData.size.Y = h;

    float x = 0;
    float y = m_mask_size.Y - h;
    float sheetWidth = m_mask_size.X;                           //texture width
    float sheetHeight = m_mask_size.Y;                          //texture height
    float cellWidth = sheetWidth;                               //cell widht
    float cellHeight = h;                                       //cell height
    float left = x/sheetWidth;                                  //left texture uv point
    float top = y/sheetHeight;                                  //top texture uv point
    float cw = left + cellWidth/sheetWidth;                     //uv texture width
    float ch = top + cellHeight/sheetHeight;                    //uv texture height
    
    m_mask_rect = TOEvector4df(left, top, cw, ch);
}

void TFRect::SetMask(std::string mask_path){
    if(mask_path.compare("")!=0) m_mask = TResourceManager::GetInstance()->GetResourceTexture(mask_path);
}