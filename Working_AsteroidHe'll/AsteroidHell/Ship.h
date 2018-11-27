#pragma once
#include "Definitions.h"

class Ship
{
	float m_fSpeed = 0.0f; //speed the ship is moving
	vector3 m_v3Direction = vector3(0.0f); //a normalized vector that stores the direction of travel
	vector3 m_v3Position = vector3(0.0f); //the position of the ship in space
	//will need some sort of sprite member
	//needs a rigidbody member
public:
	Ship();
	//parameterized constuctor needed
	//need update
	//need display\
	//need methods that can be called from appclass.cpp that move the ship
	//need a method to destory the ship
	~Ship();
};

