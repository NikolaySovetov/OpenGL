#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebufferSizeCallback(GLFWwindow* pWindow, int widht, int height);
void processInput(GLFWwindow* pWindow);

int main()  {

    int windowWigth  = 800;
    int windowHeight = 600;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow {glfwCreateWindow(windowWigth, windowHeight, 
                                         "Learn OpenGL", nullptr, nullptr)};
    if (!pWindow) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, windowWigth, windowHeight);

    glfwSetFramebufferSizeCallback(pWindow, framebufferSizeCallback);

    float color1 {0.2f};
    float color2 {0.3f};
    float color3 {0.3f};
    float color4 {1.0f};

    while(!glfwWindowShouldClose(pWindow)) {
        processInput(pWindow);
        glClearColor(color1, color2, color3, color4);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* pWindow) {
    if(glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, true);
    }
}
