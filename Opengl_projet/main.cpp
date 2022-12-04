#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Box.h"
#include "ShapeManager.h"
#include "ScreenProperty.h"
#include "PhysicsManager.h"

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
float* getVertices(glm::vec3 pos, glm::vec3 extent);
void processInput(GLFWwindow* window);
void addDefaultObjects();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float lastDepth;
bool firstMouse = true;
bool isMouseClicked = false;

// timing
float speed = 0.3f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

ShapeManager* shapeManager;
PhysicsManager* physicsManager;

int main(int argc, char **argv)
{
    
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // glad:  all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // make Drawing manager singleton
    shapeManager = ShapeManager::getInstance();

    //Initiate Physics
    physicsManager = PhysicsManager::getInstance();



    // render loop
    // -----------

    addDefaultObjects();

	

    while (!glfwWindowShouldClose(window))
    {
        // per frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
		
        if (lastFrame < 1.0f)
            continue;

		//cout << "fps: " << 1.0f / deltaTime << endl;

        // input
        // -----
        processInput(window);
 
        // render
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shapeManager->renderAll();

        physicsManager->Update(deltaTime);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// collision test 
void addDefaultObjects() {
    float* vertices = new float[24] {
        -0.35f, 0.2f, -0.1f,  //Point A 0
            -0.35f, 0.2f, 0.1f,//Point B 1
            -0.15f, 0.2f, -0.1f,//Point C 2
            -0.15f, 0.2f, 0.1f, //Point D 3
            -0.35f, 0.0f, -0.1f, //Point E 4
            -0.35f, 0.0f, 0.1f,//Point F 5
            -0.15f, 0.0f, -0.1f,//Point G 6
            -0.15f, 0.0f, 0.1f//Point H 7
    };
    shapeManager->addBox(new Box(vertices, KINEMETIC, 2.0f));

    for (float i = -1.5f; i < 1.8f; i += 1.2f) {
        for (float j = 1.0f; j < 4.1f; j += 1.2f) {
            shapeManager->addBox(new Box(getVertices(glm::vec3(i, 0.3f, j), glm::vec3(0.1f, 0.1f, 0.1f)), DYNAMIC));
        }
    }

   float* floor = new float[24] {
           -30.0f, -0.2f, -30.0f,  //Point A 0
           -30.0f, -0.2f,  30.0f,//Point B 1
            30.0f, -0.2f, -30.0f,//Point C 2
            30.0f, -0.2f,  30.0f, //Point D 3
           -30.0f, -0.3f, -30.0f, //Point E 4
           -30.0f, -0.3f,  30.0f,//Point F 5
            30.0f, -0.3f, -30.0f,//Point G 6
            30.0f, -0.3f,  30.0f//Point H 7
   };
   shapeManager->addBox(new Box(floor, STATIC));

   //shapeManager->addSphere(new Sphere());
   //shapeManager->addSphere(new Sphere());
   //shapeManager->addSphere(new Sphere());
}

float* getVertices(glm::vec3 pos, glm::vec3 extent) {
	float* vertices = new float[24] {
		pos.x - extent.x, pos.y + extent.y, pos.z - extent.z,  //Point A 0
			pos.x - extent.x, pos.y + extent.y, pos.z + extent.z,//Point B 1
			pos.x + extent.x, pos.y + extent.y, pos.z - extent.z,//Point C 2
			pos.x + extent.x, pos.y + extent.y, pos.z + extent.z, //Point D 3
			pos.x - extent.x, pos.y - extent.y, pos.z - extent.z, //Point E 4
			pos.x - extent.x, pos.y - extent.y, pos.z + extent.z,//Point F 5
			pos.x + extent.x, pos.y - extent.y, pos.z - extent.z,//Point G 6
			pos.x + extent.x, pos.y - extent.y, pos.z + extent.z//Point H 7
	};
	return vertices;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    float xDirection = 0, yDirection = 0, zDirection = 0;
    float distance = deltaTime * 2.0f;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        physicsManager->BlastAtPoint(shapeManager->getSelectedBox()->getCenter(), 5.0f, 4.0f);
        shapeManager->getSelectedBox()->setColor(glm::vec3(1, 0, 0));
    }
    else {
        shapeManager->getSelectedBox()->setColor(glm::vec3(0, 0, 1));
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        zDirection = distance;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        zDirection = -1 * distance;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        xDirection = -1 * distance;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        xDirection = distance;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        yDirection = -1 * distance;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        yDirection = distance;
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        shapeManager->rotateIn3D(5, glm::vec3(0, 1, 0));
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        shapeManager->rotateIn3D(-5, glm::vec3(0, 1, 0));

    shapeManager->processTranslation(xDirection, yDirection, zDirection);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        isMouseClicked = true;
        firstMouse = true;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_RELEASE) {
        isMouseClicked = false;
    }
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    GLbyte color[3];
    GLfloat colorf[3];
    GLuint index;
    GLfloat depth;

    if (isMouseClicked) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        float normalizedX = xoffset * 2 / SCR_WIDTH;
        float normalizedY = yoffset * 2 / SCR_HEIGHT;

        shapeManager->moveCamera(xoffset, yoffset);
        lastX = xpos;
        lastY = ypos;
    }
        
    }