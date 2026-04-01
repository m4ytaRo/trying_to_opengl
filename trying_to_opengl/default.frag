#version 330 core

in vec3 color;

in vec2 texCoord;

uniform sampler2D tex0;

out vec4 FragColor;
void main()
{
   FragColor = texture(tex0, texCoord) * vec4(color, 1.0);;
};