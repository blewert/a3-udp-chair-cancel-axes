#include "..\include\Vector3.h"

using namespace AMSA3::Math;

//Constants of the vector3 class
const Vector3 Vector3::UP      = Vector3(0, 1, 0);
const Vector3 Vector3::LEFT    = Vector3(0, 1, 0);
const Vector3 Vector3::FORWARD = Vector3(0, 1, 0);

//Constructors
AMSA3::Math::Vector3::Vector3(void)                      : data({ 0, 0, 0 }) { }
AMSA3::Math::Vector3::Vector3(float x)                   : data({ x, x, x }) { }
AMSA3::Math::Vector3::Vector3(float x, float y)          : data({ x, y, 0 }) { }
AMSA3::Math::Vector3::Vector3(float x, float y, float z) : data({ x, y, z }) { }

Vector3 AMSA3::Math::Vector3::operator*(const float rhs) const
{
	return Vector3(this->data.x * rhs, this->data.y * rhs, this->data.z * rhs);
}

Vector3& AMSA3::Math::Vector3::operator*=(const float rhs)
{
	this->data.x *= rhs;
	this->data.y *= rhs;
	this->data.z *= rhs;

	return *this;
}


Vector3 AMSA3::Math::Vector3::operator+(const float rhs) const 
{
	return Vector3(this->data.x + rhs, this->data.y + rhs, this->data.z + rhs);
}

Vector3 AMSA3::Math::Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(this->data.x + rhs.data.x, this->data.y + rhs.data.y, this->data.z + rhs.data.z);
}

Vector3 AMSA3::Math::Vector3::operator-(const float rhs) const
{
	return Vector3(this->data.x - rhs, this->data.y - rhs, this->data.z - rhs);
}

Vector3 AMSA3::Math::Vector3::operator-(const Vector3& rhs) const
{
	return Vector3(this->data.x - rhs.data.x, this->data.y - rhs.data.y, this->data.z - rhs.data.z);
}

Vector3 AMSA3::Math::Vector3::operator/(const float rhs) const
{
	return Vector3(this->data.x / rhs, this->data.y / rhs, this->data.z / rhs);
}


Vector3& AMSA3::Math::Vector3::operator+=(const float rhs)
{
	this->data.x += rhs;
	this->data.y += rhs;
	this->data.z += rhs;

	return *this;
}

Vector3& AMSA3::Math::Vector3::operator+=(const Vector3& rhs)
{
	this->data.x += rhs.data.x;
	this->data.y += rhs.data.y;
	this->data.z += rhs.data.z;

	return *this;
}

Vector3& AMSA3::Math::Vector3::operator-=(const float rhs)
{
	this->data.x -= rhs;
	this->data.y -= rhs;
	this->data.z -= rhs;

	return *this;
}

Vector3& AMSA3::Math::Vector3::operator-=(const Vector3& rhs)
{
	this->data.x -= rhs.data.x;
	this->data.y -= rhs.data.y;
	this->data.z -= rhs.data.z;

	return *this;
}

AMSA3::Math::Vector3::operator std::string() const
{
	return "(" + std::to_string(this->data.x) + ", " + std::to_string(this->data.y) + ", " + std::to_string(this->data.z) + ")";
}

Vector3& AMSA3::Math::Vector3::operator/=(const float rhs)
{
	this->data.x /= rhs;
	this->data.y /= rhs;
	this->data.z /= rhs;

	return *this;
}