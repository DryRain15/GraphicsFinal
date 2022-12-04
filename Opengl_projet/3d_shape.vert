#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 transformation;
uniform vec3 color;

varying float depth;

out vec3 FragPos;
out vec3 Normal;
out vec3 originalColor;

void main()
{
     gl_Position =  projection * view * transformation * vec4(aPos, 1.0);
     depth = gl_Position.z;
     FragPos = aPos;
     Normal = mat3(transpose(inverse(transformation))) * normal;
     originalColor = color;
} 