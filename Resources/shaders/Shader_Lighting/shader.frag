#version 330    

in vec2 texCoord0;
out vec4 colour;    
in vec3 Normal;


struct DirectionalLight
{
	 vec3 colour;
	 vec3 colourDiff;
	 float ambientIntensity;
	 vec3 direction;
	 float diffuseIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColour=vec4(directionalLight.colour,1.0f)*directionalLight.ambientIntensity;
	float diffuseFactor = max(dot(normalize(Normal),normalize(directionalLight.direction)),0.0f);
	vec4 diffuseColour = vec4(directionalLight.colourDiff,1.0f)*directionalLight.diffuseIntensity * diffuseFactor;
	colour = texture(theTexture, texCoord0)* ambientColour + diffuseColour;
	colour.a = 0.0;


};
