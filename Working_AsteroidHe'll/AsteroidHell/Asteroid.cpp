#include "Asteroid.h"

Asteroid::Asteroid()
{
	m_v3Position = vector3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), 0.0f); // assign a random position
	m_fSpeed = glm::linearRand(0.5f, 2.0f); // assign a random speed (ARBITRARY FOR NOW)
	m_fRotSpeed = glm::linearRand(-1.0f, 1.0f); // assign a random rotation speed (ARBITRARY FOR NOW)
	m_v3Direction = vector3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), 0.0f); // assign a random direction (WILL BE UNIT VECTOR)
}

Asteroid::Asteroid(vector3 position)
{
	m_v3Position = position; // set starting position
	m_fSpeed = glm::linearRand(0.5f, 2.0f); // assign a random speed (ARBITRARY FOR NOW)
	m_fRotSpeed = glm::linearRand(-1.0f, 1.0f); // assign a random rotation speed (ARBITRARY FOR NOW)
	m_v3Direction = vector3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), 0.0f); // assign a random vector (WILL BE UNIT VECTOR)
}

Asteroid::Asteroid(float speed, float rotSpeed, vector3 direction, vector3 position)
{
	m_fSpeed = speed; // set speed
	m_fRotSpeed = rotSpeed; // set rotation speed
	m_v3Direction = direction; // set "forward" direction
	m_v3Position = position; // set starting position
}

void Asteroid::RandomPos()
{
	m_v3Position = vector3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), 0.0f); // assign a random position (FILLER RANDOM POSITION)
}

void Asteroid::Update()
{
	// move the asteroid in it's current direction at it's current speed
	m_v3Position += m_v3Direction * m_fSpeed;
}

void Asteroid::Display()
{
	// draw asteroid sprite
}

void Asteroid::Release(void)
{
}


Asteroid::~Asteroid()
{
	
}
