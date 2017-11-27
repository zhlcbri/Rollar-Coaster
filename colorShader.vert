#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal; 

// Uniform variables can be updated by fetching their location and passing values to that location
uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 model; //toWorld

//uniform vec3 color; // different colors for different control/anchor points

//out vec3 color; //
out vec3 fragPos;
out vec3 fragNormal;
out vec3 objNormal;

void main()
{
    
    // OpenGL maintains the D matrix so you only need to multiply by P, V (aka C inverse), and M
    gl_Position = projection * modelview * vec4(position.x, position.y, position.z, 1.0);
    fragNormal = aNormal;
    fragNormal = mat3(transpose(inverse(model))) * aNormal;
    
    objNormal = aNormal;
    
    fragPos = vec3(model * vec4(position, 1.0)); // world space

}
