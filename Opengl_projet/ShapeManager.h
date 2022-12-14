#include <vector>
#include "Camera.h"
#include "Shader.h"
#include "Box.h"
#include "Sphere.h"
#include "ScreenProperty.h"
#include "CollisionData.h"
#include "PhysicsManager.h"

using namespace std;

class ShapeManager
{
private:
	static ShapeManager* drawingManager;
	ShapeManager();
	vector<Box*> boxes;
	vector<Sphere*> spheres;
	Shader* basic2DShader;
	Shader* basic3DShader;
	Shader* lightCubeShader;
	int boxNumber;
	int sphereNumber;
	int selectedBoxIndex;
	int selectedSphereIndex;
	GLuint lightCubeVAO;
	// camera
	Camera * camera;
	Box* lightCube;
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
	void addBox(Box * box);
	void addSphere(Sphere* sphere);
	void renderAll();
	Box* getSelectedBox();
	void selectThreeDimensionalFigure(int index);
	void processTranslation(float xDirection, float yDirection, float zDirection);
	void rotateIn3D(float rotationAngle, glm::vec3 rotationAxis);
	void moveCamera(float xoffset, float yoffset);
	void processKeyBoard(CameraMovement direction, float deltaTime);
};
