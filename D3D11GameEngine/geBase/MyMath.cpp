#include <math.h>
#include "mymath.h"

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

void float4x4::Position(const float4& other)
{
	matrix[3][0] = other.x;
	matrix[3][1] = other.y;
	matrix[3][2] = other.z;
	matrix[3][3] = other.w;
}


void float4x4::Scale(const float4& other)
{
	matrix[0][0] = other.x;
	matrix[1][1] = other.y;
	matrix[2][2] = other.z;
	matrix[3][3] = other.w;
}

void float4x4::Rotation(const float Radian)
{
	matrix[0][0] = cos(Radian);
	matrix[1][0] = -sin(Radian);

	matrix[0][1] = sin(Radian);
	matrix[1][1] = cos(Radian);
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