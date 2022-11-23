#include "ThreeDimensionalFigure.h"

ThreeDimensionalFigure& ThreeDimensionalFigure::operator=(const ThreeDimensionalFigure& threeDimensionalFigure)
{
	Shape::operator=(threeDimensionalFigure);
	return *this;
}

void ThreeDimensionalFigure::translation(float dx, float dy, float dz)
{
	glm::mat4 transMatrix = glm::mat4(1.0f);
	transMatrix[3][0] = dx;
	transMatrix[3][1] = dy;
	transMatrix[3][2] = dz;

	this->matrix = transMatrix * this->matrix;
}

void ThreeDimensionalFigure::scale(float svalue, int index)
{
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	scaleMatrix[index][index] = 1 + svalue;
	this->matrix = scaleMatrix * this->matrix;
}

void ThreeDimensionalFigure::rotate(float angle)
{
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	float cosValue = cos(angle);
	float sinValue = sin(angle);

	rotationMatrix[0][0] = cosValue;
	rotationMatrix[1][0] = -1 * sinValue;
	rotationMatrix[0][1] = sinValue;
	rotationMatrix[1][1] = cosValue;

	this->matrix = rotationMatrix * this->matrix;
}

void ThreeDimensionalFigure::transformation(glm::mat3 newMatrix)
{
	glm::mat4 rotationMatrix(1);
	rotationMatrix[3][3] = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rotationMatrix[i][j] = newMatrix[i][j];
		 }
	}

    this->matrix = rotationMatrix * this->matrix;
}

void ThreeDimensionalFigure::setPosition(float dx, float dy, float dz) {
	this->matrix[3][0] = dx;
	this->matrix[3][1] = dy;
	this->matrix[3][2] = dz;
}