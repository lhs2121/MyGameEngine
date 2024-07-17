#pragma once
#include <BaseLib\EngineMath.h>

struct VERTEX_POS
{
	float4 Pos;
};

struct VERTEX_POS_COLOR
{
	float4 Pos;
	float4 Color;
};
struct VERTEX_POS_TEXCOORD
{
	float4 Pos;
	float TexX;
	float TexY;
};