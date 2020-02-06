#define GLEW_STATIC
#define _USE_MATH_DEFINES

#include <math.h>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TableModel.h"
#include "ThreadModel.h"
using namespace std;



// m9 - push_back (ntimes) + push_back same thing but with different points on table - 10 threads
void TableModel::generateVertices(std::vector<GLfloat>* table, float size)
{
	ThreadModel thread;
	std::vector<GLfloat> temp(thread.getCoords());
	int triangles = thread.getTriangles();
	float threadToHead = thread.getThreadToHead();

	for (int i = 0; i < triangles; ++i)
	{
		for (int j = 0; j < 60; ++j)	// first 4 triangles - like in ThreadModel
			table->push_back(temp[60 * i + j]);
		
		/* next 2 triangles are for hole in the table */
		table->push_back(temp[i * 60 + 0]);	// A X
		table->push_back(temp[i * 60 + 1]);	// A Y
		table->push_back(temp[i * 60 + 2]);	// A Z
		table->push_back(temp[i * 60 + 3]);	// A TEX
		table->push_back(temp[i * 60 + 4]);	// A TEX

		table->push_back(temp[i * 60 + 0]);	// A''' X
		table->push_back(temp[i * 60 + 1]);	// A''' Y
		table->push_back(threadToHead / 2.0f * 2.0f);				// A''' Z
		table->push_back(temp[0.9f]);		// A''' TEX
		table->push_back(temp[0.0f]);		// A''' TEX

		table->push_back(temp[i * 60 + 20]);// B''' X
		table->push_back(temp[i * 60 + 21]);// B''' Y
		table->push_back(threadToHead / 2.0f * 2.0f);				// B''' Z
		table->push_back(temp[0.9f]);		// B''' TEX
		table->push_back(temp[0.0f]);		// B''' TEX

		/* second triangle */
		table->push_back(temp[i * 60 + 0]);	// A X
		table->push_back(temp[i * 60 + 1]);	// A Y
		table->push_back(temp[i * 60 + 2]);	// A Z
		table->push_back(temp[i * 60 + 3]);	// A TEX
		table->push_back(temp[i * 60 + 4]);	// A TEX

		table->push_back(temp[i * 60 + 20]);// B X
		table->push_back(temp[i * 60 + 21]);// B Y
		table->push_back(temp[i * 60 + 22]);// B Z
		table->push_back(temp[i * 60 + 23]);// B TEX
		table->push_back(temp[i * 60 + 24]);// B TEX

		table->push_back(temp[i * 60 + 20]);// B''' X
		table->push_back(temp[i * 60 + 21]);// B''' Y
		table->push_back(threadToHead / 2.0f * 2.0f);				// B''' Z
		table->push_back(temp[0.9f]);		// B''' TEX
		table->push_back(temp[0.0f]);		// B''' TEX

		/* tabletop */

		table->push_back(temp[i * 60 + 0]);	// A''' X
		table->push_back(temp[i * 60 + 1]);	// A''' Y
		table->push_back(threadToHead / 2.0f * 2.0f);				// A''' Z
		table->push_back(temp[0.9f]);		// A''' TEX
		table->push_back(temp[0.0f]);		// A''' TEX

		table->push_back(temp[i * 60 + 20]);// B''' X
		table->push_back(temp[i * 60 + 21]);// B''' Y
		table->push_back(threadToHead / 2.0f * 2.0f);				// B''' Z
		table->push_back(temp[0.9f]);		// B''' TEX
		table->push_back(temp[0.0f]);		// B''' TEX

		if (temp[i * 60 + 5] > 0)	// A''' X > 0 ?
		{
			if (temp[i * 60 + 6] > 0)	// A''' Y > 0 ?
			{
				table->push_back(size);// B''' X
				table->push_back(size / 0.5f);// B''' Y
				table->push_back(threadToHead / 2.0f * 2.0f);				// B''' Z
				table->push_back(temp[0.9f]);		// B''' TEX
				table->push_back(temp[0.0f]);		// B''' TEX
			}
			else	// A''' Y <= 0 ?
			{
				table->push_back(size);// B''' X
				table->push_back(-size / 0.5f);// B''' Y
				table->push_back(threadToHead / 2.0f * 2.0f);				// B''' Z
				table->push_back(temp[0.9f]);		// B''' TEX
				table->push_back(temp[0.0f]);		// B''' TEX
			}
		}
		else	// A''' X <= 0 ?
		{
			if (temp[i * 60 + 6] >= 0)	// A''' Y > 0 ?
			{
				table->push_back(-size);// B''' X
				table->push_back(size / 0.5f);// B''' Y
				table->push_back(threadToHead / 2.0f * 2.0f);				// B''' Z
				table->push_back(temp[0.9f]);		// B''' TEX
				table->push_back(temp[0.0f]);		// B''' TEX
			}
			else	// A''' Y <= 0 ?
			{
				table->push_back(-size);// B''' X
				table->push_back(-size / 0.5f);// B''' Y
				table->push_back(threadToHead / 2.0f * 2.0f);				// B''' Z
				table->push_back(temp[0.9f]);		// B''' TEX
				table->push_back(temp[0.0f]);		// B''' TEX
			}
		}
	}

	// 1st big triangle

	table->push_back(size);
	table->push_back(size * 2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	table->push_back(size);
	table->push_back(-size * 2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	table->push_back(0.5f);
	table->push_back(0.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	//2nd big triangle

	table->push_back(size);
	table->push_back(size * 2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	table->push_back(-size);
	table->push_back(size * 2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	table->push_back(0.0f);
	table->push_back(0.5f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	// 3rd big triangle

	table->push_back(-size);
	table->push_back(size * 2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	table->push_back(-size);
	table->push_back(-size * 2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	table->push_back(-0.5f);
	table->push_back(0.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	// 4th big triangle

	table->push_back(-size);
	table->push_back(-size * 2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	table->push_back(size);
	table->push_back(-size * 2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	table->push_back(0.0f);
	table->push_back(-0.5f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);		
	table->push_back(temp[0.0f]);		

	for (int i = triangles; i < triangles*23; ++i)	// fill the middle threads
	{
		for (int j = 0; j < 60; ++j)
			table->push_back(temp[60 * i + j]);
	}

	for (int i = 23*triangles; i < triangles*24; ++i)	// last thread
	{
		for (int j = 0; j < 60; ++j)	// first 4 triangles - like in ThreadModel
			table->push_back(temp[60 * i + j]);

		/* next 2 triangles are for hole in the table */
		table->push_back(temp[i * 60 + 35]);	// A'' X
		table->push_back(temp[i * 60 + 36]);	// A'' Y
		table->push_back(temp[i * 60 + 37]);	// A'' Z
		table->push_back(temp[i * 60 + 38]);	// A'' TEX
		table->push_back(temp[i * 60 + 39]);	// A'' TEX

		table->push_back(temp[i * 60 + 35]);	// A''' X
		table->push_back(temp[i * 60 + 36]);	// A''' Y
		table->push_back(- threadToHead * 24.0f);				// A''' Z
		table->push_back(temp[0.9f]);		// A''' TEX
		table->push_back(22.0f);		// A''' TEX

		table->push_back(temp[i * 60 + 40]);// B''' X
		table->push_back(temp[i * 60 + 41]);// B''' Y
		table->push_back(- threadToHead * 24.0f);				// B''' Z
		table->push_back(temp[0.9f]);		// B''' TEX
		table->push_back(22.0f);		// B''' TEX

		/* second triangle */
		table->push_back(temp[i * 60 + 35]);	// A'' X
		table->push_back(temp[i * 60 + 36]);	// A'' Y
		table->push_back(temp[i * 60 + 37]);	// A'' Z
		table->push_back(temp[i * 60 + 38]);	// A'' TEX
		table->push_back(temp[i * 60 + 39]);	// A'' TEX

		table->push_back(temp[i * 60 + 40]);// B'' X
		table->push_back(temp[i * 60 + 41]);// B'' Y
		table->push_back(temp[i * 60 + 42]);// B'' Z
		table->push_back(temp[i * 60 + 43]);// B'' TEX
		table->push_back(temp[i * 60 + 44]);// B'' TEX

		table->push_back(temp[i * 60 + 40]);// B''' X
		table->push_back(temp[i * 60 + 41]);// B''' Y
		table->push_back( - threadToHead * 24.0f);				// B''' Z
		table->push_back(temp[0.9f]);		// B''' TEX
		table->push_back(22.0f);		// B''' TEX


		/* tablebottom (?) */
		table->push_back(temp[i * 60 + 35]);	// A''' X
		table->push_back(temp[i * 60 + 36]);	// A''' Y
		table->push_back(-threadToHead * 24.0f);				// A''' Z
		table->push_back(temp[0.9f]);		// A''' TEX
		table->push_back(temp[0.0f]);		// A''' TEX

		table->push_back(temp[i * 60 + 40]);// B''' X
		table->push_back(temp[i * 60 + 41]);// B''' Y
		table->push_back(-threadToHead * 24.0f);				// B''' Z
		table->push_back(temp[0.9f]);		// B''' TEX
		table->push_back(temp[0.0f]);		// B''' TEX

		if (temp[i * 60 + 35] > 0)	// A''' X > 0 ?
		{
			if (temp[i * 60 + 36] >= 0)	// A''' Y > 0 ?
			{
				table->push_back(size);// B''' X
				table->push_back(size / 0.5f);// B''' Y
				table->push_back(-threadToHead * 24.0f);				// B''' Z
				table->push_back(temp[0.9f]);		// B''' TEX
				table->push_back(temp[0.0f]);		// B''' TEX
			}
			else	// A''' Y <= 0 ?
			{
				table->push_back(size);// B''' X
				table->push_back(-size / 0.5f);// B''' Y
				table->push_back(-threadToHead * 24.0f);				// B''' Z
				table->push_back(temp[0.9f]);		// B''' TEX
				table->push_back(temp[0.0f]);		// B''' TEX
			}
		}
		else	// A''' X <= 0 ?
		{
			if (temp[i * 60 + 36] >= 0)	// A''' Y > 0 ?
			{
				table->push_back(-size);// B''' X
				table->push_back(size / 0.5f);// B''' Y
				table->push_back(-threadToHead * 24.0f);				// B''' Z
				table->push_back(temp[0.9f]);		// B''' TEX
				table->push_back(temp[0.0f]);		// B''' TEX
			}
			else	// A''' Y <= 0 ?
			{
				table->push_back(-size);// B''' X
				table->push_back(-size / 0.5f);// B''' Y
				table->push_back(-threadToHead * 24.0f);				// B''' Z
				table->push_back(temp[0.9f]);		// B''' TEX
				table->push_back(temp[0.0f]);		// B''' TEX
			}
		}

		// 1st big triangle

		table->push_back(size);
		table->push_back(size * 2.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		table->push_back(size);
		table->push_back(-size * 2.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		table->push_back(1.0f / 3.0f);
		table->push_back(0.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		//2nd big triangle

		table->push_back(size);
		table->push_back(size * 2.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		table->push_back(-size);
		table->push_back(size * 2.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		table->push_back(0.0f);
		table->push_back(1.0f / 3.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		// 3rd big triangle

		table->push_back(-size);
		table->push_back(size * 2.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		table->push_back(-size);
		table->push_back(-size * 2.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		table->push_back(-1.0f / 3.0f);
		table->push_back(0.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		// 4th big triangle

		table->push_back(-size);
		table->push_back(-size * 2.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		table->push_back(size);
		table->push_back(-size * 2.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);

		table->push_back(0.0f);
		table->push_back(-1.0f / 3.0f);
		table->push_back(-threadToHead * 24.0f);
		table->push_back(temp[0.9f]);
		table->push_back(temp[0.0f]);
	}

	/* sides */
	table->push_back(size);
	table->push_back(size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(size);
	table->push_back(size*2.0f);
	table->push_back(-threadToHead*24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(-size);
	table->push_back(size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);


	table->push_back(size);
	table->push_back(size*2.0f);
	table->push_back(-threadToHead * 24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(-size);
	table->push_back(size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(-size);
	table->push_back(size*2.0f);
	table->push_back(-threadToHead*24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);


	table->push_back(-size);
	table->push_back(-size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(-size);
	table->push_back(-size*2.0f);
	table->push_back(-threadToHead * 24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(size);
	table->push_back(-size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);


	table->push_back(-size);
	table->push_back(-size*2.0f);
	table->push_back(-threadToHead * 24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(size);
	table->push_back(-size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(size);
	table->push_back(-size*2.0f);
	table->push_back(-threadToHead * 24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);


	table->push_back(size);
	table->push_back(size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(size);
	table->push_back(size*2.0f);
	table->push_back(-threadToHead * 24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(size);
	table->push_back(-size*2.0f);
	table->push_back(-threadToHead * 24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);


	table->push_back(size);
	table->push_back(-size*2.0f);
	table->push_back(-threadToHead * 24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(size);
	table->push_back(-size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(size);
	table->push_back(size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);


	table->push_back(-size);
	table->push_back(-size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(-size);
	table->push_back(-size*2.0f);
	table->push_back(-threadToHead * 24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(-size);
	table->push_back(size*2.0f);
	table->push_back(-threadToHead * 24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);


	table->push_back(-size);
	table->push_back(size*2.0f);
	table->push_back(-threadToHead * 24);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(-size);
	table->push_back(size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

	table->push_back(-size);
	table->push_back(-size*2.0f);
	table->push_back(threadToHead);
	table->push_back(temp[0.9f]);
	table->push_back(temp[0.0f]);

}


TableModel::TableModel(GLfloat size)
{
	generateVertices(&coords, size);

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



void TableModel::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);

	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)coords.size());

	// all is drawn - unbind vertex array
	glBindVertexArray(0);
}

TableModel::~TableModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}