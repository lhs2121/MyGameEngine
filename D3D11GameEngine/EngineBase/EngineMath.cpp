#include "Pre.h"
#include "EngineMath.h"
#include <math.h>

float4 float4::Cross(float4& Left, float4& Right)
{
	float x = Left.y * Right.z - Left.z * Right.y;
	float y = Left.z * Right.x - Left.x * Right.z;
	float z = Left.x * Right.y - Left.y * Right.x;

	return { x,y,z,1 };
}

float float4::Dot(float4& Left, float4& Right)
{
	return Left.x * Right.x + Left.y * Right.y + Left.z * Right.z;
}

float4 float4::Normalize(float4& Other)
{
	float4 result;
	result = Other;
	float length = sqrt(Other.x * Other.x + Other.y * Other.y + Other.z * Other.z);

	result.x /= length;
	result.y /= length;
	result.z /= length;
	return result;
}

void float4::Normalize()
{
	float length = sqrt(x * x + y * y + z * z);
	x /= length;
	y /= length;
	z /= length;
}

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

	*this = ZRot * XRot * YRot;
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
	Identity();

	EyeDir.Normalize();
	EyeUp.Normalize();

	float4 EyeRight = float4::Cross(EyeUp, EyeDir);

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

	float4 Pos = -EyePos;
	matrix[3][0] = float4::Dot(EyeRight, Pos);
	matrix[3][1] = float4::Dot(EyeUp, Pos);
	matrix[3][2] = float4::Dot(EyeDir, Pos);
}
void float4x4::Perspective(float FovYDegree, float Width, float Height, float Near, float Far)
{
	Identity();

	float DegreeToRadian = PI / 180;
	float FovY = FovYDegree * DegreeToRadian;
	float d = 1 / tanf(FovY /2);
	float aspect = Width / Height;

	matrix[0][0] = d * 1/aspect;
	matrix[1][1] = d;
	matrix[2][2] = Far / (Far - Near);
	matrix[3][2] = (-1 * Far * Near) / (Far - Near);
	matrix[2][3] = 1;
	matrix[3][3] = 0;
}
void float4x4::Orthographic(float Width, float Height, float Near, float Far)
{
	Identity();

	matrix[0][0] = 2 / Width;
	matrix[1][1] = 2 / Height;
	matrix[2][2] = 1 / (Far - Near);
	matrix[3][2] = Near / (Near - Far);
}

void float4x4::DevideW()
{
	float W = matrix[3][3];
	matrix[0][0] /= W;
	matrix[1][1] /= W;
	matrix[3][3] /= W;
}
