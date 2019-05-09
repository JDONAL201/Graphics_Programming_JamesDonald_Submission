#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL/SDL.h>


struct Camera
{
public:

Camera(){}
float yaw; // rotate on y
glm::vec3 forward;
	Camera(const glm::vec3& pos, glm::vec3 startUp, float fov, float aspect, float nearClip, float farClip, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed)
	{
		//POSITION
		position = pos; // set pos
		forward = glm::vec3(0.0f, 0.0f, 1.0f);//set forward dir
		worldUp = startUp; // set world space up

		//PROJECTION
		projection = glm::perspective(fov, aspect, nearClip, farClip); // set the projection matrix

		//ROTATION
		yaw = startYaw; // set starting yaw
		pitch = startPitch; // set starting pitch

		moveSpeed = startMoveSpeed; // set move speed
		rotateSpeed = startTurnSpeed; // set rotate speed

		updateCamera(); 
	}


	void updateCamera()
	{
		forward.x = cos(glm::radians(yaw))* cos(glm::radians(pitch));  // update forward to be relative to the pitch and yaw.
		forward.y = sin(glm::radians(pitch));
		forward.z = sin(glm::radians(yaw))* cos(glm::radians(pitch));
		forward = glm::normalize(forward); // normalise to obtain a unit vector in the forward direction

		right = glm::normalize(glm::cross(forward, worldUp));					 // find the right angle , so right is always relative to world up
		up = glm::normalize(glm::cross(right, forward));					// up can change thus why is not used instead of worldSpace up above which will always be up in the world.

	}
	void cameraControl(float deltaTime, bool* key)
	{
		float velocity = moveSpeed * deltaTime; // multiply movespeed by delta time to obtain velocity

		if (key[SDLK_w] == true) // check if w is true
		{
			position += forward * velocity; //update camera position , move forward
		}

		if (key[SDLK_s] == true)
		{
			position -= forward * velocity; // move back
		}

		if (key[SDLK_a] == true)
		{
			position -= right * velocity; // move left
		}

		if (key[SDLK_d] == true)
		{
			position += right * velocity; // move right
		}
	}
	void mouseMotion(double xChange, double yChange)
	{
		xChange *= rotateSpeed; // multiply the amount to change by the rotation speed to turn smooth towards
		yChange *= rotateSpeed;

		yaw += xChange; // update the yaw to add the change in x
		pitch -= yChange; // update the pitch to minus the change in y

		if (pitch > 89.0f) // limit the pitch
		{
			pitch = 89.0f;
		}

		if (pitch < -89.0f) //limit the pitch
		{
			pitch = -89.0f;
		}

		updateCamera(); // update the new directons
	}

	inline glm::mat4 getView() const
	{
		return glm::lookAt(position, position + forward, up); // return the view matrix

	}
	inline glm::mat4 getProjection() const
	{
		return projection; // return the projection matrix
	}

	inline glm::vec3* getPos() { return &position; } //getters
	inline void setPos(glm::vec3 pos) { position = pos; }




protected:
private:
	glm::mat4 projection;
	glm::vec3 position;

	glm::vec3 up;
	glm::vec3 right;

	glm::vec3 worldUp;



	float pitch; // looking up and down

	float moveSpeed;
	float rotateSpeed;
};


