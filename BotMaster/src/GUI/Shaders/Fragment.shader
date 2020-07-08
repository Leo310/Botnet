#version 330 core

out vec4 FragColor;
in vec3 ourColor;

uniform float u_Opacity;

void main()
{
   FragColor = vec4(ourColor, u_Opacity);
};