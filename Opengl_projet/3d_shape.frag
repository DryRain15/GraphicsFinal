#version 330 core
in vec3 FragPos;
in vec3 originalColor;
in vec3 Normal;

out vec4 FragColor;

uniform float znear, zfar;
varying float depth; 

//uniform vec3 viewPos;
uniform vec3 lightPosition;
uniform float ambient;
uniform float diffuse;
uniform vec3 lightColor;

void main() {
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	float z = (depth - znear) / (zfar - znear);
	gl_FragDepth = z;
	FragColor = vec4(originalColor * (ambient + diff) * lightColor, 1.0);
}