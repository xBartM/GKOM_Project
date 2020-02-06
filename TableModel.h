#pragma once
class TableModel
{
	GLuint VAO;
	GLuint VBO;
	std::vector<GLfloat> coords;
	std::vector<GLfloat> gunit_prism;

public:
	TableModel(GLfloat size);
	~TableModel();
	void Draw(const glm::mat4&, GLuint modelLoc) const;
	void generateVertices(std::vector<GLfloat>*, float);
};
