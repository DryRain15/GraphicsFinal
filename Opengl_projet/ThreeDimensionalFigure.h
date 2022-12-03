#ifndef THREE_DIMENSIONAL_FIGURE_H
#define THREE_DIMENSIONAL_FIGURE_H

#include "Shape.h"

class ThreeDimensionalFigure: public Shape
{
protected:
	glm::mat4 rotationMatrix;
public:
	ThreeDimensionalFigure& operator=(const ThreeDimensionalFigure& threeDimensionalFigure);
	virtual void translation(float dx, float dy, float dz);
	void scale(float svalue, int index);
	void rotate(float angle, glm::vec3 rotationAxis);
	void rotate(glm::quat quaternion);
	void transformation(glm::mat3 newMatrix);
	void setPosition(float dx, float dy, float dz);
	glm::mat4 getRotationMatrix();
};

#endif