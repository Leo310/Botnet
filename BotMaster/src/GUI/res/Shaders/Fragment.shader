#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform float u_Opacity;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float visibility;

void main()
{
   FragColor = mix(texture(texture1, TexCoord) * vec4(ourColor, u_Opacity), texture(texture2, vec2(-TexCoord.x, TexCoord.y)), visibility);
   //FragColor = vec4(ourColor, u_Opacity);
};