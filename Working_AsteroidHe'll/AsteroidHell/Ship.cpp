#include "Ship.h"
#include "AppClass.h"


Ship::Ship()
{
	m_fAngle = 0.0f;
	m_fSpeed = 0.2f;
	m_v3Position = vector3(0.0f, 1.0f, 0.0f);
	m_v3Forward = vector3(0.0f, 0.0f, 1.0f);
	m4Rotate = matrix4(0.0f);
}

Ship::Ship(Simplex::Model* a_model_ship)
{
	m_fAngle = 0.0f;
	m_fSpeed = 1.0f;
	m_v3Position = vector3(0.0f,1.0f,0.0f);
	m_v3Forward = vector3(0.0f, 0.0f, 1.0f);
	model_ship = a_model_ship;
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
	m4Rotate = glm::rotate(float(m_fAngle * PI/180), vector3(0.0f, 1.0f, 0.0f));
}

void Ship::Display() {
	model_ship->SetModelMatrix(glm::translate(m_v3Position)*m4Rotate);
	model_ship->AddToRenderList();
}

void Ship::MoveForward() {
	m_v3Position += (m_v3Forward * m_fSpeed);
}

void Ship::MoveBackward() {
	m_v3Position -= (m_v3Forward * m_fSpeed);
}

void Ship::MoveRight() {

}

void Ship::MoveLeft() {
	m_v3Position += m_v3Forward;
}

void Ship::TurnRight() {
	m_fAngle -= ANGLE_INCREMENT;
	SetForward();
}

void Ship::TurnLeft() {
	m_fAngle += ANGLE_INCREMENT;
	SetForward();
}

vector3 Ship::Position() {
	return m_v3Position;
}

matrix4 Ship::RotationMatrix() {
	return m4Rotate;
}

void Ship::SetForward() {
	m_v3Forward = vector3(cosf((m_fAngle * PI/180)), 0.0f, sinf((m_fAngle * PI/180)));
	m_v3Forward = glm::normalize(m_v3Forward);
}
