#include "TF2DText.h"
#include <GL/glew.h>
#include <TOEvector3d.h>

#include "./../../VideoDriver.h"
#include "./../../../EngineUtilities/TResourceManager.h"
#include "./../../../EngineUtilities/Resources/Program.h"

TF2DText::TF2DText(std::string text , TOEvector2df position){
    m_text = text;
    m_textSize = 0.1f;

    TOEvector2di w_dims = VideoDriver::GetInstance()->GetWindowDimensions();
    m_position  = TOEvector2df((position.X*2 - w_dims.X) / w_dims.X , (position.Y*2 - w_dims.Y) / w_dims.Y);

    m_program = TWODTEXT_SHADER;

    m_VBO = 0;
    glGenBuffers(1, &m_VBO);

    m_UVBO = 0;
    glGenBuffers(1, &m_UVBO);

    // Textura del texto
	std::string tex_path = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_font.png";
	m_texture = TResourceManager::GetInstance()->GetResourceTexture(tex_path);

    SetText(m_text);

	m_InData.position = position;
}

TF2DText::~TF2DText(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);   
    glDeleteBuffers(1, &m_VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);   
    glDeleteBuffers(1, &m_UVBO);
}

void TF2DText::Draw() const {
    Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(m_program);

    //posicion
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);
	
    //textura coords
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBO);

    GLuint uvAttrib = glGetAttribLocation(myProgram->GetProgramID(), "TextureCoords");
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
    glEnableVertexAttribArray(uvAttrib);
    
    // Enviamos la textura del sprite
	GLuint TextureID = glGetUniformLocation(myProgram->GetProgramID(), "uvMap");
	glUniform1i(TextureID, 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureId());

    glDrawArrays(GL_TRIANGLES, 0, m_vertexSize);

}

void TF2DText::Erase(){

}

void TF2DText::SetText(std::string txt){
    // PONEMOS EL TEXTO DE FORMA QUE ESTE CENTRADO EN EL 0,0
	m_text = txt;

	std::vector<glm::vec2>  textVertex;
	std::vector<glm::vec2>  textUv;

	int size = m_text.length();
	float SIZE = m_textSize;
	//float x = -SIZE*size/2;	// Centramos el texto en X
	//float y = -SIZE;	        // Centramos el texto en Y
    float x = m_position.X;
    float y = m_position.Y;

	for(int i=0; i<size; i++){
		// Sacamos los 4 puntos de la letra
		float X1 = x+i*SIZE;
		float X2 = x+i*SIZE + SIZE;
		float Y1 = y+SIZE;
		float Y2 = y+0;

		glm::vec2 vertexUpLeft 		= glm::vec2(X1 	, Y1 );
		glm::vec2 vertexDownLeft 	= glm::vec2(X1 	, Y2 );
		glm::vec2 vertexUpRight 	= glm::vec2(X2 	, Y1 );
		glm::vec2 vertexDownRight 	= glm::vec2(X2 	, Y2 );

		// Con los 4 puntos sacamos los 2 triangulos que deberian haber
		textVertex.push_back(vertexUpLeft    );
    	textVertex.push_back(vertexUpRight   );
    	textVertex.push_back(vertexDownLeft  );

    	textVertex.push_back(vertexDownRight );
    	textVertex.push_back(vertexDownLeft	 );
    	textVertex.push_back(vertexUpRight	 );

    	// Una vez ya tenemos los vertices calculamos los UV de la letra
    	// En nuestra imagen tenemos 16 columnas y filas, de ahi dividirlo entre 16
    	char character = txt[i];
		//std::cout<<"character "<<i<<":\t"<<character<<"\n";
		float reason = 1.0f/16.0f;

		float UV_X1 = (character%16)/16.0f;
		float UV_X2 = (character%16)/16.0f + reason;
		float UV_Y1 = (character/16)/16.0f;
		float UV_Y2 = (character/16)/16.0f + reason;

    	// Sacamos los UV de cada una de las cuatro esquinas
    	glm::vec2 uvUpLeft    	= glm::vec2(UV_X1   , UV_Y1	);
	    glm::vec2 uvDownLeft  	= glm::vec2(UV_X1   , UV_Y2	);
	    glm::vec2 uvUpRight   	= glm::vec2(UV_X2	, UV_Y1	);
	    glm::vec2 uvDownRight 	= glm::vec2(UV_X2	, UV_Y2 );

	    // Al igual que antes sacamos los uv de los 2 triangulos que deberian haber
	    textUv.push_back(uvUpLeft	 );
	    textUv.push_back(uvUpRight	 );
	    textUv.push_back(uvDownLeft  );

	    textUv.push_back(uvDownRight );
	    textUv.push_back(uvDownLeft	 );
	    textUv.push_back(uvUpRight	 );

	}

	m_vertexSize = textVertex.size();

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, textVertex.size()*sizeof(glm::vec2), &textVertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_UVBO);
	glBufferData(GL_ARRAY_BUFFER, textUv.size()*sizeof(glm::vec2), &textUv[0], GL_STATIC_DRAW);

}

void TF2DText::SetTextSize(float siz){
	m_textSize = siz;
}

std::string TF2DText::GetText(){
	return m_text;
}

float TF2DText::GetTextSize(){
	return m_textSize;
}

void TF2DText::SetPosition(float x, float y){
	TOEvector2di w_dims = VideoDriver::GetInstance()->GetWindowDimensions();
	m_position = TOEvector2df((x*2 - w_dims.X) / w_dims.X , (y*2 - w_dims.Y) / w_dims.Y);
    m_InData.position.X = x;
    m_InData.position.Y = y;
	SetText(m_text);
}