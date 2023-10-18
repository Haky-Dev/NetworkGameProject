#include "stdafx.h"
#include "Object.h"
#include <iostream>
#include <math.h>


Object::Object()
{
	m_isActive = false;
	m_type = ObjectType::TYPE_NORMAL;
	Initialize();
}
Object::Object(ObjectType type) : m_type(type)
{
	Initialize();
}
Object::~Object()
{
}

void Object::Initialize()
{
	m_position = Vector2d(0, 0);
	m_destination = Vector2d(0, 0);
	m_velocity = Vector2d(0, 0);
	m_acceleration = Vector2d(0, 0);
	m_volume = Vector2d(0, 0);
	m_color = Color(1.f, 1.f, 1.f, 1.f);

	m_mass = 1.0f;
	m_friction = 0.0f;
	m_currentTexIndex = 0;
	m_depth = 0;
}

void Object::SetPosition(Vector2d pos)
{
	m_position = pos;
}

void Object::SetPosition(float m_x, float m_y)
{
	m_position.m_x = m_x;
	m_position.m_y = m_y;
}

void Object::SetDestination(Vector2d des)
{
	m_destination = des;
}

void Object::SetDestination(float x, float y)
{
	m_destination.m_x = x;
	m_destination.m_y = y;
}

void Object::SetVolume(Vector2d vol)
{
	m_volume = vol;
}

void Object::SetColor(float r, float g, float b, float a)
{
	m_color = Color(r, g, b, a);
}

void Object::SetColor(Color color)
{
	m_color = color;
}

void Object::SetVolume(float m_x, float m_y)
{
	m_volume.m_x = m_x;
	m_volume.m_y = m_y;
}

void Object::SetVelocity(Vector2d vel)
{
	m_velocity = vel;
}

void Object::SetVelocity(float m_x, float m_y)
{
	m_velocity.m_x = m_x;
	m_velocity.m_y = m_y;
}

void Object::SetMass(float mass)
{
	m_mass = mass;
}

void Object::SetFriction(float frict)
{
	m_friction = frict;
}

void Object::SetType(ObjectType type)
{
	m_type = type;
}

void Object::SetTexture(const vector<int>& textures)
{
	m_texIDs = textures;
}

void Object::AddTexture(int texture)
{
	m_texIDs.push_back(texture);
}

void Object::SetTextureIndex(int index)
{
	if(index < m_texIDs.size())
		m_currentTexIndex = index;
}


void Object::SetActive(bool bActive)
{
	m_isActive = bActive;
}

void Object::SetDepth(int depth)
{
	m_depth = depth;
}

///////////////////////////////////////////////////////////////////////////////////////
void Object::Update(float deltaTime)
{
	if (m_isActive == false) return;

	const float bias = 30.0f;
	Vector2d dir = m_destination - m_position;
	float len = dir.length();
	float spd = len * bias;
	dir.normalize();
	dir *= deltaTime * spd;

	if (dir.length() > len)
		dir.normalize() * len;

	m_position += dir;
}
void Object::AddForce(Vector2d force, float fElapsedTime)
{
	Vector2d acc = force / m_mass;
	m_velocity += acc * fElapsedTime;
}

bool Object::isOverlap(const Object & other)
{
	float aMinX, aMaxX, aMinY, aMaxY;
	aMinX = m_position.m_x - m_volume.m_x / 2.0f; aMaxX = m_position.m_x + m_volume.m_x / 2.0f;
	aMinY = m_position.m_y - m_volume.m_y / 2.0f; aMaxY = m_position.m_y + m_volume.m_y / 2.0f;

	float bMinX, bMaxX, bMinY, bMaxY;
	bMinX = other.m_position.m_x - other.m_volume.m_x / 2.0f; bMaxX = other.m_position.m_x + other.m_volume.m_x / 2.0f;
	bMinY = other.m_position.m_y - other.m_volume.m_y / 2.0f; bMaxY = other.m_position.m_y + other.m_volume.m_y / 2.0f;

	if (aMinX > bMaxX) return false;
	if (aMaxX < bMinX) return false;

	if (aMinY > bMaxY) return false;
	if (aMaxY < bMinY) return false;

	return true;
}

//Player
Player::Player() : Object()
{
	m_isActive = false;
	weapon = 0;

	SetPosition(0.0f, 0.0f);
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetVolume(0.3f, 0.3f);
	SetVelocity(0.0f, 0.0f);
	SetMass(1.0f);
	SetFriction(0.6f);

	m_remainingBulletCoolTime = m_defaultBulletCoolTime[weapon];
}
Player::~Player() {};

void Player::Update(float deltaTime)
{
	// Reduce Bullet Cooltime
	m_remainingBulletCoolTime -= deltaTime;
	emotion_time -= deltaTime;

	Object::Update(deltaTime);
	for (int i = 0; i < MAX_BULLET; ++i)
		bullets[i].Update(deltaTime);
}

bool Player::CanShootBullet()
{
	return m_remainingBulletCoolTime <= FLT_EPSILON;
}

void Player::ResetShootBulletCoolTime()
{
	m_remainingBulletCoolTime = m_defaultBulletCoolTime[weapon];
}

int Player::AddBullet(Vector2d pos, Vector2d vol, Vector2d vel, float r, float g, float b, float a, float mass, float fricCoef)
{
	int idx = -1;
	for (int i = 0; i < MAX_BULLET; ++i)
	{
		if (bullets[i].GetAcitve() == false)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		std::cout << "No more remaining object" << std::endl;
		return idx;
	}

	bullets[idx].SetActive(true);
	bullets[idx].SetPosition(pos);
	bullets[idx].SetColor(r, g, b, a);
	bullets[idx].SetVolume(vol);
	bullets[idx].SetVelocity(vel);
	bullets[idx].SetMass(mass);
	bullets[idx].SetFriction(fricCoef);

	return idx;
}

void Player::ShootBullet(Vector2d MousePos)
{
	if (CanShootBullet() == false) return;

	float fAmountBullet = 8.0f, mass = 1.0f, fricCoef= 0.9f;

	Vector2d bulletDir = MousePos / 100;
	bulletDir -= m_position;
	bulletDir.normalize();
	Vector2d hVel = m_velocity + bulletDir * fAmountBullet;
	Vector2d vol(0.05f, 0.05f);

	int idx = AddBullet(m_position, vol, hVel, 1, 0, 0, 1, mass, fricCoef);
	bullets[idx].type = weapon;

	ResetShootBulletCoolTime();
}