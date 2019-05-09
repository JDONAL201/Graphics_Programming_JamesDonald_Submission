#pragma once
#include <fstream>
#include<iostream>
#include <string>
#include <GL\glew.h>
#include "Transform.h"
#include "Camera.h"


#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
class Shader
{
public:
	Shader();
	
	void createShader(const std::string& shaderVert,const std::string& shaderFrag, const std::string& shaderGeo); // INITIALISE THE SHADER AND CREATE SHADER PROGRAM
	GLuint addShader(const std::string& text, unsigned int type); // ADD A SHADER TO SHADERS BY CALLING CREATE SHADER FROM FILE.
	std::string createShaderFromFile(const std::string& fileName);// RETURN THE SHADER FROM FILE

	void useShader(); // WHEN WANT TO USE SHADER
	

	void shaderErrorCheck(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage); // error handling for shader



#pragma region unifrom setters
	// ------------------------------------------------------------------------
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);

		//if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);

	if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}

#pragma endregion

	
	
	~Shader();

private:
	
	static const unsigned int NUMBER_OF_SHADERS = 3; // HOW MANY SHADERS


	GLuint shaderID;// , uniformTransform, uniformProjection, uniformModel, uniformView, uniformAmbientColour, uniformAmbientIntensity, uniformDiffuseIntensity, uniformDirection, uniformDiffuseColour; // UNSIGNED INTS USED FOR THE LOCATION OF UNIFORMS 
	GLuint shaders[NUMBER_OF_SHADERS];//NUMBER OF SHADERS ARRAY

};

