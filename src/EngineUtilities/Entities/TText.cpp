#include "TText.h"
#include "../TOcularEngine/VideoDriver.h"
#include "./../TResourceManager.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

TText::TText(std::string text, float charSize, std::string texture){
	// Inicializamos los buffer
	m_vbo = 0;
	glGenBuffers(1, &m_vbo);

	m_uvbo = 0;
	glGenBuffers(1, &m_uvbo);

	m_size = 0;

	// Guardamos el tamanyo de las letras
	m_charSize = charSize;

	// Ponemos el texto del billboard
	m_text = "";
	ChangeText(text);

	// Ponemos la textura del texto
	if(texture.compare("")==0) texture = VideoDriver::GetInstance()->GetAssetsPath() + "/textures/DefaultFont.bmp";
	m_texture = TResourceManager::GetInstance()->GetResourceTexture(texture); 

	m_program = TEXT_SHADER;
}

TText::~TText(){}

void TText::BeginDraw(){
	// Bind and send the data to the VERTEX SHADER
	SendShaderData();
	glDrawArrays(GL_TRIANGLES, 0, m_size);
}

void TText::EndDraw(){}

void TText::ChangeSize(float charSize){
	if(m_charSize != charSize){
		m_charSize = charSize;
		LoadText(m_text);
	}
}

void TText::ChangeText(std::string text){
	if(text.compare(m_text) != 0){
		m_text = text;
		LoadText(text);
	}
}

void TText::SendShaderData(){
	// Ponemos en uso el shader del texto
		Program* myProgram = VideoDriver::GetInstance()->GetProgram(m_program);
		glUseProgram(myProgram->GetProgramID());

	// Enviamos la matriz MVP
		// Calculamos la matriz MVP

		// PRIMERO DE TODO QUITAMOS LA ROTACION DE LA MATRIZ DE LA PILA
		glm::mat4 m_matrix = m_stack.top();
		m_matrix[0] = glm::vec4(1, 0, 0, m_matrix[0][3]);
		m_matrix[1] = glm::vec4(0, 1, 0, m_matrix[1][3]);
		m_matrix[2] = glm::vec4(0, 0, 1, m_matrix[2][3]);

		// SEGUIDAMENTE COGEMOS LA ROTACION DE LA CAMARA Y LA INVERTIMOS
		// DE ESTA FORMA CONSEGUIMOS QUE SIEMPRE MIRE A LA CAMARA
		glm::mat3 m_view = ViewMatrix;
		m_view = glm::inverse(m_view);

		m_matrix[0] = glm::vec4(m_view[0][0], m_view[0][1], m_view[0][2], m_matrix[0][3]);
		m_matrix[1] = glm::vec4(m_view[1][0], m_view[1][1], m_view[1][2], m_matrix[1][3]);
		m_matrix[2] = glm::vec4(m_view[2][0], m_view[2][1], m_view[2][2], m_matrix[2][3]);

		glm::mat4 modelView = ViewMatrix * m_matrix;
		glm::mat4 mvpMatrix = ProjMatrix * modelView;

		// SEND THE MATRIX
		GLint mvpLocation = glGetUniformLocation(myProgram->GetProgramID(), "MVP");
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

	// Enviamos los vertices del texto
		// BIND VERTEX
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		// SEND THE VERTEX
		GLint posAttrib = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");
		glVertexAttribPointer(posAttrib,3, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
		glEnableVertexAttribArray(posAttrib);

	// Enviamos los uv del texto
		// BIND THE UV
		glBindBuffer(GL_ARRAY_BUFFER, m_uvbo);

		// SEND THE UV
		GLuint uvAttrib = glGetAttribLocation(myProgram->GetProgramID(), "TextureCoords");
		glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
		glEnableVertexAttribArray(uvAttrib);

	// Enviamos la textura del texto
		GLuint TextureID = glGetUniformLocation(myProgram->GetProgramID(), "myTextureSampler");
		glUniform1i(TextureID, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureId());

}

// PONEMOS EL TEXTO DE FORMA QUE ESTE CENTRADO EN EL 0,0
void TText::LoadText(std::string text){
	m_text = text;

	std::vector<glm::vec3> textVertex;
	std::vector<glm::vec2> textUv;

	int size = m_text.length();
	float SIZE = m_charSize;
	float x = -SIZE*size/2;	// Centramos el texto en X
	float y = -SIZE*size/2;	// Centramos el texto en Y
	for(int i=0; i<size; i++){
		// Sacamos los 4 puntos de la letra
		glm::vec3 vertexUpLeft 		= glm::vec3(x+i*SIZE 			, y+SIZE 	, 0);
		glm::vec3 vertexDownLeft 	= glm::vec3(x+i*SIZE 			, y+0 		, 0);
		glm::vec3 vertexUpRight 	= glm::vec3(x+i*SIZE + SIZE 	, y+SIZE 	, 0);
		glm::vec3 vertexDownRight 	= glm::vec3(x+i*SIZE + SIZE 	, y+0 		, 0);

		// Con los 4 puntos sacamos los 2 triangulos que deberian haber
		textVertex.push_back(vertexUpLeft    );
    	textVertex.push_back(vertexDownLeft  );
    	textVertex.push_back(vertexUpRight   );

    	textVertex.push_back(vertexDownRight );
    	textVertex.push_back(vertexUpRight	 );
    	textVertex.push_back(vertexDownLeft	 );

    	// Una vez ya tenemos los vertices calculamos los UV de la letra
    	// En nuestra imagen tenemos 16 columnas y filas, de ahi dividirlo entre 16
    	char character = text[i];
    	float uv_x = (character%16)/16.0f;
    	float uv_y = (character/16)/16.0f;

    	// Sacamos los UV de cada una de las cuatro esquinas
    	glm::vec2 uvUpLeft    	= glm::vec2(uv_x           	, uv_y 				 );
	    glm::vec2 uvDownLeft  	= glm::vec2(uv_x           	, (uv_y + 1.0f/16.0f) );
	    glm::vec2 uvUpRight   	= glm::vec2(uv_x+1.0f/16.0f	, uv_y 				 );
	    glm::vec2 uvDownRight 	= glm::vec2(uv_x+1.0f/16.0f	, (uv_y + 1.0f/16.0f) );

	    // Al igual que antes sacamos los uv de los 2 triangulos que deberian haber
	    textUv.push_back(uvUpLeft	 );
	    textUv.push_back(uvDownLeft  );
	    textUv.push_back(uvUpRight	 );

	    textUv.push_back(uvDownRight );
	    textUv.push_back(uvUpRight	 );
	    textUv.push_back(uvDownLeft	 );
	}

	m_size = textVertex.size();

	// Una vez ya almacenados todos los vertices y uv cargamos los vectores
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, textVertex.size()*sizeof(glm::vec3), &textVertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_uvbo);
	glBufferData(GL_ARRAY_BUFFER, textUv.size()*sizeof(glm::vec2), &textUv[0], GL_STATIC_DRAW);

}