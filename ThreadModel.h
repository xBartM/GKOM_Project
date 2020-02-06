#pragma once
class ThreadModel
{
	GLuint VAO;
	GLuint VBO;
	std::vector<GLfloat> coords;

public:
	ThreadModel();
	ThreadModel(int size);
	~ThreadModel();
	void Draw(const glm::mat4&, GLuint modelLoc) const;
	void makeUnitThread(std::vector<GLfloat>*, int);
	std::vector<GLfloat> getCoords();
	int getTriangles();
	float getThreadToHead();
};

