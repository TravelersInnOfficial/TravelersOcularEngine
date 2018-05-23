#include "./TPortal.h"
#include "./TRoom.h"
#include "./Entities/TEntity.h"
#include "./../TOcularEngine/VideoDriver.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GL/glew.h>
#include <limits>

int TPortal::Sign(int v){
	if(v>=0) return 1;
	else return -1;
}

TPortal::TPortal(TRoom* first, TRoom* second, glm::vec3 size, glm::vec3 center, glm::vec3 rotation){
	// Nos guardamos las variables pasadas por parametros
	m_firstConnection = first;
	m_secondConnection = second;
	m_size = size;
	m_center = center;
	m_rotation = rotation;

	// Inicializamos la matriz de transformacion
	m_transform = glm::mat4(1.0f);

	// Ponemos la visibilidad a true
	m_visible = true;

	// Calculamos la transformacion con los valores recibidos por parametros
	CalculateTransform();

	// Prepara los limits del clipping del portal
	PrepareLimits();
}

TPortal::~TPortal(){}

void TPortal::CalculateTransform(){
	// 3º Aplicamos la translacion a la transformacion identidad que hay cargada
	m_transform = glm::translate(m_transform, glm::vec3(m_center.x, m_center.y, m_center.z));

	// 2º Aplicamos la rotacion a la matriz actual
	glm::quat axisX = glm::angleAxis(glm::radians(m_rotation.x), glm::vec3(1,0,0));
	glm::quat axisY = glm::angleAxis(glm::radians(m_rotation.y), glm::vec3(0,1,0));
	glm::quat axisZ = glm::angleAxis(glm::radians(m_rotation.z), glm::vec3(0,0,1));

	glm::quat crossed = glm::cross(axisZ, axisY);

 	glm::mat4 final1 = glm::toMat4(crossed);
 	glm::mat4 final2 = glm::toMat4(axisX);

 	m_transform =  m_transform * final1 * final2;

 	// 1º Para finalizar aplicamos el escalado
	m_transform = glm::scale(m_transform, glm::vec3(m_size.x, m_size.y, m_size.z));
}

bool TPortal::CheckVisibility(){
	bool output = true;

	// En el caso de que ya se haya pintado la segunda habitacion o que no sea visible no hacemos la comprobacion
	if(m_secondConnection->GetDrawed() || !m_visible){	
		output = false;
	}else{	
		PrepareLimits();

		// NOTA: Se supone que el m_stack.top() debe estar como identidad, sin aplicar ninguna transformacion
		// Calculamos la matriz MVP del portal
		glm::mat4 mvp = TEntity::ProjMatrix * TEntity::ViewMatrix * TEntity::m_stack.top() * m_transform;

		int upDown, leftRight, nearFar;
		upDown = leftRight = nearFar = 0;

		for(int i= -1; i<=0; i++){
			// +X -X
			for(int j= -1; j<=0; j++){
				// +Y -Y
				for(int k= -1; k<=0; k++){
					// +Z -Z

					// Probamos la visibilidad en los 8 puntos que forma el cubo del portal
					glm::vec3 point = glm::vec3(0.5f*Sign(i), 0.5f*Sign(j), 0.5f*Sign(k));
					glm::vec4 mvpPoint = mvp * glm::vec4(point.x, point.y, point.z, 1.0f);

					CheckVisibility(mvpPoint, &upDown, &leftRight, &nearFar);
				}
			}
		}

		// Comprobacion visibilidad, en el caso de que algun valor valga 8 o -8 es que el portal no esta en la pantalla
		int sides = 8;
		if(upDown == sides || upDown == -sides || leftRight == sides || leftRight == -sides || nearFar == sides || nearFar == -sides){
			output = false;
		}
	}

	if(output){
		// En el caso de que haya pasado la prueba del clipping actualizamos los valores del clipping
		ChangeEntityClipping();
	}

	return output;
}

void TPortal::ChangeEntityClipping(){
	// Actualizamos las variables de los limites del clipping de las entidades con los limites del portal
	// Solamente se actualizan si el rectangulo formante por los limites es menos que el actual
	if(m_limits[0] < TEntity::m_clippingLimits[0] && m_limits[0] > TEntity::m_clippingLimits[1]) TEntity::m_clippingLimits[0] = m_limits[0];
	if(m_limits[1] < TEntity::m_clippingLimits[0] && m_limits[1] > TEntity::m_clippingLimits[1]) TEntity::m_clippingLimits[1] = m_limits[1];
	if(m_limits[2] < TEntity::m_clippingLimits[2] && m_limits[2] > TEntity::m_clippingLimits[3]) TEntity::m_clippingLimits[2] = m_limits[2];
	if(m_limits[3] < TEntity::m_clippingLimits[2] && m_limits[3] > TEntity::m_clippingLimits[3]) TEntity::m_clippingLimits[3] = m_limits[3];
}

void TPortal::CheckVisibility(glm::vec4 point, int* upDown, int* leftRight, int* nearFar){
    float valueX = point.x / abs(point.w);
   	float valueY = point.y / abs(point.w);
   	float valueZ = point.z / abs(point.w);

   	// Calculamos a ver si se ve el punto 
   	if(valueX > TEntity::m_clippingLimits[0]) (*leftRight)++;
    else if(valueX < TEntity::m_clippingLimits[1]) (*leftRight)--;

    if(valueY > TEntity::m_clippingLimits[2]) (*upDown)++;
    else if(valueY < TEntity::m_clippingLimits[3]) (*upDown)--;

    if(valueZ > 1) (*nearFar)++;
    else if(valueZ < 0) (*nearFar)--;

    // Actualizamos los limites del 
    // En el caso de salir por el near resetamos los valores del clipping del portal
    // puesto que al salirse por el near los valores que nos dan los demás limites no nos valen
    if(valueZ < 0){
    	m_limits[0] = +1.0f;
    	m_limits[1] = -1.0f;
    	m_limits[2] = +1.0f;
    	m_limits[3] = -1.0f;
    }

    // Actualizamos los limites del portal
    if(valueX > m_limits[0]) m_limits[0] = valueX; 
    if(valueX < m_limits[1]) m_limits[1] = valueX;
		
	if(valueY > m_limits[2]) m_limits[2] = valueY;
    if(valueY < m_limits[3]) m_limits[3] = valueY;
    
}


void TPortal::SetSize(glm::vec3 size){
	m_size = size;
	CalculateTransform();
}

void TPortal::SetCenter(glm::vec3 center){
	m_center = center;
	CalculateTransform();
}

void TPortal::SetRotation(glm::vec3 rot){
	m_rotation = rot;
	CalculateTransform();
}

void TPortal::DrawDebug(){
	Program* myProgram = VideoDriver::GetInstance()->SetShaderProgram(BB_SHADER);

	// Cube 1x1x1, centered on origin
	GLfloat vertices[] = {
		-0.5, -0.5, -0.5, 1.0,
		0.5, -0.5, -0.5, 1.0,
		0.5,  0.5, -0.5, 1.0,
		-0.5,  0.5, -0.5, 1.0,
		-0.5, -0.5,  0.5, 1.0,
		0.5, -0.5,  0.5, 1.0,
		0.5,  0.5,  0.5, 1.0,
		-0.5,  0.5,  0.5, 1.0,
	};

	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort elements[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 4, 1, 5, 2, 6, 3, 7
	};
	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	// Apply object's transformation matrix 
	glm::mat4 m = TEntity::ProjMatrix * TEntity::ViewMatrix * TEntity::m_stack.top() * m_transform;
	GLuint uniform_m = glGetUniformLocation(myProgram->GetProgramID(), "MVP");
	glUniformMatrix4fv(uniform_m, 1, GL_FALSE, &m[0][0]);

	// Send light color
	GLuint linecolor = glGetUniformLocation(myProgram->GetProgramID(), "LineColor");
	glUniform3fv(linecolor, 1, glm::value_ptr(glm::vec3(0.0f, 1.0f, 0.0f)));

	// Send each vertex data
	GLuint attribute_v_coord = glGetAttribLocation(myProgram->GetProgramID(), "VertexPosition");	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glEnableVertexAttribArray(attribute_v_coord);

	glVertexAttribPointer(
		attribute_v_coord,  // attribute
		4,                  // number of elements per vertex, here (x,y,z,w)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4*sizeof(GLushort)));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8*sizeof(GLushort)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(attribute_v_coord);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &ibo_elements);
}

void TPortal::PrepareLimits(){
	// Si quiero tener el maximo valor debo empezar por el minimo 
	// Si quiero tener el minimo valor debo empezar por el maximo		
	m_limits[0] = -1.0f;
	m_limits[1] = +1.0f;
	m_limits[2] = -1.0f;
	m_limits[3] = +1.0f;
}

void TPortal::SetVisible(bool visible){
	m_visible = visible;
}

void TPortal::DrawSecondRoom(){
	m_secondConnection->Draw();
}

bool TPortal::GetVisible(){
	return m_visible;
}
