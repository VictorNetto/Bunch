#include <vector3.h>

using namespace bunch;

Vector3::Vector3()
	: x(0), y(0), z(0) {}

Vector3::Vector3(real x, real y, real z)
	: x(x), y(y), z(z) {}

void Vector3::operator+=(const Vector3& other)
{
	*this = *this + other;
}

void Vector3::operator-=(const Vector3& other)
{
	*this = *this - other;
}

void Vector3::operator*=(real n)
{
	*this = *this * n;
}

void Vector3::operator/=(real n)
{
	*this = *this / n;
}

real Vector3::dot(const Vector3& other)
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3& other)
{
	return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
}

real Vector3::length_square()
{
	return x * x + y * y + z * z;
}

real Vector3::length()
{
	return real_sqrt(length_square());
}

void Vector3::to_unit()
{
	real vector_length = length();
	x /= vector_length;
	y /= vector_length;
	z /= vector_length;
}

Vector3 Vector3::get_unit()
{
	real vector_length = length();
	return { x / vector_length, y / vector_length, z / vector_length };
}

Vector3 bunch::operator+(const Vector3& vec, const Vector3& vec2)
{
	return { vec.x + vec2.x, vec.y + vec2.y, vec.z + vec2.z };
}

Vector3 bunch::operator-(const Vector3& vec, const Vector3& vec2)
{
	return { vec.x - vec2.x, vec.y - vec2.y, vec.z - vec2.z };
}

Vector3 bunch::operator*(const Vector3& vec, real n)
{
	return { vec.x * n, vec.y * n, vec.z * n };
}

Vector3 bunch::operator/(const Vector3& vec, real n)
{
	return { vec.x / n, vec.y / n, vec.z / n };
}

#ifdef DEBUG
std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")\n";
	return os;
}
#endif