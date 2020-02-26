#pragma once
#include <ostream>
#include <string>

namespace AMSA3
{
	namespace Math
	{
		class Vector3
		{
		private:
#pragma pack(push, 1)
			typedef struct vec3_data
			{
				float x = 0.0f;
				float y = 0.0f;
				float z = 0.0f;
			} vec3_data;
#pragma pack(pop)

			float* GetAddressFromChar(const char dest) const;
			float GetValueFromChar(const char dest) const;

		public:
			vec3_data data;

			Vector3(void);
			Vector3(float x);
			Vector3(float x, float y);
			Vector3(float x, float y, float z);

			void Swizzle(const char destX, const char destY, const char destZ);

			Vector3 operator*(const float rhs) const;
			Vector3 operator*(const Vector3& rhs) const;
			Vector3 operator/(const float rhs) const;
			Vector3 operator+(const float rhs) const;
			Vector3 operator+(const Vector3& rhs) const;
			Vector3 operator-(const float rhs) const;
			Vector3 operator-(const Vector3& rhs) const;

			Vector3& operator*=(const float rhs);
			Vector3& operator*=(const Vector3& rhs);
			Vector3& operator/=(const float rhs);
			Vector3& operator+=(const float rhs);
			Vector3& operator+=(const Vector3& rhs);
			Vector3& operator-=(const float rhs);
			Vector3& operator-=(const Vector3& rhs);

			operator std::string() const;

			static const Vector3 UP;
			static const Vector3 LEFT;
			static const Vector3 FORWARD; 
		};
	}
}