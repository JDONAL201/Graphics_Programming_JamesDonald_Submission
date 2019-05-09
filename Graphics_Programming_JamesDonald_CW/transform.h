#pragma once
#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos; // set the starting position
		this->rot = rot;//set the starting rotation
		this->scale = scale; // set the starting scale

	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(pos);								// the position matrix
		glm::mat4 scaleMat = glm::scale(scale);									//the scale matrix
		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));			 // rotation matrix X
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));		// rotation matix Y
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));		//rotation matrix Z
		glm::mat4 rotMat = rotX * rotY * rotZ;									// combine by multiplying to give the rotation matrix

		return posMat * rotMat * scaleMat;												// return the model matrix by multiplying all three transform matrices in order.
	}

	void moveForward(float speed)
	{
		pos.z += speed; // will move the object forward (world space)
	}
	void moveRight(float speed)
	{

		pos.x += speed; // move object right(world space)
	}
	void rotateOnY(float speed)
	{
		rot.y += speed; // rotate on the spot by speed

	}

	inline glm::vec3* GetPos() { return &pos; } //getters , return the position
	inline glm::vec3* GetRot() { return &rot; } // return current rotation
	inline glm::vec3* GetScale() { return &scale; } // return current scale

	inline void SetPos(glm::vec3 pos) { this->pos = pos; } // setters , set to new position
	inline void SetRot(glm::vec3 rot) { this->rot = rot; }// set to new rotation
	inline void SetScale(glm::vec3 scale) { this->scale = scale; } // set to new scale





protected:
private:
	glm::vec3 pos; // vector 3 to hold position
	glm::vec3 rot;// vec 3 for the rotation
	glm::vec3 scale; // vec3 for the scale
};


