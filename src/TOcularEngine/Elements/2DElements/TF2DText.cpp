#include "TF2DText.h"
#include <GL/glew.h>
#include <TOEvector3d.h>

#include "./../../VideoDriver.h"
#include "./../../../EngineUtilities/TResourceManager.h"
#include "./../../../EngineUtilities/Resources/Program.h"

TF2DText::TF2DText(std::string text , TOEvector2df position){
    m_text = text;
    m_textSize = 0.06f;

    TOEvector2di w_dims = VideoDriver::GetInstance()->GetWindowDimensions();
	//Calculate the position in OpenGL units
    m_position  = TOEvector2df((position.X*2 - w_dims.X) / w_dims.X , (position.Y*2 - w_dims.Y) / w_dims.Y);

    m_program = TWODTEXT_SHADER;

	//Bind the vertex and uv buffers
    m_VBO = 0;
    glGenBuffers(1, &m_VBO);

    m_UVBO = 0;
    glGenBuffers(1, &m_UVBO);

    //Font texture path
	std::string tex_path = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/default_font.png";
	m_texture = TResourceManager::GetInstance()->GetResourceTexture(tex_path);

	//Load the text texture rectangles for each letter
    SetText(m_text);

	//Size in OpenGL units
	float w = m_textSize * (m_vertexSize/6);
	float h = m_textSize;

	//Calculate the size in pixels
	float sizeX = w * w_dims.X / 2;
	float sizeY = h * w_dims.Y / 2;

	//Save the data in pixel units
	m_InData.position = position;
	m_InData.size = TOEvector2df(sizeX,sizeY);
}

TF2DText::~TF2DText(){
	//Unbind the buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);   
    glDeleteBuffers(1, &m_VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);   
    glDeleteBuffers(1, &m_UVBO);
}

void TF2DText::Draw() const {

	//Enable the OpenGL blend mode for transparencies
	glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Get the shader program
    Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(m_program);

    //Send the text position
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);
	
    //Send the texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBO);

    GLuint uvAttrib = glGetAttribLocation(myProgram->GetProgramID(), "TextureCoords");
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
    glEnableVertexAttribArray(uvAttrib);
    
    //Send the texture data
	GLuint TextureID = glGetUniformLocation(myProgram->GetProgramID(), "uvMap");
	glUniform1i(TextureID, 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureId());

	//Draw the object
    glDrawArrays(GL_TRIANGLES, 0, m_vertexSize);
	
	//Disable blend mode
	glDisable(GL_BLEND);
}

void TF2DText::SetText(std::string txt){
	m_text = txt;

	std::vector<glm::vec2>  textVertex;
	std::vector<glm::vec2>  textUv;

	int size = m_text.length();
	float SIZE = m_textSize;
    float x = m_position.X;
    float y = m_position.Y;

	for(int i=0; i<size; i++){
		//Calculate the 4 texture rect corners
		float X1 = x+i*SIZE;
		float X2 = x+i*SIZE + SIZE;
		float Y1 = y+SIZE;
		float Y2 = y+0;

		glm::vec2 vertexUpLeft 		= glm::vec2(X1 	, Y1 );
		glm::vec2 vertexDownLeft 	= glm::vec2(X1 	, Y2 );
		glm::vec2 vertexUpRight 	= glm::vec2(X2 	, Y1 );
		glm::vec2 vertexDownRight 	= glm::vec2(X2 	, Y2 );

		//Calculate the 2 triangles with the 4 corners obtained, in clockwise order for OpenGL to read
		textVertex.push_back(vertexUpLeft    );
    	textVertex.push_back(vertexUpRight   );
    	textVertex.push_back(vertexDownLeft  );

    	textVertex.push_back(vertexDownRight );
    	textVertex.push_back(vertexDownLeft	 );
    	textVertex.push_back(vertexUpRight	 );

    	//Once we got the vertices, calculate the UV 
		//We got 16 rows and columns, so we have to split between 16
    	char character = txt[i];
		float reason = 1.0f/16.0f;

		float UV_X1 = (character%16)/16.0f;
		float UV_X2 = (character%16)/16.0f + reason;
		float UV_Y1 = (character/16)/16.0f;
		float UV_Y2 = (character/16)/16.0f + reason;

    	//UV corners
    	glm::vec2 uvUpLeft    	= glm::vec2(UV_X1   , UV_Y1	);
	    glm::vec2 uvDownLeft  	= glm::vec2(UV_X1   , UV_Y2	);
	    glm::vec2 uvUpRight   	= glm::vec2(UV_X2	, UV_Y1	);
	    glm::vec2 uvDownRight 	= glm::vec2(UV_X2	, UV_Y2 );

	    //UV triangles
	    textUv.push_back(uvUpLeft	 );
	    textUv.push_back(uvUpRight	 );
	    textUv.push_back(uvDownLeft  );

	    textUv.push_back(uvDownRight );
	    textUv.push_back(uvDownLeft	 );
	    textUv.push_back(uvUpRight	 );

	}

	m_vertexSize = textVertex.size();

	//Send the buffer data
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, textVertex.size()*sizeof(glm::vec2), &textVertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_UVBO);
	glBufferData(GL_ARRAY_BUFFER, textUv.size()*sizeof(glm::vec2), &textUv[0], GL_STATIC_DRAW);
	
	//Store the positions and dimensions of the text
	TOEvector2di w_dims = VideoDriver::GetInstance()->GetWindowDimensions();
	float w = m_textSize * (m_vertexSize/6);
	float h = m_textSize;
	float sizeX = w * w_dims.X / 2;
	float sizeY = h * w_dims.Y / 2;
	m_InData.size = TOEvector2df(sizeX,sizeY);

}

void TF2DText::SetTextSize(float siz){
	m_textSize = siz;
	SetText(m_text);
}

std::string TF2DText::GetText(){
	return m_text;
}

float TF2DText::GetTextSize(){
	return m_textSize;
}

void TF2DText::SetTextureFont(std::string path){
	m_texture = TResourceManager::GetInstance()->GetResourceTexture(path);
}

void TF2DText::SetPosition(float x, float y){
	TOEvector2di w_dims = VideoDriver::GetInstance()->GetWindowDimensions();
	m_position = TOEvector2df((x*2 - w_dims.X) / w_dims.X , (y*2 - w_dims.Y) / w_dims.Y); //OpenGL units
    m_InData.position.X = x; //Pixel units 
    m_InData.position.Y = y; //Pixel units
	SetText(m_text);		 //Change the text buffer data
}