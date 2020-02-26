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


float* AMSA3::Math::Vector3::GetAddressFromChar(const char dest) const
{
	if      (dest == 'x') return (float*)(&data.x);
	else if (dest == 'y') return (float*)(&data.y);
	else if (dest == 'z') return (float*)(&data.z);
	else return nullptr;
}

float AMSA3::Math::Vector3::GetValueFromChar(const char dest) const
{
	return *this->GetAddressFromChar(dest);
}

void AMSA3::Math::Vector3::Swizzle(const char destX, const char destY, const char destZ)
{
	//A temporary vec3
	Vector3 temp(0, 0, 0);

	//Set the x, y, z of the temp to swizzled dests
	temp.data.x = this->GetValueFromChar(destX);
	temp.data.y = this->GetValueFromChar(destY);
	temp.data.z = this->GetValueFromChar(destZ);

	//Set this data to temp data
	this->data.x = temp.data.x;
	this->data.y = temp.data.y;
	this->data.z = temp.data.z;
}

Vector3 AMSA3::Math::Vector3::operator*(const float rhs) const
{
	return Vector3(this->data.x * rhs, this->data.y * rhs, this->data.z * rhs);
}

Vector3 AMSA3::Math::Vector3::operator*(const Vector3& rhs) const
{
	return Vector3(this->data.x * rhs.data.x, this->data.y * rhs.data.y, this->data.z * rhs.data.z);
}

Vector3& AMSA3::Math::Vector3::operator*=(const float rhs)
{
	this->data.x *= rhs;
	this->data.y *= rhs;
	this->data.z *= rhs;

	return *this;
}

Vector3& AMSA3::Math::Vector3::operator*=(const Vector3& rhs)
{
	this->data.x *= rhs.data.x;
	this->data.y *= rhs.data.y;
	this->data.z *= rhs.data.z;

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