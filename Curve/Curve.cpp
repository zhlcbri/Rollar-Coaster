#include "Curve.h"
#include "Window.h" //

//glm::vec3 p0 = glm::vec3(1.0f, 1.0f, 0.0f);
//glm::vec3 p1 = glm::vec3(30.0f, 30.0f, 0.0f);
//glm::vec3 p2 = glm::vec3(60.0f, 30.0f, 0.0f);
//glm::vec3 p3 = glm::vec3(100.0f, 1.0f, 0.0f);

Curve::Curve(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    anchor_points.push_back(p0);
    control_points.push_back(p1);
    control_points.push_back(p2);
    anchor_points.push_back(p3);
    
    G = glm::mat4(glm::vec4(p0, 1.0f), glm::vec4(p1, 1.0f),
                            glm::vec4(p2, 1.0f), glm::vec4(p3, 1.0f));
    
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    
    calculate_curve(); // 150 q values are pushed into vector points_on_curve
    // Create array object and buffers. Remember to delete your buffers when the object is destroyed!
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points_on_curve.size() * sizeof(GLfloat) * 3, points_on_curve.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // 6 * sizeof(float)
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //
    glGenVertexArrays(1, &pointVAO);
    glGenBuffers(1, &pointVBO);
    glBindVertexArray(pointVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    glBufferData(GL_ARRAY_BUFFER, control_points.size() * sizeof(GLfloat) * 3, control_points.data(), GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, Window::controls.size() * sizeof(GLfloat) * 3, Window::controls.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // 6 * sizeof(float)
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Curve::~Curve() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // point VAO VBO
    glDeleteVertexArrays(1, &pointVAO);
    glDeleteBuffers(1, &pointVBO);
}

void Curve::calculate_curve() {
//    glm::mat4 G = glm::mat4(glm::vec4(p0, 1.0f), glm::vec4(p1, 1.0f),
//                                glm::vec4(p2, 1.0f), glm::vec4(p3, 1.0f));

//    glm::mat4 B = glm::mat4(glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
//                            glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
//                            glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
//                            glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

    for (int k = 0; k <= 150; k++) {
        float t = k/150.0f;
        glm::vec4 T = glm::vec4(pow(t, 3.0f), pow(t, 2.0f), t, 1.0f);
        glm::vec4 q = G * B * T;
        points_on_curve.push_back(q/q.w);
    }
}

void Curve::draw(GLuint shaderProgram) {
    // Calculate the combination of the model and view (camera inverse) matrices
    glm::mat4 modelview = Window::V * toWorld;
    
    uProjection = glGetUniformLocation(shaderProgram, "projection");
    uModelview = glGetUniformLocation(shaderProgram, "modelview");
    
    // Now send these values to the shader program
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
    //toWorld
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &toWorld[0][0]);
    
    // Now draw the cube. We simply need to bind the VAO associated with it.
    glBindVertexArray(VAO);
    // Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
//    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    
    glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)points_on_curve.size());

    // Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
    glBindVertexArray(0);
}

// create separate VAOs and corresponding VBOS for anchor points
// draw in curve class
void Curve::drawLines(GLuint shaderProgram) {
    // Calculate the combination of the model and view (camera inverse) matrices
    glm::mat4 modelview = Window::V * toWorld;
    
    uProjection = glGetUniformLocation(shaderProgram, "projection");
    uModelview = glGetUniformLocation(shaderProgram, "modelview");
    
    // Now send these values to the shader program
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
    //toWorld
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &toWorld[0][0]);
    
    // Now draw the cube. We simply need to bind the VAO associated with it.
    glBindVertexArray(pointVAO);
    // Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
    //    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    
    glDrawArrays(GL_LINES, 0, (GLsizei)control_points.size());
//    glDrawArrays(GL_LINES, 0, (GLsizei)Window::controls.size());
    
    // Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
    glBindVertexArray(0);
}


