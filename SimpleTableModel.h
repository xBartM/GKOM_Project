#pragma once
class SimpleTableModel
{
	GLuint VAO;
	GLuint VBO;
	std::vector<GLfloat> coords;
	std::vector<GLfloat> gunit_prism;

public:
	SimpleTableModel(GLfloat size, GLfloat);
	~SimpleTableModel();
	void Draw(const glm::mat4&, GLuint modelLoc) const;
	
};
