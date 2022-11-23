#ifndef THREE_DIMENSIONAL_FIGURE_H
#define THREE_DIMENSIONAL_FIGURE_H

#include "Shape.h"

class ThreeDimensionalFigure: public Shape
{
public:
	ThreeDimensionalFigure& operator=(const ThreeDimensionalFigure& threeDimensionalFigure);
	// ���� ���̵�� �������� transformation �ڵ� ���̱�
	void translation(float dx, float dy, float dz);
	void scale(float svalue, int index);
	void rotate(float angle);
	void transformation(glm::mat3 newMatrix);
	void setPosition(float dx, float dy, float dz);
};

#endif