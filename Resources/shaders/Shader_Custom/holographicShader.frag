#version 330 core

uniform vec4 holoColor;
uniform float time;

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 viewDirection;
in vec2 texCoords;
in float effectDirection;

//TEXTURED
uniform sampler2D useTexture;

uniform float alphaIntensity;

//BARS
uniform float scanSpeed;
uniform float scanSpace;

//FLICKER
uniform float flickerSpeed;

//RIM
uniform vec4 rimGlowColor;
uniform float rimInensity;

//GLOW
uniform float glowSpeed;
uniform float glowSpace;

float noise(float x)
{
    float a = floor(x);
    float b = fract(x);
    return mix(fract(sin(a) * 43758.5453123), fract(sin(a+1.0) * 43758.5453123), b);
}
void main()
{
	//texture
	vec4 textureColor = vec4(1.0);
	textureColor = texture2D(useTexture,texCoords);

	//scanning effect
	float scanningBars = 0.0;
	float scrolling = time * scanSpeed + effectDirection * scanSpace;
	scanningBars = step(scrolling - floor(scrolling),0.5)*0.65;

	//alpha
	float alpha = 1.0;
	alpha = alphaIntensity;
	
	//Flickering
	float flicker = 1.0;
	flicker = clamp(noise(time * flickerSpeed),0.65,1.0);

	//Rim lit
	float rim = 1.0;
	vec4 rimColor = vec4(0.0);
	rim = 1.0 - clamp(dot(viewDirection,worldNormal),0.0,1.0);
	rimColor = rimGlowColor * pow(rim, rimInensity);

	//Glowing
	float glow = 0.0;
	float tempGlow = effectDirection * glowSpace - time * glowSpeed;
	glow = tempGlow - floor(tempGlow);
		
	vec4 color =  textureColor * holoColor  + (glow * 1.0 * rimColor);
	color *= alpha * (scanningBars + rim + glow )* flicker;
			
	gl_FragColor = color;
}
