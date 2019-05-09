#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;


varying vec2 texCoord0;
varying vec3 Normal;


uniform mat4 transform;

uniform mat4 model;															  
uniform mat4 projection;
uniform mat4 view;	

void main()
{

	texCoord0 = texCoord;

	Normal = mat3(transpose(inverse(model))) * normal; 
	gl_Position = projection * view * model * vec4(position, 1.0);


};
