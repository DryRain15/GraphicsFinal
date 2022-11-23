#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include  <vector>
#include "Shader.h"

using namespace std;

// 만들 수 있다면 추상클래스로 만들고 싶다. 
class Shape
{
protected:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int eachAttributeNumber;
	unsigned int totalVerticeNumber;
	unsigned int totalCoordinateNumber;
	unsigned int totalIndiceNumber;
	float* verticeAttributes;
	vector<unsigned int> vertexAttributeNumbers;
	unsigned int* indices;
	glm::vec3 color;
	glm::mat4 matrix;
	void initiliazeVertexBufferDatas();
public:
	Shape();
	Shape(float* vertices, vector<unsigned int> & vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	virtual ~Shape();
	void copyFrom(const Shape& src);
	Shape(const Shape& src);
	Shape& operator=(const Shape& shape);
	virtual void render();
	void setShaderValue(Shader* shader);
	glm::mat4 getMatrix();
};

#endif
