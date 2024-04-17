#include "Pre.h"
#include "EngineMath.h"
#include <math.h>

void float4::operator*=(const float4x4& Other)
{
	float4 result;
	result.x = (x * Other.matrix[0][0]) + (y * Other.matrix[1][0]) + (z * Other.matrix[2][0]) + (w * Other.matrix[3][0]);
	result.y = (x * Other.matrix[0][1]) + (y * Other.matrix[1][1]) + (z * Other.matrix[2][1]) + (w * Other.matrix[3][1]);
	result.z = (x * Other.matrix[0][2]) + (y * Other.matrix[1][2]) + (z * Other.matrix[2][2]) + (w * Other.matrix[3][2]);
	result.w = (x * Other.matrix[0][3]) + (y * Other.matrix[1][3]) + (z * Other.matrix[2][3]) + (w * Other.matrix[3][3]);

	*this = result;
}

float4 float4::operator*(const float4x4& Other)
{
	float4 result;
	result.x = (x * Other.matrix[0][0]) + (y * Other.matrix[1][0]) + (z * Other.matrix[2][0]) + (w * Other.matrix[3][0]);
	result.y = (x * Other.matrix[0][1]) + (y * Other.matrix[1][1]) + (z * Other.matrix[2][1]) + (w * Other.matrix[3][1]);
	result.z = (x * Other.matrix[0][2]) + (y * Other.matrix[1][2]) + (z * Other.matrix[2][2]) + (w * Other.matrix[3][2]);
	result.w = (x * Other.matrix[0][3]) + (y * Other.matrix[1][3]) + (z * Other.matrix[2][3]) + (w * Other.matrix[3][3]);

	return result;
}

float4x4::float4x4(const float4x4& Other)
{
	for (int x = 0; x < 16; x++)
	{
		matrix1D[x] = Other.matrix1D[x];
	}
}
float4x4::float4x4(const std::vector<std::vector<float>> _matrix)
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			matrix[x][y] = _matrix[x][y];
		}
	}
}
float4x4::float4x4(const std::vector<float> _matrix)
{
	for (int x = 0; x < 16; x++)
	{
		matrix1D[x] = _matrix[x];
	}
}
void float4x4::Identity()
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (x == y)
			{
				matrix[x][y] = 1.0f;
				continue;
			}
			matrix[x][y] = 0.0f;
		}
	}
}

void float4x4::Zero()
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			matrix[x][y] = 0.0f;
		}
	}
}

void float4x4::TransPose()
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = x + 1; y < 4; y++)
		{
			float temp = matrix[x][y];
			matrix[x][y] = matrix[y][x];
			matrix[y][x] = temp;
		}
	}
}

float4x4 float4x4::operator*(const float4x4& R)
{
	float4x4 res;
	res.Zero();

	for (size_t r = 0; r < 4; r++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t i = 0; i < 4; i++)
			{
				res.matrix[r][j] += matrix[r][i] * R.matrix[i][j];
			}
		}
	}

	return res;
}

void float4x4::Position(const float4& Other)
{
	Identity();
	matrix[3][0] = Other.x;
	matrix[3][1] = Other.y;
	matrix[3][2] = Other.z;
}


void float4x4::Scale(const float4& Other)
{
	Identity();
	matrix[0][0] = Other.x;
	matrix[1][1] = Other.y;
	matrix[2][2] = Other.z;
	matrix[3][3] = Other.w;
}

void float4x4::Rotation(const float4& Degree)
{
	Identity();

	float DegreeX = Degree.x;
	float DegreeY = Degree.y;
	float DegreeZ = Degree.z;

	float DegreeToRadian = PI / 180;
	float RadianX = DegreeX * DegreeToRadian;
	float RadianY = DegreeY * DegreeToRadian;
	float RadianZ = DegreeZ * DegreeToRadian;

	float4x4 ZRot;
	ZRot.RotationZ(RadianZ);
	float4x4 YRot;
	YRot.RotationY(RadianY);
    float4x4 XRot;
	XRot.RotationX(RadianX);

	*this = ZRot * YRot * XRot;
}

void float4x4::RotationX(const float Radian)
{
	matrix[1][1] = cosf(Radian);
	matrix[1][2] = -sinf(Radian);
	matrix[2][1] = sinf(Radian);
	matrix[2][2] = cosf(Radian);
}

void float4x4::RotationY(const float Radian)
{
	matrix[0][0] = cosf(Radian);
	matrix[0][2] = -sinf(Radian);
	matrix[2][0] = sinf(Radian);
	matrix[2][2] = cosf(Radian);
 }

void float4x4::RotationZ(const float Radian)
 {
	matrix[0][0] = cosf(Radian);
	matrix[0][1] = sinf(Radian);
	matrix[1][0] = -sinf(Radian);
	matrix[1][1] = cosf(Radian);
}

void float4x4::View(float4& EyePos, float4& EyeDir, float4& EyeUp)
{
	float4 EyeRight = EyeDir.Cross(EyeUp);
	matrix[0][0] = EyeRight.x;
	matrix[0][1] = EyeRight.y;
	matrix[0][2] = EyeRight.z;

	matrix[1][0] = EyeUp.x;
	matrix[1][1] = EyeUp.y;
	matrix[1][2] = EyeUp.z;

	matrix[2][0] = EyeDir.x;
	matrix[2][1] = EyeDir.y;
	matrix[2][2] = EyeDir.z;

	TransPose();
}
void float4x4::Projection(float Width, float Height, float Near, float Far)
{
	Identity();
	matrix[0][0] = 2 / Width;
	matrix[1][1] = 2 / Height;
	matrix[2][2] = 1 / Far - Near;
	matrix[3][2] = Near / Near - Far;
}

float4 float4::Cross(float4& Other)
{
	float X = y * Other.z - z * Other.y;
	float Y = z * Other.x - x * Other.z;
	float Z = x * Other.y - y * Other.x;

	return { X,Y,Z,1 };
}