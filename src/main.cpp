#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

void framebufferSizeCallback(GLFWwindow* pWindow, int widht, int height);
void processInput(GLFWwindow* pWindow);

const char* vertexShaderSource {
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "}\0"        
};
const char* fragmentShaderSource {
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0"
};


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

    // ----------create-vertex-buffer----------
    float vertices[] {-0.5f, -0.5f, 0.0f,
                       0.5f, -0.5f, 0.0f,
                       0.0f,  0.5f, 0.0f};

    unsigned int VBO;
    glGenBuffers(1, &VBO);   
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ----------create-and-compiling-vertex-shader-----------
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);   
    glCompileShader(vertexShader);
    
    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        glGetShaderInfoLog(vertexShader, 521, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    // ----------create-and-compiling-fragment-shader-----------
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 521, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    // ----------shader-program-------------------------------
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FALED\n" << infolog << std::endl;
    }

    glUseProgram(shaderProgram);

    while(!glfwWindowShouldClose(pWindow)) {
        processInput(pWindow);
        glClearColor(color1, color2, color3, color4);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
