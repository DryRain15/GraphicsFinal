#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 transformation;
uniform vec3 color;

out vec3 FragPos;
out vec3 originalColor;

void main()
{
     gl_Position = transformation * vec4(aPos, 1.0);
     FragPos = aPos;
     originalColor = color;
} 