// nao ta usando a tela toda

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
void init(GLFWwindow* window);
void render();
void update();
void changeSquareColor();

// global variables

struct {
  float x;
  float y;
} pos, dir;

struct {
  float r;
  float g;
  float b;
} color;

const float DELTA = 4;

int fbWidth, fbHeight; // framebuffer limits

// end global variables

int main() {
  if(!glfwInit()) {
    fprintf(stderr, "failed to initialize GLFW\n");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  GLFWwindow* window = glfwCreateWindow(1280, 720, "DVD logo bouncing animation", NULL, NULL);
  
  if(!window) {
    fprintf(stderr, "failed to create window\n");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

  init(window);

  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    render();
    update();
    glfwSwapBuffers(window);
  }
  
  glfwTerminate();
  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  switch (key) {
    case GLFW_KEY_UP:
      dir.y = DELTA;
      break;
    case GLFW_KEY_DOWN:
      dir.y = -DELTA;
      break;
    case GLFW_KEY_RIGHT:
      dir.x = DELTA;
      break;
    case GLFW_KEY_LEFT:
      dir.x = -DELTA;
      break;
    case GLFW_KEY_SPACE:
      if (action == GLFW_PRESS) changeSquareColor();
      break;
  }
  return;
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
  return;
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
  fbWidth = width;
  fbHeight = height;
  glViewport(0, 0, fbWidth, fbHeight);
  return;
}

void init(GLFWwindow* window) {
  glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
  glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
  glViewport(0, 0, fbWidth, fbHeight);
  dir.x = dir.y = DELTA;
  pos.x = (float) fbWidth / 2;
  pos.y = (float) fbHeight / 2;
  color.r = 0.0f;
  color.g = 1.0f;
  color.b = 0.0f;
  return;
}

void render() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, fbWidth, 0, fbHeight, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(pos.x, pos.y, 0);

  glColor3f(color.r, color.g, color.b);
  glBegin(GL_QUADS);
    glVertex2d(-100, 100);
  glVertex2d(-100, -100);
    glVertex2d(100, -100);
  glVertex2d(100, 100);
  glEnd();
  return;
}

void update() {
  if(pos.x <= 100 && dir.x < 0) dir.x = DELTA;
  if(pos.x >= fbWidth - 100 && dir.x > 0) dir.x = -DELTA;
  if(pos.y <= 100 && dir.y < 0) dir.y = DELTA;
  if(pos.y >= fbHeight - 100 && dir.y > 0) dir.y = -DELTA;

  pos.x += dir.x;
  pos.y += dir.y;

  return;
}

void changeSquareColor() {
  if(color.r == 1.0f) {
    color.r = 0.0f;
    color.g = 1.0f;
  } else if(color.g == 1.0f) {
    color.g = 0.0f;
    color.b = 1.0f;
  } else if(color.b == 1.0f) {
    color.b = 0.0f;
    color.r = 1.0f;
  }
}
