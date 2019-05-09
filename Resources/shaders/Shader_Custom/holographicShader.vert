#version 330 core

layout (location = 0) in vec3 inputPosition;
layout (location = 1) in vec2 inputTexCoords;
layout (location = 2) in vec3 inputNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

uniform float time;
uniform vec3 camPos;

//Glitching
uniform float glitchSpeed;
uniform float glitchIntensity;

//effect direction
uniform vec3 dir;


out vec3 worldPosition;
out vec3 worldNormal;
out vec3 viewDirection;
out vec2 texCoords;
out float effectDirection;

void main()
{
	worldPosition = (model* vec4(inputPosition,1.0)).xyz;
	texCoords = inputTexCoords;
	worldNormal = normalize(normalMatrix * inputNormal);

	viewDirection = normalize(camPos - worldPosition); 
	worldPosition.x += glitchIntensity * step(0.5,sin(time*2.0 + inputPosition.y *1.0))*step(0.99,sin(time * glitchSpeed * 0.5));
	effectDirection = dir.x * worldPosition.x + dir.y * worldPosition.y + dir.z * worldPosition.z;


	gl_Position =projection*view* vec4(worldPosition,1.0);
}