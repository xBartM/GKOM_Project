#define GLEW_STATIC
#define _USE_MATH_DEFINES

#include <math.h>

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ThreadModel.h"
using namespace std;

const int triangles = 64;
const float threadToHead = 0.5f / 3.0f / 4.0f;

void ThreadModel::makeUnitThread(vector<GLfloat> *helixOut, int threads) // thread count - next for loop :o - but with z translation (add thread lenth) - and then remove half or smthg
{
	
	//vector<GLfloat> helix;
	float t = 0;
	float sign = -1;

	for (int i = 0; i < triangles*threads; ++i)
	{
		t = (float)sign* (float)i / (float)triangles * (float) M_PI * 2.0f;
		// OUTER - 1st triangle - A
		/*X*/
		helixOut->push_back(/*0.25f -*/ 0.5f*cos(t));
		/*Y*/
		helixOut->push_back(/*0.25f -*/ 0.5f*sin(t));
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f - threadToHead * (float)i / (float)triangles);
		/* TEX */
		helixOut->push_back(1.0f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/

		// INNER UPPER - 1st triangle - A'
		/*X*/
		helixOut->push_back(/*0.5f / 3.0f - */cos(t) / 3.0f);
		/*Y*/
		helixOut->push_back(/*0.5f / 3.0f - */sin(t) / 3.0f);
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f * 2.0f - threadToHead * (float)i / (float)triangles); // starts 0.5 thread length higher 
		/* TEX */
		helixOut->push_back(0.9f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/

		// INNER UPPER - 1st triangle - B'
		++i;
		t = (float)sign* (float)i / (float)triangles *  (float)M_PI * 2.0f;
		/*X*/
		helixOut->push_back(/*0.5f / 3.0f - */cos(t) / 3.0f);
		/*Y*/
		helixOut->push_back(/*0.5f / 3.0f - */sin(t) / 3.0f);
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f * 2.0f - threadToHead * (float)i / (float)triangles); // starts 0.5 thread length higher 
		/* TEX */
		helixOut->push_back(0.9f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/
		--i;
		t = (float)sign*(float)i / (float)triangles *  (float)M_PI * 2.0f;


		// OUTER - 2nd triangle - A
		/*X*/
		helixOut->push_back(/*0.25f -*/ 0.5f*cos(t));
		/*Y*/
		helixOut->push_back(/*0.25f -*/ 0.5f*sin(t));
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f - threadToHead * (float)i / (float)triangles);
		/* TEX */
		helixOut->push_back(1.0f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/

		// OUTER - 2nd triangle - B
		++i;
		t = (float)sign*(float)i / (float)triangles *  (float)M_PI * 2.0f;
		/*X*/
		helixOut->push_back(/*0.25f -*/ 0.5f*cos(t));
		/*Y*/
		helixOut->push_back(/*0.25f -*/ 0.5f*sin(t));
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f - threadToHead * (float)i / (float)triangles);
		/* TEX */
		helixOut->push_back(1.0f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/

		// INNER UPPER - 2nd triangle - B'
		/*X*/
		helixOut->push_back(/*0.5f / 3.0f -*/ cos(t) / 3.0f);
		/*Y*/
		helixOut->push_back(/*0.5f / 3.0f -*/ sin(t) / 3.0f);
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f * 2.0f - threadToHead * (float)i / (float)triangles); // starts 0.5 thread length higher 
		/* TEX */
		helixOut->push_back(0.9f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/
		--i;
		t = (float)sign*(float)i / (float)triangles *  (float)M_PI * 2.0f;


		// OUTER - 2nd triangle - A
		/*X*/
		helixOut->push_back(/*0.25f - */0.5f*cos(t));
		/*Y*/
		helixOut->push_back(/*0.25f -*/ 0.5f*sin(t));
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f - threadToHead * (float)i / (float)triangles);
		/* TEX */
		helixOut->push_back(1.0f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/

		// INNER LOWER - 3rd triangle - A''
		/*X*/
		helixOut->push_back(/*0.5f / 3.0f -*/ cos(t) / 3.0f);
		/*Y*/
		helixOut->push_back(/*0.5f / 3.0f -*/ sin(t) / 3.0f);
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f * 0.0f - threadToHead * (float)i / (float)triangles); // starts 0.5 thread length lower 
		/* TEX */
		helixOut->push_back(0.9f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/

		// INNER LOWER - 3rd triangle - B''
		++i;
		t = (float)sign*(float)i / (float)triangles *  (float)M_PI * 2.0f;
		/*X*/
		helixOut->push_back(/*0.5f / 3.0f -*/ cos(t) / 3.0f);
		/*Y*/
		helixOut->push_back(/*0.5f / 3.0f -*/ sin(t) / 3.0f);
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f * 0.0f - threadToHead * (float)i / (float)triangles); // starts 0.5 thread length lower 
		/* TEX */
		helixOut->push_back(0.9f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/
		--i;
		t = (float)sign*(float)i / (float)triangles *  (float)M_PI * 2.0f;


		// OUTER - 4th triangle - A
		/*X*/
		helixOut->push_back(/*0.25f -*/ 0.5f*cos(t));
		/*Y*/
		helixOut->push_back(/*0.25f -*/ 0.5f*sin(t));
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f - threadToHead * (float)i / (float)triangles);
		/* TEX */
		helixOut->push_back(1.0f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/

		// OUTER - 4th triangle - B
		++i;
		t = (float)sign*(float)i / (float)triangles *  (float)M_PI * 2.0f;
		/*X*/
		helixOut->push_back(/*0.25f -*/ 0.5f*cos(t));
		/*Y*/
		helixOut->push_back(/*0.25f -*/ 0.5f*sin(t));
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f - threadToHead * (float)i / (float)triangles);
		/* TEX */
		helixOut->push_back(1.0f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/

		// INNER LOWER - 4th (?) triangle - B''
		/*X*/
		helixOut->push_back(/*0.5f / 3.0f -*/ cos(t) / 3.0f);
		/*Y*/
		helixOut->push_back(/*0.5f / 3.0f -*/ sin(t) / 3.0f);
		/*Z*/
		helixOut->push_back(threadToHead / 2.0f * 0.0f - threadToHead * (float)i / (float)triangles); // starts 0.5 thread length lower 
		/* TEX */
		helixOut->push_back(0.9f);	/* X const */
		helixOut->push_back((float)i / (float)triangles);	/* Y [0;1]*/
		--i;
		//t = (float)sign*(float)i / (float)triangles *  (float)M_PI * 2.0f;

	}
}



ThreadModel::ThreadModel()
{
	makeUnitThread(&coords, 24);
}

std::vector<GLfloat> ThreadModel::getCoords()
{
	return coords;
}

int ThreadModel::getTriangles()
{
	return triangles;
}

float ThreadModel::getThreadToHead()
{
	return threadToHead;
}

ThreadModel::ThreadModel(int size)
{
	makeUnitThread(&coords, size);

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

void ThreadModel::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);

	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)coords.size());

	// all is drawn - unbind vertex array
	glBindVertexArray(0);
}

ThreadModel::~ThreadModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
