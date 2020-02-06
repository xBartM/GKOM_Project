#pragma once
class HexagonalPrismModel
{
	GLuint VAO;
	GLuint VBO;
	std::vector<GLfloat> coords;
	//std::vector<GLfloat> unit_prism_p;

public:
	HexagonalPrismModel(GLfloat size);
	~HexagonalPrismModel();
	void Draw(const glm::mat4&, GLuint modelLoc) const;
	void generateVertices();
};
