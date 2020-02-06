#pragma once
class SpannerModel
{
	GLuint VBO, EBO, VAO;
	std::vector<GLfloat> coords;
	float size;

public:
	SpannerModel(GLfloat size);
	~SpannerModel();
	void Draw(const glm::mat4&, GLuint modelLoc) const;
	float getRotPoint();
};