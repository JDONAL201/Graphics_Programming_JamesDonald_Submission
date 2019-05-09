#include "Shader.h"



Shader::Shader()
{
	shaderID = 0;
}
void Shader::createShader(const std::string& shaderVert, const std::string& shaderFrag,const std::string& shaderGeom)
{
	shaderID = glCreateProgram();														// create a shader program

	shaders[0] = addShader(createShaderFromFile(shaderVert), GL_VERTEX_SHADER);		// load two shaders change file to point to shader. and define the type of shader
	shaders[1] = addShader(createShaderFromFile(shaderFrag), GL_FRAGMENT_SHADER);

	if(!shaderGeom.empty())
	shaders[2] = addShader(createShaderFromFile(shaderGeom), GL_GEOMETRY_SHADER);
	
	for (int i = 0; i < NUMBER_OF_SHADERS; i++) // for loop to iterate through the shaders and attach to shader program
	{
		glAttachShader(shaderID, shaders[i]); // attach the shader to the program
	}
	glBindAttribLocation(shaderID, 0, "position"); //bind the attribute location 
	glBindAttribLocation(shaderID, 1, "texCoord"); //bind the texture attribute.
	glBindAttribLocation(shaderID, 2, "normal");

	glLinkProgram(shaderID); //link the program to run on vertex processor 															// link the program to the shader id																//link the program
	shaderErrorCheck(shaderID, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // check linked properly

	glValidateProgram(shaderID);															 // validate the shader program make sure can be excuted in opengl state
	shaderErrorCheck(shaderID, GL_VALIDATE_STATUS, true, "Error:Shader program not valid "); // check validation of shader program

}
GLuint Shader::addShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << type << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	shaderErrorCheck(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

std::string Shader::createShaderFromFile(const std::string& fileName) // load shader from file.
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}
void Shader::shaderErrorCheck(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << " : " << " " << std::endl;
	}
}
void Shader::useShader() 
{
	glUseProgram(shaderID);
}

Shader::~Shader()
{
	for (int i = 0; i < NUMBER_OF_SHADERS; i++)// iterate through the shaders
	{
		glDetachShader(shaderID, shaders[i]);// detach the shader from the program
		glDeleteShader(shaders[i]);	// delete the shader once detached from program

	}
	glDeleteProgram(shaderID);							// delete the program once all shaders have been detached and deleted
}
