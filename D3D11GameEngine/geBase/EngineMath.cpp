#include "Pre.h"
#include "EngineMath.h"
#include <math.h>

float4x4::float4x4(const float4x4& other)
{
	for (int x = 0; x < 16; x++)
	{
		matrix1D[x] = other.matrix1D[x];
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

void float4x4::Position(const float4& other)
{
	Identity();
	matrix[3][0] = other.x;
	matrix[3][1] = other.y;
	matrix[3][2] = other.z;
	matrix[3][3] = other.w;
}


void float4x4::Scale(const float4& other)
{
	Identity();
	matrix[0][0] = other.x;
	matrix[1][1] = other.y;
	matrix[2][2] = other.z;
	matrix[3][3] = other.w;
}

void float4x4::Rotation(const float4& Radian)
{
	Identity();

	float DegreeX = Radian.x;
	float DegreeY = Radian.y;
	float DegreeZ = Radian.z;

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
	matrix[1][2] = sinf(Radian);
	matrix[2][1] = -sinf(Radian);
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

void float4::operator*=(const float4x4& other)
{
	x = (x * other.matrix[0][0]) + (y * other.matrix[1][0]) + (z * other.matrix[2][0]) + (w * other.matrix[3][0]);
	y = (x * other.matrix[0][1]) + (y * other.matrix[1][1]) + (z * other.matrix[2][1]) + (w * other.matrix[3][1]);
	z = (x * other.matrix[0][2]) + (y * other.matrix[1][2]) + (z * other.matrix[2][2]) + (w * other.matrix[3][2]);
	w = (x * other.matrix[0][3]) + (y * other.matrix[1][3]) + (z * other.matrix[2][3]) + (w * other.matrix[3][3]);
}

float4 float4::operator*(const float4x4& other)
{
	float4 result;
	result.x = (x * other.matrix[0][0]) + (y * other.matrix[1][0]) + (z * other.matrix[2][0]) + (w * other.matrix[3][0]);
	result.y = (x * other.matrix[0][1]) + (y * other.matrix[1][1]) + (z * other.matrix[2][1]) + (w * other.matrix[3][1]);
	result.z = (x * other.matrix[0][2]) + (y * other.matrix[1][2]) + (z * other.matrix[2][2]) + (w * other.matrix[3][2]);
	result.w = (x * other.matrix[0][3]) + (y * other.matrix[1][3]) + (z * other.matrix[2][3]) + (w * other.matrix[3][3]);

	return result;
}