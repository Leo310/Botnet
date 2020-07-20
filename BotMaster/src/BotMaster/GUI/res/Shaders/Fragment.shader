#version 330 core

in vec3 ourColor;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D u_Texture1;
//uniform sampler2D u_Texture2;

void main()
{
    FragColor = texture(u_Texture1, TexCoords) * vec4(ourColor, 1.0f);
  //FragColor = vec4(1.0f, 0.5f, 1.0f, 1.0);

};