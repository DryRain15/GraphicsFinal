#include "ThreeDimensionalFigure.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;

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
	this->translationMatrix[3][0] += dx;
	this->translationMatrix[3][1] += dy;
	this->translationMatrix[3][2] += dz;
	
	this->matrix = this->translationMatrix * this->rotationMatrix;
}

void ThreeDimensionalFigure::scale(float svalue, int index)
{
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	scaleMatrix[index][index] = 1 + svalue;
	this->matrix = scaleMatrix * this->matrix;
}

void ThreeDimensionalFigure::rotate(float rotationAngle, glm::vec3 rotationAxis)
{
	glm::quat quaternion;
	float angle = (rotationAngle * 3.14 / 180.0);
	quaternion = glm::angleAxis(angle, rotationAxis);
	rotate(quaternion);
}

void ThreeDimensionalFigure::rotate(glm::quat quaternion)
{
	mat4 rotateMatrix = glm::toMat4(quaternion);
	this->rotationMatrix = rotateMatrix * this->rotationMatrix;
	this->matrix = this->translationMatrix * this->rotationMatrix;
}

void ThreeDimensionalFigure::transformation(glm::mat3 newMatrix)
{
	glm::mat4 rotationMatrix(1);
	rotationMatrix[3][3] = 1;
	this->matrix = this->translationMatrix * this->rotationMatrix;
}

void ThreeDimensionalFigure::setPosition(float dx, float dy, float dz) {
	this->matrix[3][0] = dx;
	this->matrix[3][1] = dy;
	this->matrix[3][2] = dz;
}

glm::mat4 ThreeDimensionalFigure::getRotationMatrix()
{
	return this->rotationMatrix;
}
