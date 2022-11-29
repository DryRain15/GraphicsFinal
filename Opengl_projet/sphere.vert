#version 330 core
// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * vec4(vertexPosition_modelspace, 1);
}