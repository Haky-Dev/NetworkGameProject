#pragma once
#include <iostream>

class Vector2d {
public:
	Vector2d() :m_x(0), m_y(0) {};
	Vector2d(float m_x, float m_y) :m_x(m_x), m_y(m_y) {};
	~Vector2d() {};

	float dot(const Vector2d& other) const { return this->m_x*other.m_x + this->m_y*other.m_y; };
	float cross(const Vector2d& other) const { return this->m_x*other.m_y - this->m_y*other.m_x; };
	float length() { return sqrtf(m_x*m_x + m_y * m_y); };
	Vector2d& normalize() { if (isZero()) return *this;	float len = length();	m_x /= len; m_y /= len;	return *this; };
	bool isZero() { return length() < 0.000001f; };

	void clear() { m_x = 0; m_y = 0; };

	float m_x, m_y;

public:
	Vector2d operator+(const Vector2d& other) { return Vector2d(this->m_x + other.m_x, this->m_y + other.m_y); };
	Vector2d operator-(const Vector2d& other) { return Vector2d(this->m_x - other.m_x, this->m_y - other.m_y); };
	Vector2d operator*(const float& value) { return Vector2d(this->m_x * value, this->m_y * value); };
	Vector2d operator/(const float& value) { return Vector2d(this->m_x / value, this->m_y / value); };

	Vector2d& operator=(const Vector2d& other) { this->m_x = other.m_x; this->m_y = other.m_y; return *this; };
	Vector2d& operator+=(const Vector2d& other) { this->m_x += other.m_x; this->m_y += other.m_y; return *this; };
	Vector2d& operator-=(const Vector2d& other) { this->m_x -= other.m_x; this->m_y -= other.m_y; return *this; };
	Vector2d& operator*=(const float& value) { this->m_x *= value; this->m_y *= value; return *this; };
	Vector2d& operator/=(const float& value) { this->m_x /= value; this->m_y /= value; return *this; };
	bool operator==(const Vector2d& other) { return (this->m_x == other.m_x) && (this->m_y == other.m_y); };
};