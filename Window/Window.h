#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "shader.h"
#include "Skybox.h"
#include "Curve.h"
#include "Cube.h"
#include "OBJObject.h"
#include <unordered_set>
#include <limits>

// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

class Window
{
public:
	static int width;
	static int height;
    
    static double xpos;
    static double ypos;
    static double OLD_XPOS;
    static double OLD_YPOS;
    static double scrollY;
    
    static glm::vec3 A;
    static glm::vec3 B;
    static float angle;
    static glm::vec3 axis;
    
	static glm::mat4 P; // P for projection
	static glm::mat4 V; // V for view
    static bool CAMERA_ROTATE;
    static bool POINT_INTERACTION;
    static bool SPHERE_MOVE;
    static bool TO_HIGHEST_POINT;
    static bool RIDERS_VIEW;
    
    static bool TEST_DRAG;
    
    static GLuint pointVAO, pointVBO; //
//    static GLuint uProjection, uModelview;
    static vector<Curve*> curves;
    static vector<glm::vec3> anchors; //
    static vector<glm::vec3> controls;
    static vector<glm::vec3> selectable_points;
    
    static glm::mat4 matrix;
    static int countC; // curve counter
    static float countT; // time counter (0 to 150)
    static int countP; // point counter
    static glm::vec3 highestPoint;
    
    static void update();
    static float velocityAt(float currentHeight);
    static void drawLines(GLuint shaderProgram);
    static void selectionDraw(GLuint shaderProgram);
    static void processSelection(int xx, int yy);
    static void renderSelection();
    
	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    //
    static glm::vec3 trackBallMapping(GLFWwindow* window, double xpos, double ypos);
    
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif
