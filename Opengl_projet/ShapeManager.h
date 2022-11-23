#include <vector>
#include "ThreeDimensionalFigure.h"
#include "Camera.h"
#include "Shader.h"

using namespace std;

class ShapeManager
{
private:
	static ShapeManager* drawingManager;
	ShapeManager();
	vector<ThreeDimensionalFigure*> threeDimensionFigures;
	Shader* basic2DShader;
	Shader* basic3DShader;
	int polygonNumber;
	int threeDimensionalFigureNumber;
	int selectedPolygonIndex;
	int selectedThreeDimensionalFigureIndex;
	// camera
	Camera * camera;
	glm::mat4 projection;
	static void Destroy();
	bool isValidIndex3d(int index);
public:
	/**
	* Singletons should not be cloneable.
	* =delete: prohibiting copying
	*/
	static ShapeManager* getInstance();
	ShapeManager(ShapeManager& other) = delete;
	void operator= (const ShapeManager &) = delete;
	void addThreeDimensionalFigure(ThreeDimensionalFigure * threeDimensionalFigure);
	void renderAll();
	void selectThreeDimensionalFigure(int index);
	void processTranslation(float dx, float dy, float dz);
	void rotateIn3D(glm::mat4 rogridMatrix);
	void moveCamera(float xoffset, float yoffset);
	void processKeyBoard(CameraMovement direction, float deltaTime);
};
