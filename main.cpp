
#include <iostream>
#include <cmath>

// GLEW
#define GLEW_STATIC

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "shaders.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// Function prototypes
void moveVerticles (GLfloat buffers[3]) {
    for (int i = 0; i < 9; i++) {
        buffers[i] += 0.002;
    }
}

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

GLFWwindow* createWindow () {
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    // Create a GLFW window object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Window the great", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    // Set the required callback functions
//  glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    return window;
}

int main() {
    GLFWwindow* window = createWindow();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaders::vertex_shader, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shaders::fragment_shader, NULL);
    glCompileShader(fragmentShader);

    GLuint fragmentShader_niceGray;
    fragmentShader_niceGray = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader_niceGray, 1, &shaders::fragment_shader_niceGray, NULL);
    glCompileShader(fragmentShader_niceGray);

    GLint success;
    GLchar log[512] = "ddfds";
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    glGetShaderInfoLog(vertexShader, 512, NULL, log);
    std::cout << "Vertex shader compillation status = " << success << "_\n";
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    glGetShaderInfoLog(fragmentShader, 512, NULL, log);
    std::cout << "fragment shader compillation status = " << success << "_\n";
    glGetShaderiv(fragmentShader_niceGray, GL_COMPILE_STATUS, &success);
    glGetShaderInfoLog(fragmentShader_niceGray, 512, NULL, log);
    std::cout << "nice gray fragment shader compillation status = " << success << "_\n";

    GLuint shaderProgram, shaderProgram_forGrey;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    shaderProgram_forGrey= glCreateProgram();
    glAttachShader(shaderProgram_forGrey, vertexShader);
    glAttachShader(shaderProgram_forGrey, fragmentShader_niceGray);
    glLinkProgram(shaderProgram_forGrey);

    int verticlesCount = 100;
    int indicesCount = 30;

    float verticles[verticlesCount];

    const long twoPow32 = 2147483648;

    for (int i = 0; i < verticlesCount; i++) {
        if ((i + 1) % 3 == 0)
            verticles[i] = 0;
        else
            verticles[i] = ((GLfloat)rand() - twoPow32 / 2) / (GLfloat)twoPow32;
    }

    int indices[indicesCount];
    for (int i = 0; i < indicesCount; i++)
        indices[i] = i;




    GLuint vao, vbo, veo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &veo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//        // texture loading, binding and generating
//    int tex_width, tex_height, nrChannels;
//    unsigned char *data = stbi_load("water_texture.jpg", &width, &height, &nrChannels, 0);
//
//    unsigned int texture;
//    glGenTextures(1, &texture);
//
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//
//    stbi_image_free(data);

    // Game loop
    while (!glfwWindowShouldClose(window)) {
    // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.01f, 0.0f, 0.0f, 0.3f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram_forGrey);
        glBindVertexArray(vao);
//        glDrawArrays(GL_TRIANGLES,0,3);
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

  // Terminate GLFW, clearing any resources allocated by GLFW.

  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
  glfwTerminate();
  return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  std::cout << key << std::endl;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
