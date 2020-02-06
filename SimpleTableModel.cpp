#define GLEW_STATIC

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SimpleTableModel.h"



namespace takethatlinker
{
	float one3 = 1.0f; // 3.0f;
	float two3 = 2.0f; // 3.0f;

	static GLfloat unit_table[] = {
		// FRONT
		-0.5f, -0.5f, -0.5f / 3.0f / 4.0f, 0.0f, 1.0f,	// D
		0.5f, -0.5f, -0.5f / 3.0f / 4.0f, 1.0f, 1.0f,	// C
		0.5f, 0.5f, -0.5f / 3.0f / 4.0f, 1.0f, 0.0f,	// B
		0.5f, 0.5f, -0.5f / 3.0f / 4.0f, 1.0f, 0.0f,	// B
		-0.5f, 0.5f, -0.5f / 3.0f / 4.0f, 0.0f, 0.0f,	// A
		-0.5f, -0.5f, -0.5f / 3.0f / 4.0f, 0.0f, 1.0f,	// D
		// BACK
		-0.5f, -0.5f, 0.5f / 3.0f / 4.0f, 1.0f, 0.0f,	// H
		0.5f, -0.5f, 0.5f / 3.0f / 4.0f, 0.0f, 0.0f,	// G
		0.5f, 0.5f, 0.5f / 3.0f / 4.0f, 0.0f, 1.0f,		// F
		0.5f, 0.5f, 0.5f / 3.0f / 4.0f, 0.0f, 1.0f,		// F
		-0.5f, 0.5f, 0.5f / 3.0f / 4.0f, 1.0f, 1.0f,	// E
		-0.5f, -0.5f, 0.5f / 3.0f / 4.0f, 1.0f, 0.0f,	// H
		// LEFT
		-0.5f, 0.5f, 0.5f / 3.0f / 4.0f, 0.0f, one3,	// E
		-0.5f, 0.5f, -0.5f / 3.0f / 4.0f, 0.25f, one3,	// A
		-0.5f, -0.5f, -0.5f / 3.0f / 4.0f, 0.25f, two3,	// D
		-0.5f, -0.5f, -0.5f / 3.0f / 4.0f, 0.25f, two3,	// D
		-0.5f, -0.5f, 0.5f / 3.0f / 4.0f, 0.0f, two3,	// H
		-0.5f, 0.5f, 0.5f / 3.0f / 4.0f, 0.0f, one3,	// E
		// RIGHT
		0.5f, 0.5f, 0.5f / 3.0f / 4.0f, 0.75f, one3,	// F
		0.5f, 0.5f, -0.5f / 3.0f / 4.0f, 0.5f, one3,	// B
		0.5f, -0.5f, -0.5f / 3.0f / 4.0f, 0.5f, two3,	// C
		0.5f, -0.5f, -0.5f / 3.0f / 4.0f, 0.5f, two3,	// C
		0.5f, -0.5f, 0.5f / 3.0f / 4.0f, 0.75f, two3,	// G
		0.5f, 0.5f, 0.5f / 3.0f / 4.0f, 0.75f, one3,	// F
		// DOWN
		-0.5f, -0.5f, -0.5f / 3.0f / 4.0f, 0.25f, two3,	// D
		0.5f, -0.5f, -0.5f / 3.0f / 4.0f, 0.5f, two3,	// C
		0.5f, -0.5f, 0.5f / 3.0f / 4.0f, 0.5f, 1.0f,	// G
		0.5f, -0.5f, 0.5f / 3.0f / 4.0f, 0.5f, 1.0f,	// G
		-0.5f, -0.5f, 0.5f / 3.0f / 4.0f, 0.25f, 1.0f,	// H
		-0.5f, -0.5f, -0.5f / 3.0f / 4.0f, 0.25f, two3,	// D
		// UP
		-0.5f, 0.5f, -0.5f / 3.0f / 4.0f, 0.25f, one3,	// A
		0.5f, 0.5f, -0.5f / 3.0f / 4.0f, 0.5f, one3,	// B
		0.5f, 0.5f, 0.5f / 3.0f / 4.0f, 0.5f, 0.0f,	// F
		0.5f, 0.5f, 0.5f / 3.0f / 4.0f, 0.5f, 0.0f,	// F
		-0.5f, 0.5f, 0.5f / 3.0f / 4.0f, 0.25f, 0.0f,	// E
		-0.5f, 0.5f, -0.5f / 3.0f / 4.0f, 0.25f, one3	// A
	};

}

using namespace takethatlinker;

SimpleTableModel::SimpleTableModel(GLfloat size, GLfloat density)
{
	for (int i = 0; i < _countof(unit_table) / 5; ++i)
	{
		coords.push_back(unit_table[i * 5] * size);
		coords.push_back(unit_table[i * 5 + 1] * size);
		coords.push_back(unit_table[i * 5 + 2] * size);
		coords.push_back(unit_table[i * 5 + 3] * density);
		coords.push_back(unit_table[i * 5 + 4] * density);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * coords.size(), &(coords[0]), GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SimpleTableModel::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{


	glBindVertexArray(VAO);

	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)coords.size());

	// all is drawn - unbind vertex array
	glBindVertexArray(0);

}

SimpleTableModel::~SimpleTableModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
