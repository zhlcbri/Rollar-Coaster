#ifndef Curve_h
#define Curve_h

// glfw functions
#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "stb_image.h"

// glm functions
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;
class Curve {
private:
//    float factorial(int num);
    
public:
    glm::mat4 toWorld = glm::mat4(1.0f);
    GLuint uProjection, uModelview; //
    GLuint VBO, VAO, EBO;
    glm::vec3 p0, p1, p2, p3;
    glm::mat4 G;
    glm::mat4 B = glm::mat4(glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
                            glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
                            glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
                            glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    
    GLuint pointVAO, pointVBO;
    
    Curve(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    ~Curve();
    
    vector<glm::vec3> anchor_points;
    vector<glm::vec3> control_points; // 4 control points that determine a curve, namely p
    vector<glm::vec3> points_on_curve; // q computed from Bernstein polynomial and p
    
//    vector<glm::vec3> points_physics; // points sphere should move along concerning velocity
    
    void calculate_curve();
//    void velocityAt(float currentHeight, float maxHeight);
//    void calculate_curve_physics(float currentHeight, float maxHeight); //
//    vector<glm::vec3> calculate_curve_physics(float v); //
    
    void draw(GLuint shaderProgram);
    void drawLines(GLuint shaderProgram);

//    void update();
    // handles
    // update
};


#endif /* Curve_h */
