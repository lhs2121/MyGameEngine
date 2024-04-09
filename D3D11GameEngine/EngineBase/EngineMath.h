#pragma once
#include <DirectXMath.h>
constexpr auto PI = 3.14159265358979323846264338327950288419716939937510f;

class float4x4;
class float4
{
public:
	float4(float _x = 0, float _y = 0, float _z = 0, float _w = 1) : x(_x), y(_y), z(_z), w(_w)
	{

	}

	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		DirectX::XMVECTOR DXvec;
		DirectX::XMFLOAT4 DXfloat3;
		DirectX::XMFLOAT3 DXfloat4;
	};

	float hx() const
	{
		return x / 2;
	}

	float hy() const
	{
		return y / 2;
	}

	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int ihx() const
	{
		return static_cast<int>(x / 2);
	}

	int ihy() const
	{
		return static_cast<int>(y / 2);
	}

	float4 operator+(const float4& other) const
	{
		return { x + other.x ,y + other.y ,z + other.z ,w };
	}

	float4 operator+(const float4&& other) const
	{
		return { x + other.x ,y + other.y ,z + other.z ,w };
	}

	float4 operator-(const float4& other) const
	{
		return { x - other.x ,y - other.y ,z - other.z ,w };
	}

	float4 operator-(const float4&& other) const
	{
		return { x - other.x ,y - other.y ,z - other.z ,w };
	}

	float4 operator-() const
	{
		return { -x,-y,-z ,w };
	}

	float4 operator*(const float4& other) const
	{
		return { x * other.x ,y * other.y ,z * other.z ,w };
	}

	float4 operator*(const float4&& other) const
	{
		return { x * other.x ,y * other.y ,z * other.z ,w };
	}

	float4 operator*(const float other) const
	{
		return { x * other,y * other,z * other,w };
	}

	float4 operator/(const float4& other) const
	{
		return { x / other.x ,y / other.y ,z / other.z ,w };
	}

	float4 operator/(const float4&& other) const
	{
		return { x / other.x ,y / other.y ,z / other.z ,w };
	}

	float4 operator/(float other) const
	{
		return { x / other ,y / other ,z / other ,w };
	}

	void operator+=(const float4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	void operator+=(const float4&& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	void operator-=(const float4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}

	void operator-=(const float4&& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}

	void operator*=(const float4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
	}

	void operator*=(const float4&& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
	}

	void operator*=(const float other)
	{
		x *= other;
		y *= other;
		z *= other;
	}

	void operator/=(const float4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
	}

	void operator/=(const float4&& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
	}

	void operator/=(const float other)
	{
		x /= other;
		y /= other;
		z /= other;
	}

	void operator*=(const float4x4& other);
	float4 operator*(const float4x4& other);
};

class float4x4
{
public:
	float4x4()
	{

	}

	float4x4(const float4x4& other);
	float4x4(const std::vector<std::vector<float>> _matrix);
	float4x4(const std::vector<float> _matrix);

	union
	{
		float matrix[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f},
			{ 0.0f, 1.0f, 0.0f, 0.0f},
			{ 0.0f, 0.0f, 1.0f, 0.0f},
			{ 0.0f, 0.0f, 0.0f, 1.0f}
		};

		float matrix1D[16];
	};

	float4x4 operator*(const float4x4& other);
	void Position(const float4& other);
	void Scale(const float4& other);
	void Rotation(const float4& Radian);

	void RotationX(const float Radian);
	void RotationY(const float Radian);
	void RotationZ(const float Radian);

	void Identity();
	void Zero();
	void TransPose();
};