#include "ThreeDimensionalFigure.h"
#include "Collider.h"
#include <windows.h>

class Sphere : public Collider, public ThreeDimensionalFigure
{
private:
	glm::vec3 center;
	float radius;
	int latitudes;
	int longitudes;
	GLuint m_vao, m_vboVertex, m_vboIndex;
	int numsToDraw;
public:
	Sphere(glm::vec3 center = glm::vec3(0, 0.5, 0), float radius = 0.1, Collider_Type type = DYNAMIC, float weight = 1, glm::vec3 velocity = glm::vec3(0.3));
	~Sphere();
	void render() override;
	bool isCollideWith(Sphere* neighbor);
	void init(GLuint vertexPositionID);
	glm::vec3 getCenter();
	float getRadius();
	virtual void translation(float directionX, float directionY, float directionZ);
};

