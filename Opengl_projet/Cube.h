#ifndef CUBE_H
#define CUBE_H
#include "ThreeDimensionalFigure.h"

class Cube : public ThreeDimensionalFigure
{
public:
	Cube(float* vertices, vector<unsigned int> vertexAttributeNumbers = { 3}, unsigned int eachAttributeNumber = 3);
	Cube(const Cube& src);
	Cube& operator=(const Cube& cube);
};

#endif

