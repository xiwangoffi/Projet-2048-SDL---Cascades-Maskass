#include "Vector2.h"

#pragma region Vector2

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2::~Vector2()
{}

Vector2 Vector2::operator+(const Vector2& u) {
	return Vector2(
		x + u.x,
		y + u.y
	);
}

Vector2 Vector2::operator-(const Vector2& u) {
	return Vector2(
		x + u.x,
		y + u.y
	);
}

Vector2 Vector2::operator*(const float& scalar) {
	return Vector2(
		x * scalar,
		y * scalar
	);
}

Vector2 Vector2::operator/(const float& scalar) {
	return Vector2(
		x / scalar,
		y / scalar
	);
}

void Vector2::operator+=(const Vector2& u) {
	x += u.x;
	y += u.y;
}

void Vector2::operator-=(const Vector2& u) {
	x -= u.x;
	y -= u.y;
}

void Vector2::operator*=(const float& scalar) {
	x *= scalar;
	y *= scalar;
}

void Vector2::operator/=(const float& scalar) {
	x /= scalar;
	y /= scalar;
}

std::ostream& operator<<(std::ostream& os, const Vector2& u) {
	os << u.x << ", " << u.y;
	return os;
}

#pragma endregion Vector2

#pragma region Vector2i

Vector2i::Vector2i(int x, int y) {
	this->x = x;
	this->y = y;
}

Vector2i::~Vector2i()
{}

Vector2i Vector2i::operator+(const Vector2i& u) {
	return Vector2i(
		x + u.x,
		y + u.y
	);
}

Vector2i Vector2i::operator-(const Vector2i& u) {
	return Vector2i(
		x + u.x,
		y + u.y
	);
}

Vector2i Vector2i::operator*(const float& scalar) {
	return Vector2i(
		std::round(x * scalar),
		std::round(y * scalar)
	);
}

Vector2i Vector2i::operator/(const float& scalar) {
	return Vector2i(
		std::round(x / scalar),
		std::round(y / scalar)
	);
}

void Vector2i::operator+=(const Vector2i& u) {
	x += u.x;
	y += u.y;
}

void Vector2i::operator-=(const Vector2i& u) {
	x -= u.x;
	y -= u.y;
}

void Vector2i::operator*=(const float& scalar) {
	x = std::round(x * scalar);
	y = std::round(y * scalar);
}

void Vector2i::operator/=(const float& scalar) {
	x = std::round(x / scalar);
	y = std::round(y / scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector2i& u) {
	os << u.x << ", " << u.y;
	return os;
}

#pragma endregion Vector2i