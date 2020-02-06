#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CubeModel.h"
using namespace std;

float one3 = 1.0f / 3.0f;
float two3 = 2.0f / 3.0f;

static GLfloat unit_cube[] = {
	// FRONT
	-0.5f,	-0.5f,	-0.5f,  0.25f,	two3,	// D
	0.5f,	-0.5f,	-0.5f,  0.5f,	two3,	// C
	0.5f,	0.5f,	-0.5f,  0.5f,	one3,	// B
	0.5f,	0.5f,	-0.5f,  0.5f,	one3,	// B
	-0.5f,  0.5f,	-0.5f,  0.25f,	one3,	// A
	-0.5f, -0.5f,	-0.5f,	0.25f,	two3,	// D
	// BACK
	-0.5f, -0.5f,  0.5f,  1.0f,	two3,	// H
	0.5f, -0.5f,  0.5f,  0.75f, two3,	// G
	0.5f,  0.5f,  0.5f,  0.75f, one3,	// F
	0.5f,  0.5f,  0.5f,  0.75f, one3,	// F
	-0.5f,  0.5f,  0.5f, 1.0f, one3,	// E
	-0.5f, -0.5f,  0.5f,  1.0f,	two3,	// H
	// LEFT
	-0.5f,  0.5f,  0.5f,  0.0f, one3,	// E
	-0.5f,  0.5f, -0.5f,   0.25f, one3,	// A
	-0.5f, -0.5f, -0.5f, 0.25f, two3,	// D
	-0.5f, -0.5f, -0.5f, 0.25f, two3,	// D
	-0.5f, -0.5f,  0.5f,  0.0f, two3,	// H
	-0.5f,  0.5f,  0.5f,  0.0f, one3,	// E
	// RIGHT
	0.5f,  0.5f,  0.5f,  0.75f, one3,	// F
	0.5f,  0.5f, -0.5f,  0.5f, one3,	// B
	0.5f, -0.5f, -0.5f, 0.5f, two3,	// C
	0.5f, -0.5f, -0.5f, 0.5f, two3,	// C
	0.5f, -0.5f,  0.5f, 0.75f, two3,	// G
	0.5f,  0.5f,  0.5f,  0.75f, one3,	// F
	// DOWN
	-0.5f, -0.5f, -0.5f, 0.25f, two3,	// D
	0.5f, -0.5f, -0.5f, 0.5f, two3,	// C
	0.5f, -0.5f,  0.5f,  0.5f, 1.0f,	// G
	0.5f, -0.5f,  0.5f,  0.5f, 1.0f,	// G
	-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,	// H
	-0.5f, -0.5f, -0.5f, 0.25f, two3,	// D
	// UP
	-0.5f,  0.5f, -0.5f,   0.25f, one3,	// A
	0.5f,  0.5f, -0.5f,  0.5f, one3,	// B
	0.5f,  0.5f,  0.5f,  0.5f, 0.0f,	// F
	0.5f,  0.5f,  0.5f,  0.5f, 0.0f,	// F
	-0.5f,  0.5f,  0.5f,  0.25f, 0.0f,	// E
	-0.5f,  0.5f, -0.5f,  0.25f, one3	// A
};

CubeModel::CubeModel(GLfloat size)
{
	for (int i = 0; i < _countof(unit_cube) / 5; ++i)
	{
		cube_coord.push_back(unit_cube[i * 5] * size);
		cube_coord.push_back(unit_cube[i * 5 + 1] * size);
		cube_coord.push_back(unit_cube[i * 5 + 2] * size);
		cube_coord.push_back(unit_cube[i * 5 + 3]);
		cube_coord.push_back(unit_cube[i * 5 + 4]);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * cube_coord.size(), &(cube_coord[0]), GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
}

void CubeModel::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{

	
	glBindVertexArray(VAO);

	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint) cube_coord.size());

	// all is drawn - unbind vertex array
	glBindVertexArray(0);
	
}

CubeModel::~CubeModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
