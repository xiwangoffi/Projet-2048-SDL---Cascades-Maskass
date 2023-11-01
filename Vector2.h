#pragma once

#include <iostream>

class Vector2 {
public:
	float x, y;
	
	Vector2(float x, float y);
	~Vector2();

	Vector2 operator+(const Vector2& u);
	Vector2 operator-(const Vector2& u);
	Vector2 operator*(const float& scalar);
	Vector2 operator/(const float& scalar);
	void operator+=(const Vector2& u);
	void operator-=(const Vector2& u);
	void operator*=(const float& scalar);
	void operator/=(const float& scalar);

	static Vector2 one() { return Vector2(1, 1); }
	static Vector2 zero() { return Vector2(0, 0); }
	static Vector2 up() { return Vector2(0, -1); }
	static Vector2 down() { return Vector2(0, 1); }
	static Vector2 right() { return Vector2(1, 0); }
	static Vector2 left() { return Vector2(-1, 0); }
};

class Vector2i {
public:
	int x, y;

	Vector2i(int x, int y);
	~Vector2i();

	Vector2i operator+(const Vector2i& u);
	Vector2i operator-(const Vector2i& u);
	Vector2i operator*(const float& scalar);
	Vector2i operator/(const float& scalar);
	
	static Vector2 one() { return Vector2(1.0, 1.0); }
	static Vector2 zero() { return Vector2(0.0, 0.0); }
	static Vector2 up() { return Vector2(0.0, -1.0); }
	static Vector2 down() { return Vector2(0.0, 1.0); }
	static Vector2 right() { return Vector2(1.0, 0.0); }
	static Vector2 left() { return Vector2(-1.0, 0.0); }
};