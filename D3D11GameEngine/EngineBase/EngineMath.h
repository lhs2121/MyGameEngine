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
	};

	float4 Cross(float4& Other);

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

	float4 operator+(const float4& Other) const
	{
		return { x + Other.x ,y + Other.y ,z + Other.z ,w };
	}

	float4 operator+(const float4&& Other) const
	{
		return { x + Other.x ,y + Other.y ,z + Other.z ,w };
	}

	float4 operator-(const float4& Other) const
	{
		return { x - Other.x ,y - Other.y ,z - Other.z ,w };
	}

	float4 operator-(const float4&& Other) const
	{
		return { x - Other.x ,y - Other.y ,z - Other.z ,w };
	}

	float4 operator-() const
	{
		return { -x,-y,-z ,w };
	}

	float4 operator*(const float4& Other) const
	{
		return { x * Other.x ,y * Other.y ,z * Other.z ,w };
	}

	float4 operator*(const float4&& Other) const
	{
		return { x * Other.x ,y * Other.y ,z * Other.z ,w };
	}

	float4 operator*(const float Other) const
	{
		return { x * Other,y * Other,z * Other,w };
	}

	float4 operator/(const float4& Other) const
	{
		return { x / Other.x ,y / Other.y ,z / Other.z ,w };
	}

	float4 operator/(const float4&& Other) const
	{
		return { x / Other.x ,y / Other.y ,z / Other.z ,w };
	}

	float4 operator/(float Other) const
	{
		return { x / Other ,y / Other ,z / Other ,w };
	}

	void operator+=(const float4& Other)
	{
		x += Other.x;
		y += Other.y;
		z += Other.z;
	}

	void operator+=(const float4&& Other)
	{
		x += Other.x;
		y += Other.y;
		z += Other.z;
	}

	void operator-=(const float4& Other)
	{
		x -= Other.x;
		y -= Other.y;
		z -= Other.z;
	}

	void operator-=(const float4&& Other)
	{
		x -= Other.x;
		y -= Other.y;
		z -= Other.z;
	}

	void operator*=(const float4& Other)
	{
		x *= Other.x;
		y *= Other.y;
		z *= Other.z;
	}

	void operator*=(const float4&& Other)
	{
		x *= Other.x;
		y *= Other.y;
		z *= Other.z;
	}

	void operator*=(const float Other)
	{
		x *= Other;
		y *= Other;
		z *= Other;
	}

	void operator/=(const float4& Other)
	{
		x /= Other.x;
		y /= Other.y;
		z /= Other.z;
	}

	void operator/=(const float4&& Other)
	{
		x /= Other.x;
		y /= Other.y;
		z /= Other.z;
	}

	void operator/=(const float Other)
	{
		x /= Other;
		y /= Other;
		z /= Other;
	}

	void operator*=(const float4x4& Other);
	float4 operator*(const float4x4& Other);
};

class float4x4
{
public:
	float4x4()
	{

	}

	float4x4(const float4x4& Other);
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

	float4x4 operator*(const float4x4& Other);

	void Identity();
	void Zero();
	void TransPose();

	void Position(const float4& Other);
	void Scale(const float4& Other);
	void Rotation(const float4& Radian);

	void RotationX(const float Radian);
	void RotationY(const float Radian);
	void RotationZ(const float Radian);

	void View(float4& EyePos, float4& EyeDir, float4& EyeUp);
	void Projection();
};