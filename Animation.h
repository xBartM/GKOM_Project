#pragma once

class HexagonalPrismModel;
class ThreadModel;
class TableModel;
class SpannerModel;
class SimpleTableModel;

const float ANGLESTEP = 0.5f;
const float DISTSTEP =  ANGLESTEP / 24.0f / 360.0f;	// 1/24 per 360 degrees


class Animation
{
	glm::mat4 hpmPos;
	glm::mat4 thrPos;
	glm::mat4 tabPos;
	glm::mat4 spaPos;
	glm::mat4 stmPos;
	HexagonalPrismModel *hpm;
	ThreadModel *thr;
	TableModel *tab; 
	SpannerModel *spa;
	SimpleTableModel *stm;

	bool isSpannerIn;
	bool isScrewIn;
	bool isOnThread;

	

public:
	Animation(HexagonalPrismModel*,	ThreadModel*, TableModel*, SpannerModel*);
	Animation(HexagonalPrismModel*, ThreadModel*, SimpleTableModel*, SpannerModel*);
	//~Animation();
	void drawScene(GLuint);
	void drawPrism(GLuint);
	void drawThread(GLuint);
	void drawTable(GLuint);
	void drawSpanner(GLuint);
	void drawSimpleTable(GLuint);
	
	void screwIn();
	void screwOut();

	void spannerIn();
	void spannerOut();
};