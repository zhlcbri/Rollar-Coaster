#version 330 core

uniform uint code;

//uniform int anchor; // 1 if drawing anchor points (red)
//uniform int control; // 1 if drawing control points (green)

out vec4 outputF;

void main()
{
    outputF = vec4(code/255.0f, 0.0f, 0.0f, 0.0f);
    
//    if (anchor == 1) outputF = vec4(code/1.0f, 0.0f, 0.0f, 0.0f); // code/255.0f will give black sphere
//    else if (control == 1) outputF = vec4(0.0f, code/1.0f, 0.0f, 0.0f);
}








