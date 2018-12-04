#pragma once
#include "Definitions.h"
#include "Ship.h"
using namespace Simplex;

class Asteroid
{
	Simplex::Model* m_pMyModel = nullptr;
	//MyRigidBody *m_pMyRB = nullptr;

	
	float m_fRotSpeed = 0.0f; //speed the asteroid rotates in space, need to be in radians
	float m_fYRotaton = 0.0f; //current rotation on the y axis
	vector3 m_v3Direction = vector3(0.0f); //a normalized vector that stores the direction of travel
	
	float minZ = 7; //for keeping the asteroids on screen should use screen size in the future
	float maxZ = -7;
	float minX = -25.5f;
	float maxX = 25.5f;
	

	
public:
	float m_fCollisionRadius = 0.45f;
	std::vector<Asteroid*> collisionList;

	float m_fSpeed = 0.0f; //speed the asteroid moves through space
	vector3 m_v3Position = vector3(0.0f); //the position of the asteroid in space

	bool ShipCollision(Ship* other);//checks if this asteroid is colliding with the ship
	bool AsteroidCollision(Asteroid* other); //checks if this asteroid is colliding with another, adds the other to this ones list of collisions

	vector3 Position();
	Asteroid();
	Asteroid(vector3 position); //constructor with just the position
	Asteroid(float speed, float rotSpeed, vector3 direction, vector3 position); //parameterized constructor with all movement stuff
	vector3 RandomUnitVec3(); //returns a random unit vector on the xz-plane
	void Update(); //moves the asteroid based on speed, direction, and location
	void Display(); //should do whatever it needs to display the asteroid
	void Release(void); //used for SafeDelete() to work or something
	~Asteroid(); //call release
};

