#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout(location = 2) in vec2 texPos;

out vec3 ourColor;
out vec2 TexCoords;

//uniform mat4 model;
//uniform mat4 projectionview;

void main()
{
    //projectionview * model * 
   gl_Position = vec4(aPos, 1.0);
   ourColor = aColor;
   TexCoords = texPos;
};