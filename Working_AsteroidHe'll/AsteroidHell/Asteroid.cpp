#include "Asteroid.h"

bool Asteroid::ShipCollision(Ship * other)
{
	//return false; // remove this
	vector3 distance = m_v3Position - other->Position();
	distance.y = 0.0f;
	float dMag = glm::length(distance);
	if (dMag <= m_fCollisionRadius + other->m_fCollisionRadius) {
		std::cout << "COLLISION DETECTED" << std::endl;
		return true;
	}
	return false;
}

bool Asteroid::AsteroidCollision(Asteroid * other)
{
	vector3 distance = m_v3Position - other->Position();
	float dMag = glm::length(distance);
	if (dMag == 0.0f) {
		return false;
	}


	if (dMag < m_fCollisionRadius + other->m_fCollisionRadius) {
		//std::cout << "COLLISION DETECTED" << std::endl;
		collisionList.push_back(other);
		return true;
	}
	return false;
}

vector3 Asteroid::Position()
{
	return m_v3Position;
}

Asteroid::Asteroid()
{
	m_v3Position = vector3(0.0f); // assign a random position
	m_fSpeed = glm::linearRand(0.1f, 0.2f); // assign a random speed (ARBITRARY FOR NOW)
	m_fRotSpeed = glm::linearRand(-5.0f, 5.0f); // assign a random rotation speed (ARBITRARY FOR NOW)
	m_fYRotaton = glm::linearRand(-180.0f, 180.0f); // assign a random starting rotation
	m_v3Direction = RandomUnitVec3(); // assign a random direction
	//set the model
	m_pMyModel = new Simplex::Model();
	m_pMyModel->Load("Asteroid\\asteroid.obj");
}

Asteroid::Asteroid(vector3 position)
{
	m_v3Position = position; // set starting position
	m_fSpeed = glm::linearRand(0.05f, 0.15f); // assign a random speed (ARBITRARY FOR NOW) //0.05f
	m_fRotSpeed = glm::linearRand(-5.0f, 5.0f); // assign a random rotation speed (ARBITRARY FOR NOW)
	m_fYRotaton = glm::linearRand(-180.0f, 180.0f); // assign a random starting rotation
	m_v3Direction = RandomUnitVec3(); // assign a random vector

	//set the model
	m_pMyModel = new Simplex::Model();
	m_pMyModel->Load("Asteroid\\asteroid.obj");
}

Asteroid::Asteroid(float speed, float rotSpeed, vector3 direction, vector3 position)
{
	m_fSpeed = speed; // set speed
	m_fRotSpeed = rotSpeed; // set rotation speed
	m_v3Direction = direction; // set "forward" direction
	m_fYRotaton = glm::linearRand(-180.0f, 180.0f); // assign a random starting rotation
	m_v3Position = position; // set starting position

	//set the model
	m_pMyModel = new Simplex::Model();
	m_pMyModel->Load("Asteroid\\asteroid.obj");
}

vector3 Asteroid::RandomUnitVec3()
{
	vector3 v3 = vector3(glm::linearRand(-1.0f, 1.0f), 0.0f, glm::linearRand(-1.0f, 1.0f));
	float length = v3.length();

	return v3/length; // return unit vector (on the xz-plane)
}

void Asteroid::Update()
{

	if (collisionList.size() > 0) {
		for (uint i = 0; i < collisionList.size(); i++) {

			vector3 diffVect = (this->m_v3Position - collisionList[i]->m_v3Position);
			vector3 v3PointOfCollision = diffVect / 2.0f;
			vector3 v3Normal = v3PointOfCollision - collisionList[i]->m_v3Position;
			vector3 v3Tangent = vector3(v3Normal.z, 1.0f, v3Normal.x);



			//float slope = this->m_v3Position.y - collisionList[i]->m_v3Position.y / this->m_v3Position.x - collisionList[i]->m_v3Position.x;
			float angleOfDiff = glm::acos(glm::dot(diffVect, m_v3Direction) / (diffVect.length() * m_v3Direction.length()));

			if (/*glm::abs(slope < 1.0f)*/ (angleOfDiff * PI/180.0f) < 5.0f ) {
				this->m_v3Direction *= -1.0f;
				collisionList[i]->m_v3Direction *= -1.0f;
			}
			else {
				this->m_v3Direction = v3Normal;
				collisionList[i]->m_v3Direction = v3Tangent;
			}

			//normalize this
			float total = glm::sqrt((m_v3Direction.x * m_v3Direction.x) + (m_v3Direction.z * m_v3Direction.z));
			m_v3Direction.x /= total;
			m_v3Direction.z /= total;
			m_v3Direction.y = 0.0f;

			//normalize other
			total = glm::sqrt((collisionList[i]->m_v3Direction.x * collisionList[i]->m_v3Direction.x) + (collisionList[i]->m_v3Direction.z * collisionList[i]->m_v3Direction.z));
			collisionList[i]->m_v3Direction.x /= total;
			collisionList[i]->m_v3Direction.z /= total;
			collisionList[i]->m_v3Direction.y = 0.0f;

			//move this away from other
			this->m_v3Position += m_v3Direction * m_fSpeed;

			//clear the collision list
			collisionList[i]->collisionList.clear();
		}

	}
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
	m_fYRotaton += m_fRotSpeed;
	//std::cout << collisionList.size();
	Display();
}

void Asteroid::Display()
{
	// draw asteroid sprite
	m_pMyModel->SetModelMatrix(glm::translate(m_v3Position) * glm::rotate(IDENTITY_M4, glm::radians(m_fYRotaton), AXIS_Y) * glm::scale(vector3(0.5f)));

	m_pMyModel->AddToRenderList();
}

void Asteroid::Release(void)
{
}


Asteroid::~Asteroid()
{
	
}
