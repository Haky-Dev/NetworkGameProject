#pragma once
#include "Vector2d.h"
#include <vector>
#include "Color.h"
#include "Config.h"

using namespace std;

#define INVALID_TEXTURE -1
class Object
{
public:
	Object();
	Object(ObjectType type);
	~Object();
	void Initialize();

	//Set & Get
	void SetPosition(Vector2d pos);
	void SetPosition(float m_x, float m_y);
	void SetDestination(Vector2d des);
	void SetDestination(float x, float y);
	void SetVolume(Vector2d vol);
	void SetVolume(float m_x, float m_y);
	void SetVelocity(Vector2d vel);
	void SetVelocity(float m_x, float m_y);
	void SetColor(float r, float g, float b, float a);
	void SetColor(Color color);
	void SetMass(float mass);
	void SetFriction(float frict);
	void SetType(ObjectType type);
	void SetTexture(const vector<int>& textures);
	void AddTexture(int texture);
	void SetTextureIndex(int index);
	void SetActive(bool NewVisibility);
	void SetDepth(int depth);

	Vector2d GetPosition() const { return m_position; }
	Vector2d GetVolume() const { return m_volume; }
	Vector2d GetVelocity() const { return m_destination; }
	Color GetColor() const { return m_color; }
	int GetTexture() const { return m_texIDs[m_currentTexIndex]; }
	int GetTexture(int index) const {
		if(m_texIDs.size() > index)	return m_texIDs[index];
		return INVALID_TEXTURE;
	}
	int GetDepth() const { return m_depth; }
	bool GetAcitve() const { return m_isActive; }

	//Update
	void Update(float fTimeElapsed);
	void AddForce(Vector2d force, float fElapsedTime);

	//Collision Check
	bool isOverlap(const Object& other);
	void correctpos(const Object& collider) {
		Vector2d dir = m_position - collider.m_position;
		if (dir.m_y * dir.m_y > dir.m_x * dir.m_x)
		{
			float len = (m_volume.m_y + collider.m_volume.m_y) / 2.0f;
			if (dir.m_y > 0)
				m_position.m_y = collider.m_position.m_y + len;
			else
				m_position.m_y = collider.m_position.m_y - len;
		}
		else
		{
			float len = (m_volume.m_x + collider.m_volume.m_x) / 2.0f;
			if (dir.m_x > 0)
				m_position.m_x = collider.m_position.m_x + len;
			else
				m_position.m_x = collider.m_position.m_x - len;
		}
	}

protected:
	bool m_isActive;

	ObjectType m_type;
	Vector2d m_position;
	Vector2d m_destination;
	Vector2d m_velocity;
	Vector2d m_acceleration;
	Vector2d m_volume;

	float m_mass;
	float m_friction;
	int m_currentTexIndex;
	int m_depth;
	vector<int> m_texIDs;
	Color m_color;
};

class Bullet : public Object
{
public:
	Bullet() : Object() {};
	~Bullet(){};

	int type = 0;
};

class Item : public Object
{
public:
	Item() : Object() { type = rand() % 3; };
	~Item() {};
	int type;
};

class Player : public Object
{
public:
	int m_hp = 100;
	int weapon = 0;
	Bullet bullets[MAX_BULLET];

	int m_chat = -1;
	bool m_key[4];
	bool m_mouse;

	float emotion_time = 0.0f;
	float emotion_duration_time = 2.0f;

	Player();
	~Player();
	void Update(float fTimeElapsed);
	bool CanShootBullet();
	void ResetShootBulletCoolTime();
	int AddBullet(Vector2d pos, Vector2d vol, Vector2d vel, float r, float g, float b, float a, float mass, float fricCoef);
	void ShootBullet(Vector2d MousePos);
	bool getDamage(const Bullet& bullet)
	{
		m_hp -= m_damage[bullet.type];
		return m_hp <= 0;
	}
	void die() {
		m_isActive = false;
		for (auto& b : bullets)
			b.SetActive(false);
	}

private:
	float m_remainingBulletCoolTime = 0.0f;
	float m_defaultBulletCoolTime[3] = { 0.1f, 0.075f, 0.125f };
	int m_damage[3] = { 30, 20, 50 };
};