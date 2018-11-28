#include "Asteroid.h"

Asteroid::Asteroid()
{
	m_v3Position = vector3(0.0f); // assign a random position
	m_fSpeed = glm::linearRand(0.05f, 0.2f); // assign a random speed (ARBITRARY FOR NOW)
	m_fRotSpeed = glm::linearRand(-1.0f, 1.0f); // assign a random rotation speed (ARBITRARY FOR NOW)
	m_v3Direction = RandomPos(); // assign a random direction (WILL BE UNIT VECTOR)

	//set the model
	m_pMyModel = new Simplex::Model();
	m_pMyModel->Load("Asteroid\\asteroid.obj");
}

Asteroid::Asteroid(vector3 position)
{
	m_v3Position = position; // set starting position
	m_fSpeed = glm::linearRand(0.1f, 0.3f); // assign a random speed (ARBITRARY FOR NOW)
	m_fRotSpeed = glm::linearRand(-1.0f, 1.0f); // assign a random rotation speed (ARBITRARY FOR NOW)
	m_v3Direction = RandomPos(); // assign a random vector (WILL BE UNIT VECTOR)

	//set the model
	m_pMyModel = new Simplex::Model();
	m_pMyModel->Load("Asteroid\\asteroid.obj");
}

Asteroid::Asteroid(float speed, float rotSpeed, vector3 direction, vector3 position)
{
	m_fSpeed = speed; // set speed
	m_fRotSpeed = rotSpeed; // set rotation speed
	m_v3Direction = direction; // set "forward" direction
	m_v3Position = position; // set starting position

	//set the model
	m_pMyModel = new Simplex::Model();
	m_pMyModel->Load("Asteroid\\asteroid.obj");
}

vector3 Asteroid::RandomPos()
{
	return vector3(glm::linearRand(-1.0f, 1.0f), 0.0f, glm::linearRand(-1.0f, 1.0f)); // assign a random position (FILLER RANDOM POSITION)
}

void Asteroid::Update()
{
	// move the asteroid in it's current direction at it's current speed
	/*if ((m_v3Position.x + m_v3Direction.x * m_fSpeed) >= maxX) {
		m_v3Direction.x *= -1.0f;
	}

	if ((m_v3Position.x + m_v3Direction.x * m_fSpeed) <= minX) {
		m_v3Direction.x *= -1.0f;
	}

	if ((m_v3Position.z + m_v3Direction.z * m_fSpeed) <= minZ) {
		m_v3Direction.z *= -1.0f;
	}

	if ((m_v3Position.z + m_v3Direction.z * m_fSpeed) >= maxZ) {
		m_v3Direction.z *= -1.0f;
	}*/
	if (m_v3Position.z < -11.0f) {
		m_v3Position.z = 11.0f;
	}
	else if (m_v3Position.z > 11.0f) {
		m_v3Position.z = -11.0f;
	}

	if (m_v3Position.x < -16.5f) {
		m_v3Position.x = 16.5f;
	}
	else if (m_v3Position.x > 16.5f) {
		m_v3Position.x = -16.5f;
	}
	m_v3Position += m_v3Direction * m_fSpeed;
	Display();
}

void Asteroid::Display()
{
	// draw asteroid sprite
	m_pMyModel->SetModelMatrix(glm::translate(m_v3Position));
	m_pMyModel->AddToRenderList();
}

void Asteroid::Release(void)
{
}


Asteroid::~Asteroid()
{
	
}
