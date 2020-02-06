#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SpannerModel.h"
using namespace std;




static GLfloat unit_spanner[] =
{
	0.375f, 0.0625f, 0.01f, 1.0f, 2.0f / 13.0f,	// A
	-0.1875f, 0.0625f, 0.01f, 4.0f / 13.0f, 2.0f / 13.0f,	// B
	-0.3125f, 0.1875f, 0.01f, 2.0f / 13.0f, 0.0f,	// C
	-0.4375f, 0.0625f * sqrt(3.0f), 0.01f, 0.0f, 3.0f / 13.0f - 0.0625*sqrt(3.0f),	// D
	-0.3125f, 0.0625f * sqrt(3.0f), 0.01f, 2.0f / 13.0f, 3.0f / 13.0f - 0.0625f*sqrt(3.0f),	// E

	-0.25f, 0.0f, 0.01f, 3.0f / 13.0f, 3.0f / 13.0f,	// F

	-0.3125f, -0.0625f * sqrt(3.0f), 0.01f, 2.0f / 13.0f, 3.0f / 13.0f + 0.0625f*sqrt(3.0f),	// G
	-0.4375f, -0.0625f * sqrt(3.0f), 0.01f, 0.0f, 3.0f / 13.0f + 0.0625*sqrt(3.0f),	// H
	-0.3125f, -0.1875f, 0.01f, 2.0f / 13.0f, 6.0f / 13.0f,	// I
	-0.1875f, -0.0625f, 0.01f, 4.0f / 13.0f, 4.0f / 13.0f,	// J
	0.375f, -0.0625f, 0.01f, 1.0f, 4.0f / 13.0f,	// K


	0.375f, 0.0625f, -0.01f, 1.0f, 2.0f / 13.0f,	// A'
	-0.1875f, 0.0625f, -0.01f, 4.0f / 13.0f, 2.0f / 13.0f,	// B'
	-0.3125f, 0.1875f, -0.01f, 2.0f / 13.0f, 0.0f,	// C'
	-0.4375f, 0.0625f * sqrt(3.0f), -0.01f, 0.0f, 3.0f / 13.0f - 0.0625*sqrt(3.0f),	// D'
	-0.3125f, 0.0625f * sqrt(3.0f), -0.01f, 2.0f / 13.0f, 3.0f / 13.0f - 0.0625f*sqrt(3.0f),	// E'

	-0.25f, 0.0f, -0.01f, 3.0f / 13.0f, 3.0f / 13.0f,	// F'

	- 0.3125f, -0.0625f * sqrt(3.0f), -0.01f, 2.0f / 13.0f, 3.0f / 13.0f + 0.0625f*sqrt(3.0f),	// G'
	-0.4375f, -0.0625f * sqrt(3.0f), -0.01f, 0.0f, 3.0f / 13.0f + 0.0625*sqrt(3.0f),	// H'
	-0.3125f, -0.1875f, -0.01f, 2.0f / 13.0f, 6.0f / 13.0f,	// I'
	-0.1875f, -0.0625f, -0.01f, 4.0f / 13.0f, 4.0f / 13.0f,	// J'
	0.375f, -0.0625f, -0.01f, 1.0f, 4.0f / 13.0f	// K'
};


static GLuint indices[] = {
	0, 1, 10,
	1, 9, 10,
	1, 5, 9,
	1, 5, 2,
	5, 9, 8,
	5, 4, 2,
	5, 6, 8,
	2, 3, 4,
	8, 7, 6,

	indices[0] + 11, indices[1] + 11, indices[2] + 11,
	indices[3] + 11, indices[4] + 11, indices[5] + 11,
	indices[6] + 11, indices[7] + 11, indices[8] + 11,
	indices[9] + 11, indices[10] + 11, indices[11] + 11,
	indices[12] + 11, indices[13] + 11, indices[14] + 11,
	indices[15] + 11, indices[16] + 11, indices[17] + 11,
	indices[18] + 11, indices[19] + 11, indices[20] + 11,
	indices[21] + 11, indices[22] + 11, indices[23] + 11,
	indices[24] + 11, indices[25] + 11, indices[26] + 11,

	0, 10, 11,
	10, 11, 21,
	0, 1, 12,
	0, 12, 11,
	1, 2, 13,
	1, 13, 12,
	2, 3, 14,
	2, 14, 13,
	3, 4, 15,
	3, 15, 14,
	4, 5, 16,
	4, 16, 15,
	5, 6, 17,
	5, 17, 16,
	6, 7, 18,
	6, 18, 17,
	7, 8, 19,
	7, 19, 18,
	8, 9, 20,
	8, 20, 19,
	9, 10, 21,
	9, 21, 20
};


SpannerModel::SpannerModel(GLfloat size)
{
	this->size = size;

	for (int i = 0; i < _countof(unit_spanner) / 5; ++i)
	{
		coords.push_back(unit_spanner[i * 5] * size);
		coords.push_back(unit_spanner[i * 5 + 1] * size);
		coords.push_back(unit_spanner[i * 5 + 2] * size * 2);
		coords.push_back(unit_spanner[i * 5 + 3]);
		coords.push_back(unit_spanner[i * 5 + 4]);
	}

	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * coords.size(), &(coords[0]), GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void SpannerModel::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);

	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	glDrawElements(GL_TRIANGLES, _countof(indices), GL_UNSIGNED_INT, 0);

	// all is drawn - unbind vertex array
	glBindVertexArray(0);
}

SpannerModel::~SpannerModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

float SpannerModel::getRotPoint()
{
	return size*3.0f/8.0f;
}