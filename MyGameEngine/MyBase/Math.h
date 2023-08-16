#pragma once

class vec4
{
public:
	vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 1) : x(_x), y(_y), z(_z), w(_w)
	{

	}
	float x;
	float y;
	float z;
	float w;
};

class matrix4x4
{
public:
	matrix4x4()
	{
		identity();
	}

	float matrix[4][4];

	void identity()
	{
		for (int a = 0; a < 4; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				a == b ? matrix[a][b] = 1 : matrix[a][b] = 0;
			}
		}
	}

	matrix4x4 operator+(matrix4x4 _other)
	{
		matrix4x4 result;
		for (int a = 0; a < 4; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				result.matrix[a][b] = matrix[a][b] + _other.matrix[a][b];
			}
		}

		return result;
	}

};