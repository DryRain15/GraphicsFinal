#version 330 core
in vec3 originalColor;
out vec4 FragColor;

void main() {
	FragColor = vec4(originalColor, 1.0);
}