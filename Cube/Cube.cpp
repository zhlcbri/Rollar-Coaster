#include "Cube.h"
#include "Window.h"

unsigned int cubemapTexture2;

Cube::Cube(float size)
{
	this->toWorld = glm::mat4(1.0f);
	this->size = size;
	this->angle = 0.0f;
    
    faces = {
        "right.ppm",
        "left.ppm",
        "top.ppm",
        "bottom.ppm",
        "back.ppm",
        "front.ppm"
    };
    
    cubemapTexture2 = loadCubemap(faces);
    
    // Create array object and buffers. Remember to delete your buffers when the object is destroyed!
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
    // Consider the VAO as a container for all your buffers.
    glBindVertexArray(VAO);
    
    // Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
    // you want to draw, such as vertices, normals, colors, etc.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
    // the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Enable the usage of layout location 0 (check the vertex shader to see what this is)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
                          3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
                          GL_FLOAT, // What type these components are
                          GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
                          3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
                          (GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
    
//    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
//    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(1); // Enable the usage of layout location 1
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // when layout=1
    
    // We've sent the vertex data over to OpenGL, but there's still something missing.
    // In what order should it draw those vertices? That's why we'll need a GL_ELEMENT_ARRAY_BUFFER for this.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);

}

Cube::~Cube()
{
}

unsigned int Cube::loadCubemap(vector<string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                         );
            stbi_image_free(data);
        }
        else
        {
            cout << "Cubemap texture failed to load at path: " << faces[i] << endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); // seamless edge
    
    return textureID;
}

void Cube::draw(GLuint shaderProgram)
{
    // Calculate the combination of the model and view (camera inverse) matrices
    glm::mat4 modelview = Window::V * toWorld;
    
    glEnable(GL_CULL_FACE);
//    glCullFace(GL_FRONT);
    glCullFace(GL_BACK);
    //    glDepthMask(GL_FALSE);
    
    // We need to calculate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
    // Consequently, we need to forward the projection, view, and model matrices to the shader programs
    // Get the location of the uniform variables "projection" and "modelview"
    uProjection = glGetUniformLocation(shaderProgram, "projection");// light.colorvec3
    //    uModelview = glGetUniformLocation(shaderProgram, "modelview");
    uModelview = glGetUniformLocation(shaderProgram, "view");
    
    // Now send these values to the shader program
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
    //
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &toWorld[0][0]);
    
    // skybox cube
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture2);
    //    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    //    glDepthMask(GL_TRUE);
    
    glDepthFunc(GL_LESS); // set depth function back to default
}

//==================================================================================

void Cube::update()
{
	spin(1.0f);
}

void Cube::spin(float deg)
{
	this->angle += deg;
	if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
	// This creates the matrix to rotate the cube
	this->toWorld = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
}

