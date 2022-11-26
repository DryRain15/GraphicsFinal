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

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void addDefaultObjects();

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float lastDepth;
bool firstMouse = true;

// timing
float speed = 0.3f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

ShapeManager* shapeManager;

int main()
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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // make Drawing manager singleton
    shapeManager = ShapeManager::getInstance();

    // render loop
    // -----------

    addDefaultObjects();

    while (!glfwWindowShouldClose(window))
    {
        // per frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
       // -----
        processInput(window);
 
        // render
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shapeManager->renderAll();

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

// ¹Ú½º collision test 
void addDefaultObjects() {
    float* vertices = new float[24] {
        -0.1f, 0.1f, -0.1f,  //Point A 0
        -0.1f, 0.1f, 0.1f,//Point B 1
        0.1f, 0.1f, -0.1f,//Point C 2
        0.1f, 0.1f, 0.1f, //Point D 3
        -0.1f, -0.1f, -0.1f, //Point E 4
        -0.1f, -0.1f, 0.1f,//Point F 5
        0.1f, -0.1f, -0.1f,//Point G 6
        0.1f, -0.1f, 0.1f//Point H 7
    };
   shapeManager->addBox(new Box(vertices));
   float* secondVertices = new float[24] {
       -0.35f, 0.1f, -0.1f,  //Point A 0
        -0.35f, 0.1f, 0.1f,//Point B 1
        -0.15f, 0.1f, -0.1f,//Point C 2
        -0.15f, 0.1f, 0.1f, //Point D 3
        -0.35f, -0.1f, -0.1f, //Point E 4
        -0.35f, -0.1f, 0.1f,//Point F 5
        -0.15f, -0.1f, -0.1f,//Point G 6
        -0.15f, -0.1f, 0.1f//Point H 7
   };
   shapeManager->addBox(new Box(secondVertices));

   

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    float xDirection = 0, zDirection = 0;
    float distance = deltaTime;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        zDirection = distance;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        zDirection = -1 * distance;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        xDirection = -1 * distance;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        xDirection = distance;

    shapeManager->processTranslation(xDirection, 0, zDirection);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}