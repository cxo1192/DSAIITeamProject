#include "Ship.h"



Ship::Ship()
{
	m_fAngle = 0.0f;
	m_fSpeed = 0.0f;
	m_v3Position = vector3(0.0f);
}

Ship::Ship(vector3 a_v3Pos) {
	m_fAngle = 0.0f;
	m_fSpeed = 0.0f;
	m_v3Position = a_v3Pos;
}

Ship::~Ship()
{
}

void Ship::Update() {
	//update forward vector based on m_fAngle
	m_v3Position.z = 0.0f; //keep ship on the XY plane
	m4Rotate *= glm::rotate(float(m_fAngle*PI/180.0f), vector3(0.0f, 0.0f, 1.0f));
}

void Ship::Display() {
	//get projection matrix
	//get view matrix
	//matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	//matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//apply render list
	//m_pMesh->Render(m4Projection, m4View, m4Translate * m4Rotate);
}

void Ship::MoveForward() {
	m_fSpeed += SPEED_INCREMENT;
	m_v3Position += (m_v3Forward * m_fSpeed);
}

void Ship::MoveBackward() {
	m_v3Position -= (m_v3Forward * m_fSpeed);
}

void Ship::TurnRight() {
	m_fAngle += ANGLE_INCREMENT;

	//check radians vs degrees
	//update forward vector
	m_v3Forward = vector3(glm::acos(m_fAngle), glm::asin(m_fAngle), 0.0f);
}

void Ship::TurnLeft() {
	m_fAngle -= ANGLE_INCREMENT;

	//check radians vs degrees
	//update forward vector
	m_v3Forward = vector3(glm::acos(m_fAngle), glm::asin(m_fAngle), 0.0f);
}
