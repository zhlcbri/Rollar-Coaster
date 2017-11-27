#version 330 core

in vec3 fragNormal;
in vec3 objNormal;
in vec3 fragPos;
//in vec3 color;

uniform vec3 color; // different colors for different control/anchor points

out vec4 fragColor;

void main()
{
//    vec3 norm = (normalize(objNormal)+1.0f)/2.0f; // only for normal coloring
//    fragColor = vec4(norm, 1.0f); // normal coloring
    
//    vec3 color = vec3(0.2f, 1.0f, 0.7f);
    fragColor = vec4(color, 1.0f);
}








