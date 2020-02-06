#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "HexagonalPrismModel.h"
using namespace std;

const float head = 0.5f / 3.0f;
const float thre = sqrt(3.0f) / 4.0f;

static GLfloat unit_prism[] = 
{
	/*X*/	/*Y*/	/*Z*/
	0.5f,	0.0f,	head,	// 0	- A'
	0.25f,	thre,	head,	// 1	- B'
	-0.25f,	thre,	head,	// 2	- C'
	-0.5f,	0.0f,	head,	// 3	- D'
	-0.25f,	-thre,	head,	// 4	- E'
	0.25f,	-thre,	head,	// 5	- F'
	0.0f,	0.0f,	head,	// 6	- centre'


	0.5f,	0.0f,	-head,	// 7	- A''
	0.25f,	thre,	-head,	// 8	- B''
	-0.25f,	thre,	-head,	// 9	- C''
	-0.5f,	0.0f,	-head,	// 10	- D''
	-0.25f,	-thre,	-head,	// 11	- E''
	0.25f,	-thre,	-head,	// 12	- F''
	0.0f,	0.0f,	-head,	// 13	- centre''
};

static GLfloat unit_prism_generator[] = 
{
	/*X*/	/*Y*/	/*Z*/
	0.5f,	0.0f,	head,	// 0	- A'
	0.25f,	thre,	head,	// 1	- B'
};

static GLuint indices[] =
{
	0, 1, 2
};

void generateVertices()
{

};

static GLfloat unit_prism_p[] = 
{
	/*X*/	/*Y*/	/*Z*/
	0.5f,	0.0f,	head,	1.0f,	0.5f,	// A'
	0.25f,	thre,	head,	0.75f,	0.5f-thre,	// B'
	0.0f,	0.0f,	head,	0.5f,	0.5f,	// centre'

	0.25f,	thre,	head,	0.75f,	0.5f-thre,	// B'
	-0.25f,	thre,	head,	0.25f,	0.5f-thre,	// C'
	0.0f,	0.0f,	head,	0.5f,	0.5f,	// centre'

	-0.25f,	thre,	head,	0.25f,	0.5f-thre,	// C'
	-0.5f,	0.0f,	head,	0.0f,	0.5f,	// D'
	0.0f,	0.0f,	head,	0.5f,	0.5f,	// centre'

	-0.5f,	0.0f,	head,	0.0f,	0.5f,	// D'
	-0.25f,	-thre,	head,	0.25f,	0.5f+thre,	// E'
	0.0f,	0.0f,	head,	0.5f,	0.5f,	// centre'

	-0.25f, -thre,	head,	0.25f,	0.5f+thre,	// E'
	0.25f,	-thre,	head,	0.75f,	0.5f+thre,	// F'
	0.0f,	0.0f,	head,	0.5f,	0.5f,	// centre'

	0.25f,	-thre,	head,	0.75f,	0.5f+thre,	// F'
	0.5f,	0.0f,	head,	1.0f,	0.5f,	// A'
	0.0f,	0.0f,	head,	0.5f,	0.5f,	// centre'


	0.5f,	0.0f,	-head,	1.0f,	0.5f,	// A''
	0.25f,	thre,	-head,	0.75f,	0.5f-thre,	// B''
	0.0f,	0.0f,	-head,	0.5f,	0.5f,	// centre''

	0.25f,	thre,	-head,	0.75f,	0.5f-thre,	// B''
	-0.25f,	thre,	-head,	0.25f,	0.5f-thre,	// C''
	0.0f,	0.0f,	-head,	0.5f,	0.5f,	// centre''

	-0.25f,	thre,	-head,	0.25f,	0.5f-thre,	// C''
	-0.5f,	0.0f,	-head,	0.0f,	0.5f,	// D''
	0.0f,	0.0f,	-head,	0.5f,	0.5f,	// centre''

	-0.5f,	0.0f,	-head,	0.0f,	0.5f,	// D''
	-0.25f,	-thre,	-head,	0.25f,	0.5f+thre,	// E''
	0.0f,	0.0f,	-head,	0.5f,	0.5f,	// centre''

	-0.25f, -thre,	-head,	0.25f,	0.5f+thre,	// E''
	0.25f,	-thre,	-head,	0.75f,	0.5f+thre,	// F''
	0.0f,	0.0f,	-head,	0.5f,	0.5f,	// centre''

	0.25f,	-thre,	-head,	0.75f,	0.5f+thre,	// F''
	0.5f,	0.0f,	-head,	1.0f,	0.5f,	// A''
	0.0f,	0.0f,	-head,	0.5f,	0.5f,	// centre''


	0.5f,	0.0f,	head,	1.0f,	0.5f,	// A'
	0.25f,	thre,	head,	0.75f,	0.5f-thre,	// B'
	0.25f,	thre,	-head,	0.75f,	0.5f-thre,	// B''

	0.5f,	0.0f,	head,	1.0f,	0.5f,	// A'
	0.5f,	0.0f,	-head,	1.0f,	0.5f,	// A''
	0.25f,	thre,	-head,	0.75f,	0.5f-thre,	// B''

	0.25f,	thre,	head,	0.75f,	0.5f-thre,	// B'
	-0.25f,	thre,	head,	0.25f,	0.5f-thre,	// C'
	-0.25f,	thre,	-head,	0.25f,	0.5f-thre,	// C''

	0.25f,	thre,	head,	0.75f,	0.5f-thre,	// B'
	0.25f,	thre,	-head,	0.75f,	0.5f-thre,	// B''
	-0.25f,	thre,	-head,	0.25f,	0.5f-thre,	// C''

	-0.25f,	thre,	head,	0.25f,	0.5f-thre,	// C'
	-0.5f,	0.0f,	head,	0.0f,	0.5f,	// D'
	-0.5f,	0.0f,	-head,	0.0f,	0.5f,	// D''

	-0.25f,	thre,	head,	0.25f,	0.5f-thre,	// C'
	-0.25f,	thre,	-head,	0.25f,	0.5f-thre,	// C''
	-0.5f,	0.0f,	-head,	0.0f,	0.5f,	// D''

	-0.5f,	0.0f,	head,	0.0f,	0.5f,	// D'
	-0.25f,	-thre,	head,	0.25f,	0.5f+thre,	// E'
	-0.25f,	-thre,	-head,	0.25f,	0.5f+thre,	// E''

	-0.5f,	0.0f,	head,	0.0f,	0.5f,	// D'
	-0.5f,	0.0f,	-head,	0.0f,	0.5f,	// D''
	-0.25f,	-thre,	-head,	0.25f,	0.5f+thre,	// E''

	-0.25f, -thre,	head,	0.25f,	0.5f+thre,	// E'
	0.25f,	-thre,	head,	0.75f,	0.5f+thre,	// F'
	0.25f,	-thre,	-head,	0.75f,	0.5f+thre,	// F''

	-0.25f, -thre,	head,	0.25f,	0.5f+thre,	// E'
	-0.25f, -thre,	-head,	0.25f,	0.5f+thre,	// E''
	0.25f,	-thre,	-head,	0.75f,	0.5f+thre,	// F''

	0.25f,	-thre,	head,	0.75f,	0.5f+thre,	// F'
	0.5f,	0.0f,	head,	1.0f,	0.5f,	// A'
	0.5f,	0.0f,	-head,	1.0f,	0.5f,	// A''

	0.25f,	-thre,	head,	0.75f,	0.5f+thre,	// F'
	0.25f,	-thre,	-head,	0.75f,	0.5f+thre,	// F''
	0.5f,	0.0f,	-head,	1.0f,	0.5f,	// A''


};
HexagonalPrismModel::HexagonalPrismModel(GLfloat size)
{

	for (int i = 0; i < _countof(unit_prism_p) / 5; ++i)
	{
		coords.push_back(unit_prism_p[i * 5] * size);
		coords.push_back(unit_prism_p[i * 5 + 1] * size);
		coords.push_back(unit_prism_p[i * 5 + 2] * size);
		coords.push_back(unit_prism_p[i * 5 + 3]);
		coords.push_back(unit_prism_p[i * 5 + 4]);
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

void HexagonalPrismModel::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);

	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)coords.size());

	// all is drawn - unbind vertex array
	glBindVertexArray(0);
}

HexagonalPrismModel::~HexagonalPrismModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
