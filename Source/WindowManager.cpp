#include "WindowManager.hpp"

#include <bitset>
#include <iostream>

#include "Core/Coordinator.hpp"

/**
 * global coordinator
 */
extern Coordinator gCoordinator;

/**
 * init the windows
 * @param windowTitle window name
 * @param windowWidth window width
 * @param windowHeight window height
 * @param windowPositionX window pos x
 * @param windowPositionY windows pos y
 */
void WindowManager::Init(std::string const &windowTitle,
                         unsigned int windowWidth, unsigned int windowHeight,
                         unsigned int windowPositionX,
                         unsigned int windowPositionY) {
  glfwInit();

  mWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(),
                             NULL, NULL);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create OpenGL Context
  glfwMakeContextCurrent(mWindow);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSwapInterval(2);

  // Configure OpenGL
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
}

/**
 * update the window
 */
void WindowManager::Update() { glfwSwapBuffers(mWindow); }

/**
 * shutdown the window
 */
void WindowManager::Shutdown() {
  glfwDestroyWindow(mWindow);
  glfwTerminate();
}

/**
 * handle event
 */
void WindowManager::ProcessEvents() {
  glfwPollEvents();

  bool buttonStateChanged = true;

  if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE)) {
    gCoordinator.SendEvent(Events::Window::QUIT);
  } else if (glfwGetKey(mWindow, GLFW_KEY_W)) {
    mButtons.set(static_cast<std::size_t>(InputButtons::W));
  } else if (glfwGetKey(mWindow, GLFW_KEY_A)) {
    mButtons.set(static_cast<std::size_t>(InputButtons::A));
  } else if (glfwGetKey(mWindow, GLFW_KEY_S)) {
    mButtons.set(static_cast<std::size_t>(InputButtons::S));
  } else if (glfwGetKey(mWindow, GLFW_KEY_D)) {
    mButtons.set(static_cast<std::size_t>(InputButtons::D));
  } else if (glfwGetKey(mWindow, GLFW_KEY_Q)) {
    mButtons.set(static_cast<std::size_t>(InputButtons::Q));
  } else if (glfwGetKey(mWindow, GLFW_KEY_E)) {
    mButtons.set(static_cast<std::size_t>(InputButtons::E));
  } else {
    buttonStateChanged = false;
  }

  if (buttonStateChanged) {
    Event event(Events::Window::INPUT);
    event.SetParam(Events::Window::Input::INPUT, mButtons);
    gCoordinator.SendEvent(event);
  }
}
