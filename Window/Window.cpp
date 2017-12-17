#include "Window.h"
#include <math.h>
#include "shader.h"
#include <time.h> //

//float zVal = 0.0f;
const char* window_title = "GLFW Starter Project";

GLint shaderProgram_curve;
GLint shaderProgram_skybox;
GLint shaderProgram_obj;
GLint shaderProgram_reflect;
GLint shaderProgram_color;
GLint shaderProgram_select;

// On some systems you need to change this to the absolute path
#define CURVE_VERTEX_SHADER_PATH "curveShader.vert"
#define CURVE_FRAGMENT_SHADER_PATH "curveShader.frag"

#define SKYBOX_VERTEX_SHADER_PATH "skyboxShader.vert"
#define SKYBOX_FRAGMENT_SHADER_PATH "skyboxShader.frag"

#define OBJ_VERTEX_SHADER_PATH "objShader.vert"
#define OBJ_FRAGMENT_SHADER_PATH "objShader.frag"

#define REFLECT_VERTEX_SHADER_PATH "reflectiveShader.vert"
#define REFLECT_FRAGMENT_SHADER_PATH "reflectiveShader.frag"

#define COLOR_VERTEX_SHADER_PATH "colorShader.vert"
#define COLOR_FRAGMENT_SHADER_PATH "colorShader.frag"

#define SELECTION_VERTEX_SHADER_PATH "selectionShader.vert"
#define SELECTION_FRAGMENT_SHADER_PATH "selectionShader.frag"

// Default camera parameters
//glm::vec3 cam_pos(-300.0f, 300.0f, 0.0f);        // e  | Position of camera
glm::vec3 cam_pos(-15.0f, -5.0f, 20.0f);        // e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;

double Window::xpos;
double Window::ypos;

double Window::click_xpos;
double Window::click_ypos;

double Window::OLD_XPOS;
double Window::OLD_YPOS;

double Window::scrollY = 0.0f;

GLuint Window::pointVAO;
GLuint Window::pointVBO;//

glm::vec3 Window::A;
glm::vec3 Window::B;
float Window::angle;
glm::vec3 Window::axis;

bool Window::CAMERA_ROTATE;
bool Window::POINT_INTERACTION;
bool Window::SPHERE_MOVE = true;
bool Window::TO_HIGHEST_POINT;
bool Window::RIDERS_VIEW;

bool Window::MOVE_UP;
bool Window::MOVE_DOWN;
bool Window::MOVE_LEFT;
bool Window::MOVE_RIGHT;

Skybox * skybox;

Curve* Window::curve0;
Curve* Window::curve1;
Curve* Window::curve2;
Curve* Window::curve3;
Curve* Window::curve4;
Curve* Window::curve5;
Curve* Window::curve6;
Curve* Window::curve7;
Curve* Window::curve8;
Curve* Window::curve9;

//OBJObject * obj;
OBJObject * sphere;

glm::vec3 Window::p0 = glm::vec3(1.0f, 16.0f, -20.0f);
glm::vec3 Window::p1 = glm::vec3(4.0f, 16.0f, -20.0f);
glm::vec3 Window::p2 = glm::vec3(8.0f, 8.0f, -20.0f);
glm::vec3 Window::p3 = glm::vec3(8.0f, 6.0f, -20.0f);
//
glm::vec3 Window::p4 = glm::vec3(p3 - p2 + p3);
glm::vec3 Window::p5 = glm::vec3(12.0f, 5.0f, -20.0f);
glm::vec3 Window::p6 = glm::vec3(16.0f, 8.0f, -20.0f);
//
glm::vec3 Window::p7 = glm::vec3(p6 - p5 + p6);
glm::vec3 Window::p8 = glm::vec3(24.0f, 10.0f, -25.0f);
glm::vec3 Window::p9 = glm::vec3(28.0f, 10.0f, -25.0f);
//
glm::vec3 Window::p10 = glm::vec3(p9 - p8 + p9);
glm::vec3 Window::p11 = glm::vec3(34.0f, 15.0f, -25.0f);
glm::vec3 Window::p12 = glm::vec3(34.0f, 15.0f, -18.0f);
//
glm::vec3 Window::p13 = glm::vec3(p12 - p11 + p12);
glm::vec3 Window::p14 = glm::vec3(32.0f, 9.0f, -10.0f);
glm::vec3 Window::p15 = glm::vec3(32.0f, 5.0f, -10.0f);
//
glm::vec3 Window::p16 = glm::vec3(p15 - p14 + p15);
glm::vec3 Window::p17 = glm::vec3(28.0f, 3.0f, -15.0f);
glm::vec3 Window::p18 = glm::vec3(28.0f, 1.0f, -15.0f);
//
glm::vec3 Window::p19 = glm::vec3(p18 - p17 + p18);
glm::vec3 Window::p20 = glm::vec3(22.0f, 0.0f, -18.0f);
glm::vec3 Window::p21 = glm::vec3(18.0f, 0.0f, -18.0f);
//
glm::vec3 Window::p22 = glm::vec3(p21 - p20 + p21);
glm::vec3 Window::p23 = glm::vec3(12.0f, -4.0f, -18.0f);
glm::vec3 Window::p24 = glm::vec3(8.0f, -4.0f, -18.0f);
//
glm::vec3 Window::p25 = glm::vec3(p24 - p23 + p24);
glm::vec3 Window::p26 = glm::vec3(5.0f, 10.0f, -22.0f);
glm::vec3 Window::p27 = glm::vec3(2.0f, 10.0f, -22.0f);
//
glm::vec3 Window::p28 = glm::vec3(p27 - p26 + p27);
glm::vec3 Window::p29 = glm::vec3(p0 - p1 + p0);

glm::vec3 Window::selected; //

vector<Curve*> Window::curves;
vector<Curve*> Window::originalCurves;
vector<glm::vec3> Window::anchors; //
vector<glm::vec3> Window::controls; // handle points
vector<glm::vec3> Window::selectable_points; // all points

glm::vec3 Window::highestPoint;
glm::mat4 Window::matrix = glm::mat4(1.0f); // used to control sphere movement
int Window::countC = 0;
float Window::countT = 0.0f;
int Window::countP = 0;

int Window::index = -1;

void Window::initialize_objects()
{
    skybox = new Skybox();
   
//    curve0 = new Curve(p0, p1, p2, p3);
//    curve1 = new Curve(p3, p4, p5, p6);
//    curve2 = new Curve(p6, p7, p8, p9);
//    curve3 = new Curve(p9, p10, p11, p12);
//    curve4 = new Curve(p12, p13, p14, p15);
//    curve5 = new Curve(p15, p16, p17, p18);
//    curve6 = new Curve(p18, p19, p20, p21);
//    curve7 = new Curve(p21, p22, p23, p24);
//    curve8 = new Curve(p24, p25, p26, p27);
//    curve9 = new Curve(p27, p28, p29, p0);
    define_curves();
    
//    anchors.push_back(p0);
//    anchors.push_back(p3);
//    anchors.push_back(p6);
//    anchors.push_back(p9);
//    anchors.push_back(p12);
//    anchors.push_back(p15);
//    anchors.push_back(p18);
//    anchors.push_back(p21);
//    anchors.push_back(p24);
//    anchors.push_back(p27);
    populate_anchors();
    populate_controls();
//    controls.push_back(p2);
//    controls.push_back(p4);
//    controls.push_back(p5);
//    controls.push_back(p7);
//    controls.push_back(p8);
//    controls.push_back(p10);
//    controls.push_back(p11);
//    controls.push_back(p13);
//    controls.push_back(p14);
//    controls.push_back(p16);
//    controls.push_back(p17);
//    controls.push_back(p19);
//    controls.push_back(p20);
//    controls.push_back(p22);
//    controls.push_back(p23);
//    controls.push_back(p25);
//    controls.push_back(p26);
//    controls.push_back(p28);
//    controls.push_back(p1);
//    controls.push_back(p29);

    
//    obj = new OBJObject("sphere.obj");
    sphere = new OBJObject("sphere.obj");
    
//    curves.push_back(curve0);
//    curves.push_back(curve1);
//    curves.push_back(curve2);
//    curves.push_back(curve3);
//    curves.push_back(curve4);
//    curves.push_back(curve5);
//    curves.push_back(curve6);
//    curves.push_back(curve7);
//    curves.push_back(curve8);
//    curves.push_back(curve9);
    populate_curves();
    originalCurves = curves; //
    
    // push all points into a vector
//    for (Curve* c: curves) {
//        selectable_points.push_back(c->p0); // selectable[0] = p0
//        selectable_points.push_back(c->p1);
//        selectable_points.push_back(c->p2);
//    }
    populate_selectables();
    
	// Load the shader program. Make sure you have the correct filepath up top
    shaderProgram_curve = LoadShaders(CURVE_VERTEX_SHADER_PATH, CURVE_FRAGMENT_SHADER_PATH);
    shaderProgram_skybox = LoadShaders(SKYBOX_VERTEX_SHADER_PATH, SKYBOX_FRAGMENT_SHADER_PATH);
    shaderProgram_obj = LoadShaders(OBJ_VERTEX_SHADER_PATH, OBJ_FRAGMENT_SHADER_PATH);
    shaderProgram_reflect = LoadShaders(REFLECT_VERTEX_SHADER_PATH, REFLECT_FRAGMENT_SHADER_PATH);
    shaderProgram_color = LoadShaders(COLOR_VERTEX_SHADER_PATH, COLOR_FRAGMENT_SHADER_PATH);
    shaderProgram_select = LoadShaders(SELECTION_VERTEX_SHADER_PATH, SELECTION_FRAGMENT_SHADER_PATH);
    
    glGenVertexArrays(1, &pointVAO); // below from these lines are for binding control points data
    glGenBuffers(1, &pointVBO);
    
    glBindVertexArray(pointVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
//    glBufferData(GL_ARRAY_BUFFER, controls.size() * sizeof(glm::vec3), controls.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, controls.size() * sizeof(GLfloat) * 3, controls.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // 6 * sizeof(float)
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Window::define_curves() {
    curve0 = new Curve(p0, p1, p2, p3);
    curve1 = new Curve(p3, p4, p5, p6);
    curve2 = new Curve(p6, p7, p8, p9);
    curve3 = new Curve(p9, p10, p11, p12);
    curve4 = new Curve(p12, p13, p14, p15);
    curve5 = new Curve(p15, p16, p17, p18);
    curve6 = new Curve(p18, p19, p20, p21);
    curve7 = new Curve(p21, p22, p23, p24);
    curve8 = new Curve(p24, p25, p26, p27);
    curve9 = new Curve(p27, p28, p29, p0);
}

void Window::populate_curves() {
    curves.push_back(curve0);
    curves.push_back(curve1);
    curves.push_back(curve2);
    curves.push_back(curve3);
    curves.push_back(curve4);
    curves.push_back(curve5);
    curves.push_back(curve6);
    curves.push_back(curve7);
    curves.push_back(curve8);
    curves.push_back(curve9);
}

void Window::populate_selectables() {
    for (Curve* c: curves) {
        selectable_points.push_back(c->p0); // selectable[0] = p0
        selectable_points.push_back(c->p1);
        selectable_points.push_back(c->p2);
    }
}

void Window::populate_anchors() {
    anchors.push_back(p0);
    anchors.push_back(p3);
    anchors.push_back(p6);
    anchors.push_back(p9);
    anchors.push_back(p12);
    anchors.push_back(p15);
    anchors.push_back(p18);
    anchors.push_back(p21);
    anchors.push_back(p24);
    anchors.push_back(p27);
}

void Window::populate_controls() {
    controls.push_back(p2);
    controls.push_back(p4);
    controls.push_back(p5);
    controls.push_back(p7);
    controls.push_back(p8);
    controls.push_back(p10);
    controls.push_back(p11);
    controls.push_back(p13);
    controls.push_back(p14);
    controls.push_back(p16);
    controls.push_back(p17);
    controls.push_back(p19);
    controls.push_back(p20);
    controls.push_back(p22);
    controls.push_back(p23);
    controls.push_back(p25);
    controls.push_back(p26);
    controls.push_back(p28);
    controls.push_back(p1);
    controls.push_back(p29);
}

void Window::drawLines(GLuint shaderProgram) {

    glGenVertexArrays(1, &pointVAO); // below from these lines are for binding control points data
    glGenBuffers(1, &pointVBO);
    
    glBindVertexArray(pointVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
//    glBufferData(GL_ARRAY_BUFFER, controls.size() * sizeof(glm::vec3), controls.data(), GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, controls.size() * sizeof(GLfloat) * 3, controls.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // 6 * sizeof(float)
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    //////////////////////
    
    // Calculate the combination of the model and view (camera inverse) matrices
    glm::mat4 modelview = Window::V * glm::mat4(1.0f);
    glm::mat4 toWorld = glm::mat4(1.0f);
    
    // Now send these values to the shader program
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &P[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelview"), 1, GL_FALSE, &modelview[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &toWorld[0][0]);
    
    // Now draw the cube. We simply need to bind the VAO associated with it.
    glBindVertexArray(pointVAO);
    // Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
    glDrawArrays(GL_LINES, 0, (GLsizei)controls.size());
    
    // Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
    glBindVertexArray(0);
}

void Window::display_callback(GLFWwindow* window)
{
    
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram_skybox);
    skybox->draw(shaderProgram_skybox);

    // Use the shader of programID
    glUseProgram(shaderProgram_curve);
    // Render the object
    for (Curve * c: curves) {
        c->draw(shaderProgram_curve);
    }
    
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    glUseProgram(shaderProgram_color);
    // draw anchor and control points
    for (int i = 0; i < curves.size(); i++) {;
        glUniform3f(glGetUniformLocation(shaderProgram_color, "color"), 1.0f, 0.0f, 0.0f); // or 255.0f
        for (glm::vec3 anchor: curves[i]->anchor_points) {
            M[3] = glm::vec4(anchor, 1.0f);
            sphere->draw(shaderProgram_color, M);
        }
        glUniform3f(glGetUniformLocation(shaderProgram_color, "color"), 0.0f, 1.0f, 0.0f); // or 255.0f
        for (glm::vec3 control: curves[i]->control_points) {
            M[3] = glm::vec4(control, 1.0f);
            sphere->draw(shaderProgram_color, M);
        }
    }
    // draw handles
    glUniform3f(glGetUniformLocation(shaderProgram_color, "color"), 1.0f, 1.0f, 0.0f);
    drawLines(shaderProgram_color);
    
    // Draw the sphere using envrionment mapping
    glUseProgram(shaderProgram_reflect);
    glUniform3f(glGetUniformLocation(shaderProgram_reflect, "cameraPos"), cam_pos.x, cam_pos.y, cam_pos.z);
    sphere->draw(shaderProgram_reflect, matrix);
    
    if (index != -1) {
        if (MOVE_LEFT || MOVE_RIGHT) {
            glm::vec3 temp = selectable_points[index];
            selectable_points[index] = glm::vec3(temp.x + (xpos - click_xpos)*0.0003f, temp.y, temp.z);
//            recalculate_points();
//            recalculate_continuity();
        }
        if (MOVE_UP || MOVE_DOWN) {
            glm::vec3 temp = selectable_points[index];
            selectable_points[index] = glm::vec3(temp.x, temp.y + (click_ypos - ypos)*0.0003f, temp.z);
//            recalculate_points();
//            recalculate_continuity();
        }
        
        recalculate_points();
        recalculate_continuity(); // TODO debug
        
        anchors.clear();
        populate_anchors();
        
        controls.clear();
        populate_controls();
        
        
        curves.clear();
        define_curves();
        populate_curves();
        
        selectable_points.clear();
        populate_selectables();
     
    }
    
    glUseProgram(shaderProgram_color);
    glUniform3f(glGetUniformLocation(shaderProgram_color, "color"), 1.0f, 1.0f, 0.0f);
    drawLines(shaderProgram_color);
    // Swap buffers
    glfwSwapBuffers(window);
    // Gets events, including input such as keyboard and mouse or window resizing
    glfwPollEvents();
//    glfwSwapBuffers(window);
}

void Window::recalculate_continuity() {
    p4 = glm::vec3(p3 - p2 + p3);
    p7 = glm::vec3(p6 - p5 + p6);
    p10 = glm::vec3(p9 - p8 + p9);
    p13 = glm::vec3(p12 - p11 + p12);
    p16 = glm::vec3(p15 - p14 + p15);
    p19 = glm::vec3(p18 - p17 + p18);
    p22 = glm::vec3(p21 - p20 + p21);
    p25 = glm::vec3(p24 - p23 + p24);
    p28 = glm::vec3(p27 - p26 + p27);
    p29 = glm::vec3(p0 - p1 + p0);
}

void Window::recalculate_points() {
    int k = 0;
    p0 = selectable_points[k];
    k++;
    p1 = selectable_points[k];
    k++;
    p2 = selectable_points[k];
    k++;
    p3 = selectable_points[k];
    k++;
    p4 = selectable_points[k];
//    p4 = glm::vec3(p3 - p2 + p3);
    k++;
    p5 = selectable_points[k];
    k++;
    p6 = selectable_points[k];
    k++;
    p7 = selectable_points[k];
    k++;
    p8 = selectable_points[k];
    k++;
    p9 = selectable_points[k];
    k++;
    p10 = selectable_points[k];
    k++;
    p11 = selectable_points[k];
    k++;
    p12 = selectable_points[k];
    k++;
    p13 = selectable_points[k];
    k++;
    p14 = selectable_points[k];
    k++;
    p15 = selectable_points[k];
    k++;
    p16 = selectable_points[k];
    k++;
    p17 = selectable_points[k];
    k++;
    p18 = selectable_points[k];
    k++;
    p19 = selectable_points[k];
    k++;
    p20 = selectable_points[k];
    k++;
    p21 = selectable_points[k];
    k++;
    p22 = selectable_points[k];
    k++;
    p23 = selectable_points[k];
    k++;
    p24 = selectable_points[k];
    k++;
    p25 = selectable_points[k];
    k++;
    p26 = selectable_points[k];
    k++;
    p27 = selectable_points[k];
    k++;
    p28 = selectable_points[k];
    k++;
    p29 = selectable_points[k];
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    
    if (action == GLFW_PRESS) {
        
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT: {
                POINT_INTERACTION = true;
                
                glfwGetCursorPos(window, &click_xpos, &click_ypos); // get current mouse click position
                index = processSelection((int)click_xpos, (int)click_ypos); // unsigned int to int; index can't be -1
                
                break;
            }
            case GLFW_MOUSE_BUTTON_RIGHT: {
                CAMERA_ROTATE = true;
                
                break;
            }
                
            default: {
                break;
            }
        }
    }
    if (action == GLFW_RELEASE) {
        POINT_INTERACTION = false;
        CAMERA_ROTATE = false;
        glfwGetCursorPos(window, &xpos, &ypos); // cursor position when mouse is released

//        if (xpos - click_xpos < 0) MOVE_LEFT = true;
//        else MOVE_LEFT = false;
        MOVE_LEFT = false;
        MOVE_RIGHT = false;
        MOVE_UP = false;
        MOVE_DOWN = false;
        if (xpos - click_xpos < 0) MOVE_LEFT = true;
        else if (xpos - click_xpos > 0) MOVE_RIGHT = true;
        if (ypos - click_ypos < 0) MOVE_UP = true;
        else if (ypos - click_ypos > 0) MOVE_DOWN = true;
    }
}

//void Window::processSelection(int xx, int yy) {
unsigned int Window::processSelection(int xx, int yy) {
    unsigned char res[4];
    GLint viewport[4];
    
    renderSelection();
    
    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(xx*2, viewport[3] - yy*2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);
  
    unsigned int index = (unsigned int)(res[0]-1); // index of selected point; 6 for p6
    
    switch((unsigned int)res[0]-1) {
        default: printf("Picked p%d\n", res[0]-1); break;
    }
    
    return index;
}

void Window::renderSelection() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // use the selection shader
    glUseProgram(shaderProgram_select);
    
    unsigned int id = 0;
//    glm::mat4 M = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f));
    glm::mat4 M = glm::mat4(1.0f);
    for (glm::vec3 point: selectable_points) {
        glUniform1ui(glGetUniformLocation(shaderProgram_select, "code"), ++id);
        M[3] = glm::vec4(point, 1.0f);
        sphere->draw(shaderProgram_select, M);
    }
    
    // Render everything else as 0
    glUniform1ui(glGetUniformLocation(shaderProgram_select, "code"), 0);
    skybox->draw(shaderProgram_select);
    drawLines(shaderProgram_select);
    for (Curve* c: curves) {
        c->draw(shaderProgram_select);
    }
    
    //don't swap buffers
    //glutSwapBuffers();
    
    // restore clear color if needed
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Check for a key press
    if (action == GLFW_PRESS)
    {
        // Check if escape was pressed
        if (key == GLFW_KEY_ESCAPE)
        {
            // Close the window. This causes the program to also terminate.
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        
        switch (key) {
            case GLFW_KEY_M: // 'M' key pauses/unpauses sphere movement
                if (SPHERE_MOVE) SPHERE_MOVE = false;
                else SPHERE_MOVE = true;
                break;
                
            case GLFW_KEY_H: // 'H' key automatically place the sphere at the highest point of track
                TO_HIGHEST_POINT = true;
                break;
                
            case GLFW_KEY_C: // rider's view action camera
                if (RIDERS_VIEW) RIDERS_VIEW = false;
                else RIDERS_VIEW = true;
                break;
                
            default:
                break;
        }
    }
}

void Window::idle_callback()
{    
    skybox->toWorld = glm::translate(glm::mat4(1.0f), cam_pos); // so scene won't move when we zoom in/out robots
    
    // Get the highest point on all curves
    float tempY = numeric_limits<float>::min();
    for (Curve * c: curves) {
        for (glm::vec3 tempPoint: c->points_on_curve) {
            if (tempPoint.y > tempY) {
                tempY = tempPoint.y;
                highestPoint = tempPoint;
            }
        }
    }
    if (SPHERE_MOVE) update();
    
    if (TO_HIGHEST_POINT) {
        countT = 0.0f;
        countP = 0;
        countC = 0;
        TO_HIGHEST_POINT = false;
    }
    
//    if (RIDERS_VIEW) {
//        cam_pos = matrix[3]/matrix[3].w;
//        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
//    } else {
//        cam_pos = glm::vec3(-15.0f, -5.0f, 20.0f);
//    }
//    V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    
}

// apply sphere movement physics here
void Window::update() {
//    // First make the sphere move along curve without implementing physics
//    Curve * tempCurve = curves.at(countC);
//    glm::vec3 tempPoint = tempCurve->points_on_curve.at(countT);
//    matrix[3] = glm::vec4(tempPoint, 1.0f);
//    countT++;
//    if (countT == 151) {
//        countT = 0;
//        countC++;
//    }
//    if (countC == 10) countC = 0;

    
    if (TO_HIGHEST_POINT) {
        countT = 0.0f;
        countP = 0;
        countC = 0;
        TO_HIGHEST_POINT = false;
    }
    
    float v = velocityAt(matrix[3][1]);
    Curve* tempCurve = curves.at(countC);
    glm::mat4 B = tempCurve->B;
    glm::mat4 G = tempCurve->G;
    
    if (countT + v <= 1.0f) {
        countT = countP/150.0f + v;
        glm::vec4 T = glm::vec4(pow(countT, 3.0f), pow(countT, 2.0f), countT, 1.0f);
        glm::vec4 q = G * B * T;
        glm::vec4 tempPoint = q;
        matrix[3] = tempPoint;
        countP++;
    } else {
        countT -= 1.0f;
        countP = 0;
        countC++;
    }
    if (countC > 9) countC = 0;
    
//    cout << "v: " << v << ", " << "countP: " << countP << ", " << "countC: " << countC << endl;
//    cout << "v is: " << v << " at height: " << matrix[3][1] << endl; // the lower the sphere is the faster it goes
}

float Window::velocityAt(float currentHeight) {
    float v = 0.0f;
    float a = 0.00001f; // try different values
    float maxHeight = highestPoint.y;
    float deltaH = currentHeight - maxHeight;
    float c = 0.008f; // try different values
    
    cout << "currentHeight: " << currentHeight << ", " << "maxHeight: " << maxHeight << endl;
    
    v = (float)sqrt(-2.0f * a * deltaH) + c;;
    return v;
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
    delete(skybox);
    delete(sphere);
    for (Curve * c: curves) {
        delete(c);
    }
    // delete all other objects
    glDeleteProgram(shaderProgram_curve);
    glDeleteProgram(shaderProgram_skybox);
    // delete all other shaders
    glDeleteProgram(shaderProgram_reflect);
    glDeleteProgram(shaderProgram_select);
    glDeleteProgram(shaderProgram_obj);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);
	// Set swap interval to 1
	glfwSwapInterval(1);
	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);
	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;

	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
//        P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
        P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 3000.0f);
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

// Map 2D cursor position to 3D; do not change this method
glm::vec3 Window::trackBallMapping(GLFWwindow* window, double xpos, double ypos) {
    glm::vec3 v;
    float d;
    int w = Window::width;
    int h = Window::height;
    
    v.x = (2.0 * xpos - w)/w;
    v.y = (h - 2.0 * ypos)/h;
    v.z = 0.0;
    d = glm::length(v);
    d = (d < 1) ? d : 1.0; // if d is smaller than 1, set d to 1
    v.z = sqrtf(1.0001 - d*d); // or pow(d, 2.0)
    v = glm::normalize(v);
    return v;
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

    A = trackBallMapping(window, OLD_XPOS, OLD_YPOS);
    B = trackBallMapping(window, xpos, ypos);

    if (A == B) {
        return;
    }
    
    float velocity = length(B-A);
    if (velocity < 0.0001) return;
    
    angle = velocity;
    axis = glm::cross(A, B);

    if (CAMERA_ROTATE) {
        glm::mat3 R = glm::mat3(glm::rotate(glm::mat4(1.0f), angle*50/180 * glm::pi<float>(), axis));
        cam_pos = R * cam_pos;
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
    
    OLD_XPOS = xpos;
    OLD_YPOS = ypos;
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    scrollY += yoffset;
    if (yoffset > 0) cam_pos = 0.9f * cam_pos;
    if (yoffset < 0) cam_pos = 1.1f * cam_pos;
    V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    scrollY = 0.0;
}



