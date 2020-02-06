#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Animation.h"
#include "HexagonalPrismModel.h"
#include "ThreadModel.h"
#include "TableModel.h"
#include "SpannerModel.h"
#include "SimpleTableModel.h"


Animation::Animation(HexagonalPrismModel* hpm, ThreadModel* thr, TableModel* tab, SpannerModel* spa)
{
	this->isSpannerIn = true;
	this->isScrewIn = false;
	this->isOnThread = false;

	// bind objects
	this->hpm = hpm;
	this->thr = thr;
	this->tab = tab;
	this->spa = spa;

	tabPos = glm::rotate(tabPos, (float)glm::radians(-90.0f), glm::vec3(1, 0, 0));
	hpmPos = glm::rotate(hpmPos, (float)glm::radians(-90.0f), glm::vec3(1, 0, 0));
	thrPos = glm::rotate(thrPos, (float)glm::radians(-90.0f), glm::vec3(1, 0, 0));
	spaPos = glm::rotate(spaPos, (float)glm::radians(-90.0f), glm::vec3(1, 0, 0));

	hpmPos = glm::translate(hpmPos, glm::vec3(0.0f, 0.0f, 1.5f));
	thrPos = glm::translate(thrPos, glm::vec3(0.0f, 0.0f, 1.5f)); /* 12960.0f / 24.0f / 360.0f*/
	spaPos = glm::translate(spaPos, glm::vec3(0.0f, 0.0f, 1.5f));

	hpmPos = glm::translate(hpmPos, glm::vec3(0.0f, 0.0f, 0.25f));
	spaPos = glm::translate(spaPos, glm::vec3(0.0f, 0.0f, 0.25f));

	spaPos = glm::translate(spaPos, glm::vec3(3.0f, 0.0f, 0.0f));
}

Animation::Animation(HexagonalPrismModel* hpm, ThreadModel* thr, SimpleTableModel* stm, SpannerModel* spa)
{
	this->isSpannerIn = true;
	this->isScrewIn = false;
	this->isOnThread = false;

	// bind objects
	this->hpm = hpm;
	this->thr = thr;
	this->stm = stm;
	this->spa = spa;

	stmPos = glm::rotate(stmPos, (float)glm::radians(-90.0f), glm::vec3(1, 0, 0));
	hpmPos = glm::rotate(hpmPos, (float)glm::radians(-90.0f), glm::vec3(1, 0, 0));
	thrPos = glm::rotate(thrPos, (float)glm::radians(-90.0f), glm::vec3(1, 0, 0));
	spaPos = glm::rotate(spaPos, (float)glm::radians(-90.0f), glm::vec3(1, 0, 0));

	hpmPos = glm::translate(hpmPos, glm::vec3(0.0f, 0.0f, 1.5f));
	thrPos = glm::translate(thrPos, glm::vec3(0.0f, 0.0f, 1.5f)); /* 12960.0f / 24.0f / 360.0f*/
	spaPos = glm::translate(spaPos, glm::vec3(0.0f, 0.0f, 1.5f));

	hpmPos = glm::translate(hpmPos, glm::vec3(0.0f, 0.0f, 0.25f));
	spaPos = glm::translate(spaPos, glm::vec3(0.0f, 0.0f, 0.25f));

	spaPos = glm::translate(spaPos, glm::vec3(3.0f, 0.0f, 0.0f));
}

void Animation::drawScene(GLuint modelLoc)
{
	drawPrism(modelLoc);
	drawThread(modelLoc);
	drawTable(modelLoc);
	drawSpanner(modelLoc);
}

void Animation::drawPrism(GLuint modelLoc)
{
	hpm->Draw(hpmPos, modelLoc);
}

void Animation::drawThread(GLuint modelLoc)
{
	thr->Draw(thrPos, modelLoc);
}

void Animation::drawTable(GLuint modelLoc)
{
	tab->Draw(tabPos, modelLoc);
}

void Animation::drawSpanner(GLuint modelLoc)
{
	spa->Draw(spaPos, modelLoc);
}

void Animation::drawSimpleTable(GLuint modelLoc)
{
	stm->Draw(stmPos, modelLoc);
}

void Animation::screwIn()
{
	if (!isSpannerIn)
		return;
	if (isScrewIn)
		return;
	if (!isOnThread)
	{
		hpmPos = glm::translate(hpmPos, glm::vec3(0.0f, 0.0f, -DISTSTEP*10));
		thrPos = glm::translate(thrPos, glm::vec3(0.0f, 0.0f, -DISTSTEP*10));
		spaPos = glm::translate(spaPos, glm::vec3(0.0f, 0.0f, -DISTSTEP*10));

		if (spaPos[3][1] < 1.5f + 1.0f / 12.0f)
			isOnThread = true;
		return;
	}

	hpmPos = glm::translate(hpmPos, glm::vec3(0.0f, 0.0f, -DISTSTEP));
	hpmPos = glm::rotate(hpmPos, (float)glm::radians(-ANGLESTEP), glm::vec3(0, 0, 1));

	thrPos = glm::translate(thrPos, glm::vec3(0.0f, 0.0f, -DISTSTEP));
	thrPos = glm::rotate(thrPos, (float)glm::radians(-ANGLESTEP), glm::vec3(0, 0, 1));

	spaPos = glm::translate(spaPos, glm::vec3(0.0f, 0.0f, -DISTSTEP));

	// rotation
	glm::mat4 id = glm::mat4();
	glm::mat4 id2 = glm::mat4();
	glm::mat4 id3 = glm::mat4();
	glm::vec3 aux = glm::vec3();
	//aux[0] = abs((hpmPos[3][0] - spaPos[3][0])) + cos(abs(hpmPos[3][1] - spaPos[3][1]));	// COSINE ERROR OMG !!!
	aux[0] = spa->getRotPoint();
	aux[0] = sqrt((hpmPos[3][0] - spaPos[3][0])*(hpmPos[3][0] - spaPos[3][0]) + (hpmPos[3][2] - spaPos[3][2]) * (hpmPos[3][2] - spaPos[3][2]));	// ALTERNATIVE
	aux[1] = 0;
	aux[2] = 0;

	id *= glm::translate(id, aux);
	id2 *= glm::rotate(id2, (float)glm::radians(-ANGLESTEP), glm::vec3(0, 0, 1));
	id3 *= glm::translate(id3, -aux);

	spaPos = spaPos * (id3 * (id2 * id));

	if (spaPos[3][1] < 0.38f)
		isScrewIn = true;
}

void Animation::screwOut()
{
	if (!isSpannerIn)
		return;

	if (!isOnThread)
	{
		if (hpmPos[3][1] > 2.0f)
			return;

		hpmPos = glm::translate(hpmPos, glm::vec3(0.0f, 0.0f, DISTSTEP * 10));
		thrPos = glm::translate(thrPos, glm::vec3(0.0f, 0.0f, DISTSTEP * 10));
		spaPos = glm::translate(spaPos, glm::vec3(0.0f, 0.0f, DISTSTEP * 10));

		return;
	}

	if (spaPos[3][1] > 1.5f + 1.0f / 12.0f)
		isOnThread = false;

	isScrewIn = false;

	hpmPos = glm::translate(hpmPos, glm::vec3(0.0f, 0.0f, DISTSTEP));
	hpmPos = glm::rotate(hpmPos, (float)glm::radians(ANGLESTEP), glm::vec3(0, 0, 1));

	thrPos = glm::translate(thrPos, glm::vec3(0.0f, 0.0f, DISTSTEP));
	thrPos = glm::rotate(thrPos, (float)glm::radians(ANGLESTEP), glm::vec3(0, 0, 1));

	spaPos = glm::translate(spaPos, glm::vec3(0.0f, 0.0f, DISTSTEP));

	// rotation
	glm::mat4 id = glm::mat4();
	glm::mat4 id2 = glm::mat4();
	glm::mat4 id3 = glm::mat4();
	glm::vec3 aux = glm::vec3();
	//aux[0] = abs((hpmPos[3][0] - spaPos[3][0])) + cos(abs(hpmPos[3][1] - spaPos[3][1]));	// COSINE ERROR OMG !!!
	
	aux[0] = spa->getRotPoint();
	aux[0] = sqrt((hpmPos[3][0] - spaPos[3][0])*(hpmPos[3][0] - spaPos[3][0]) + (hpmPos[3][2] - spaPos[3][2]) * (hpmPos[3][2] - spaPos[3][2]));	// ALTERNATIVE

	aux[1] = 0;
	aux[2] = 0;
	
	id *= glm::translate(id, aux);
	id2 *= glm::rotate(id2, (float)glm::radians(ANGLESTEP), glm::vec3(0, 0, 1));
	id3 *= glm::translate(id3, -aux);

	spaPos = spaPos * (id3 * (id2 * id));

	
}

//void Animation::spannerIn()
//{
//	if (isSpannerIn)
//		return;
//
//	float distance;
//	distance = sqrt((glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][0] - spaPos[3][0])*
//		(glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][0] - spaPos[3][0]) +
//		(glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][2] - spaPos[3][2]) * 
//		(glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][2] - spaPos[3][2]));
//	if (distance < 0.1f)
//	{
//		isSpannerIn = true;
//		spaPos = hpmPos;
//		spaPos = glm::translate(spaPos, glm::vec3(3.0f, 0.0f, 0.0f));
//		return;
//	}
//
//	spaPos = glm::translate(spaPos, glm::vec3(-DISTSTEP * 100, 0.0f, 0.0f));
//}
//
//void Animation::spannerOut()
//{
//	isSpannerIn = false;
//	if (spaPos[3][0] > 7.0f || spaPos[3][2] > 7.0f || spaPos[3][0] < -7.0f || spaPos[3][2] < -7.0f)
//		return;
//	spaPos = glm::translate(spaPos, glm::vec3(DISTSTEP*100, 0.0f, 0.0f));
//}

void Animation::spannerIn()
{
	//if (isSpannerIn)
	//return;

	float distance;
	distance = sqrt(
		(glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][0] - spaPos[3][0])*
		(glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][0] - spaPos[3][0]) +
		(glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][2] - spaPos[3][2]) * 
		(glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][2] - spaPos[3][2]));
	if (distance < 1.05f)
	{
		isSpannerIn = true;
		spaPos = glm::translate(spaPos, glm::vec3(-DISTSTEP * 100, 0.0f, 0.0f));
		if (distance < 0.01f)
		{
			spaPos = hpmPos;
			spaPos = glm::translate(spaPos, glm::vec3(3.0f, 0.0f, 0.0f));
		}
		return;
	}
	spaPos = glm::translate(spaPos, glm::vec3(-DISTSTEP * 100, 0.0f, 0.0f));

}

void Animation::spannerOut()
{


	float distance;
	distance = sqrt((glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][0] - spaPos[3][0])*
		(glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][0] - spaPos[3][0]) +
		(glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][2] - spaPos[3][2]) * (glm::translate(hpmPos, glm::vec3(3.0f, 0.0f, 0.0f))[3][2] - spaPos[3][2]));
	if (distance > 1.05f)
		isSpannerIn = false;

	if (spaPos[3][0] > 7.0f || spaPos[3][2] > 7.0f || spaPos[3][0] < -7.0f || spaPos[3][2] < -7.0f)
		return;
	spaPos = glm::translate(spaPos, glm::vec3(DISTSTEP * 100, 0.0f, 0.0f));
}