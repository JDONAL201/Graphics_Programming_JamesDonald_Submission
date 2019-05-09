#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 2) in vec3 inNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;


void main()
{
	Normal = normalize(normalMatrix * inNormal);;

	Position = vec3(model * vec4(inPos, 1.0));
    gl_Position = projection * view * model * vec4(inPos, 1.0);

}