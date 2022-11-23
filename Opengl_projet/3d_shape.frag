#version 330 core
in vec3 originalColor;

out vec4 FragColor;

uniform float znear,zfar;
varying float depth; 

void main() {
	float z = (depth - znear) / (zfar - znear);
	gl_FragDepth = z;
	FragColor = vec4(originalColor, 1.0);
}