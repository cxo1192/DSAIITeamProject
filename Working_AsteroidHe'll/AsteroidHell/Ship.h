#pragma once
#include "Definitions.h"

using namespace Simplex;

class Ship
{
	float m_fSpeed = 0.0f; //speed the ship is moving
	vector3 m_v3Position = vector3(0.0f); //the position of the ship in space
	vector3 m_v3Forward = vector3(0.0f); //normalized vector to store the direction
	float m_fAngle = 0.0f;
	const float ANGLE_INCREMENT = 1.0f;
	const float MAX_SPEED = 5.0f;
	const float SPEED_INCREMENT = 1.0f;
	matrix4 m4Translate = matrix4(0.0f);
	matrix4 m4Rotate = matrix4(0.0f);
	//will need some sort of sprite member
	//needs a rigidbody member
public:
	Ship();
	Ship(vector3 a_fPos);
	//parameterized constuctor needed
	//need update
	void Update();
	//need display
	void Display();
	//need methods that can be called from appclass.cpp to move the ship
	//need a method to destroy the ship
	~Ship();
	void MoveForward();
	void MoveBackward();
	void TurnRight();
	void TurnLeft();
};

