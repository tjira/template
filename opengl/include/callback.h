#pragma once

#include "gui.h"

// define all the callbacks
void keyCallback(GLFWwindow* window, int key, int, int action, int mods);
void positionCallback(GLFWwindow* window, double x, double y);
void resizeCallback(GLFWwindow* window, int width, int height);
void scrollCallback(GLFWwindow* window, double, double dy);
