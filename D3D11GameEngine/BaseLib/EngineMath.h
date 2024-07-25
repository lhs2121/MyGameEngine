#pragma once

constexpr float PI = 3.141592653f;
constexpr float DegToRad = 3.141592653f / 180.0f;

struct BaseAPI EngineMath
{
	static int GetDigitCount(unsigned long long Num);
};
struct float2
{
	float2(float _x = 0, float _y = 0)
		: x(_x), y(_y)
	{
	}

	float x;
	float y;

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

	float2 operator+(const float2& Other) const
	{
		return { x + Other.x ,y + Other.y };
	}

	float2 operator+(const float2&& Other) const
	{
		return { x + Other.x ,y + Other.y };
	}

	float2 operator-(const float2& Other) const
	{
		return { x - Other.x ,y - Other.y };
	}

	float2 operator-(const float2&& Other) const
	{
		return { x - Other.x ,y - Other.y };
	}

	float2 operator-() const
	{
		return { -x,-y };
	}

	float2 operator*(const float2& Other) const
	{
		return { x * Other.x ,y * Other.y };
	}

	float2 operator*(const float2&& Other) const
	{
		return { x * Other.x ,y * Other.y };
	}

	float2 operator*(const float Other) const
	{
		return { x * Other,y * Other };
	}

	float2 operator/(const float2& Other) const
	{
		return { x / Other.x ,y / Other.y };
	}

	float2 operator/(const float2&& Other) const
	{
		return { x / Other.x ,y / Other.y };
	}

	float2 operator/(float Other) const
	{
		return { x / Other ,y / Other };
	}

	void operator+=(const float2& Other)
	{
		x += Other.x;
		y += Other.y;
	}

	void operator+=(const float2&& Other)
	{
		x += Other.x;
		y += Other.y;
	}

	void operator-=(const float2& Other)
	{
		x -= Other.x;
		y -= Other.y;
	}

	void operator-=(const float2&& Other)
	{
		x -= Other.x;
		y -= Other.y;
	}

	void operator*=(const float2& Other)
	{
		x *= Other.x;
		y *= Other.y;
	}

	void operator*=(const float2&& Other)
	{
		x *= Other.x;
		y *= Other.y;
	}

	void operator*=(const float Other)
	{
		x *= Other;
		y *= Other;
	}

	void operator/=(const float2& Other)
	{
		x /= Other.x;
		y /= Other.y;
	}

	void operator/=(const float2&& Other)
	{
		x /= Other.x;
		y /= Other.y;
	}

	void operator/=(const float Other)
	{
		x /= Other;
		y /= Other;
	}

};

struct float3
{
	float3(float _x = 0, float _y = 0, float _z = 0)
		: x(_x), y(_y), z(_z)
	{
	}
	float x;
	float y;
	float z;
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

	float3 operator+(const float3& Other) const
	{
		return { x + Other.x ,y + Other.y ,z + Other.z };
	}

	float3 operator+(const float3&& Other) const
	{
		return { x + Other.x ,y + Other.y ,z + Other.z };
	}

	float3 operator-(const float3& Other) const
	{
		return { x - Other.x ,y - Other.y ,z - Other.z };
	}

	float3 operator-(const float3&& Other) const
	{
		return { x - Other.x ,y - Other.y ,z - Other.z };
	}

	float3 operator-() const
	{
		return { -x,-y,-z };
	}

	float3 operator*(const float3& Other) const
	{
		return { x * Other.x ,y * Other.y ,z * Other.z };
	}

	float3 operator*(const float3&& Other) const
	{
		return { x * Other.x ,y * Other.y ,z * Other.z };
	}

	float3 operator*(const float Other) const
	{
		return { x * Other,y * Other,z * Other };
	}

	float3 operator/(const float3& Other) const
	{
		return { x / Other.x ,y / Other.y ,z / Other.z };
	}

	float3 operator/(const float3&& Other) const
	{
		return { x / Other.x ,y / Other.y ,z / Other.z };
	}

	float3 operator/(float Other) const
	{
		return { x / Other ,y / Other ,z / Other };
	}

	void operator+=(const float3& Other)
	{
		x += Other.x;
		y += Other.y;
		z += Other.z;
	}

	void operator+=(const float3&& Other)
	{
		x += Other.x;
		y += Other.y;
		z += Other.z;
	}

	void operator-=(const float3& Other)
	{
		x -= Other.x;
		y -= Other.y;
		z -= Other.z;
	}

	void operator-=(const float3&& Other)
	{
		x -= Other.x;
		y -= Other.y;
		z -= Other.z;
	}

	void operator*=(const float3& Other)
	{
		x *= Other.x;
		y *= Other.y;
		z *= Other.z;
	}

	void operator*=(const float3&& Other)
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

	void operator/=(const float3& Other)
	{
		x /= Other.x;
		y /= Other.y;
		z /= Other.z;
	}

	void operator/=(const float3&& Other)
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
};
struct float4x4;
struct BaseAPI float4
{
	float4(float _x = 0, float _y = 0, float _z = 0, float _w = 1)
		: x(_x), y(_y), z(_z), w(_w)
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

	void Normalize();

	static float4 Normalize(float4& Other);

	static float Dot(float4& Left, float4& Right);

	static float4 Cross(float4& Left, float4& Right);

	void operator*=(const float4x4& Other);

	float4 operator*(const float4x4& Other);

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

};

struct BaseAPI float4x4
{
	float4x4()
	{

	}
	float4x4(const float4x4& Other);

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
	void Rotation(const float4& Deg);

	void RotationX(const float Rad);
	void RotationY(const float Rad);
	void RotationZ(const float Rad);

	void View(float4& EyePos, float4& EyeDir, float4& EyeUp);
	void Perspective(float FovYDeg, float Width, float Height, float Near, float Far);
	void Orthographic(float Width, float Height, float Near, float Far);
};