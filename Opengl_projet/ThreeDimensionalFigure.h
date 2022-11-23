#ifndef THREE_DIMENSIONAL_FIGURE_H
#define THREE_DIMENSIONAL_FIGURE_H

#include "Shape.h"

class ThreeDimensionalFigure: public Shape
{
public:
	ThreeDimensionalFigure& operator=(const ThreeDimensionalFigure& threeDimensionalFigure);
	// 좋은 아이디어 생각나면 transformation 코드 줄이기
	void translation(float dx, float dy, float dz);
	void scale(float svalue, int index);
	void rotate(float angle);
	void transformation(glm::mat3 newMatrix);
	void setPosition(float dx, float dy, float dz);
};

#endif