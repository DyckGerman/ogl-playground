
#include <iostream>

// GLEW
#define GLEW_STATIC

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "shaders.h"

// Function prototypes
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run application game loop
int main() {
  std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
  // Init GLFW
  glfwInit();
  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // Create a GLFW window object that we can use for GLFW's functions
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Window the great", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);

  // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
  glewExperimental = GL_TRUE;
  // Initialize GLEW to setup the OpenGL Function pointers
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

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

  GLfloat verticles_1[] = {
      0.8f, -0.5f, 0.0f,
      0.1f, -0.5f, 0.0f,
      0.45f, 0.2f, 0.0f
  };

  GLfloat verticles_2[] = {
      0.6f, 0.7f, 0.0f,
      0.0f, -0.5f, 0.0f,
      -0.6f, 0.7f, 0.0f
  };

  GLfloat verticles_3[] = {
      -0.8f, -0.5f, 0.0f,
      -0.1f, -0.5f, 0.0f,
      -0.45f, 0.2f, 0.0f
  };

  GLuint vaos[3], buffers[3];

  glCreateVertexArrays(1, &vaos[0]);
  glBindVertexArray(vaos[0]);
  glGenBuffers(1, &buffers[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticles_1), verticles_1, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glCreateVertexArrays(1, &vaos[1]);
  glBindVertexArray(vaos[1]);
  glGenBuffers(1, &buffers[1]);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticles_2), verticles_2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glCreateVertexArrays(1, &vaos[2]);
  glBindVertexArray(vaos[2]);
  glGenBuffers(1, &buffers[2]);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticles_3), verticles_3, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);


  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
    glfwPollEvents();

    // Render
    // Clear the colorbuffer
    glClearColor(0.01f, 0.02f, 0.015f, 0.3f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vaos[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(shaderProgram_forGrey);
    glBindVertexArray(vaos[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(shaderProgram);
    glBindVertexArray(vaos[2]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
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