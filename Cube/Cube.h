#ifndef _CUBE_H_
#define _CUBE_H_

#ifdef __APPLE__
// If modern OpenGL replace gl.h with gl3.h
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>
#include "stb_image.h"

using namespace std;

//unsigned int cubemapTexture2;

class Cube
{
public:
	Cube(float);
	~Cube();
    
	glm::mat4 toWorld;
    
    GLuint VBO, VAO, EBO; //
    GLuint VBO2;
    
    GLuint uProjection, uModelview; //

	float size;
	float angle;

//    void draw();
    
	void update();

	void spin(float);
    
    vector<string> faces;
    void draw(GLuint shaderProgram);
    unsigned int loadCubemap(vector<string> faces);
    
    const GLfloat vertices[8][3] = {
        // "Front" vertices
        {-5.0, -5.0,  5.0}, {5.0, -5.0,  5.0}, {5.0,  5.0,  5.0}, {-5.0,  5.0,  5.0},
        // "Back" vertices
        {-5.0, -5.0, -5.0}, {5.0, -5.0, -5.0}, {5.0,  5.0, -5.0}, {-5.0,  5.0, -5.0}
    };
    
    // Note that GL_QUADS is deprecated in modern OpenGL (and removed from OSX systems).
    // This is why we need to draw each face as 2 triangles instead of 1 quadrilateral
    const GLuint indices[6][6] = {
        // Front face
        {0, 1, 2, 2, 3, 0},
        //        {2, 1, 0, 0, 3, 2},
        // Top face
        {1, 5, 6, 6, 2, 1},
        //        {6, 5, 1, 1, 2, 6},
        // Back face
        {7, 6, 5, 5, 4, 7},
        //        {5, 6, 7, 7, 4, 5},
        // Bottom face
        {4, 0, 3, 3, 7, 4},
        //        {3, 0, 4, 4, 7, 3},
        // Left face
        {4, 5, 1, 1, 0, 4},
        //        {1, 5, 4, 4, 0, 1},
        // Right face
        {3, 2, 6, 6, 7, 3}
        //        {6, 2, 3, 3, 7, 6}
    };
    
//    vector<glm::vec3> normals;
};

#endif

