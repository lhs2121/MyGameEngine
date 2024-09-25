struct VS_INPUT
{
    float4 POS : POSITION;
};

struct VS_OUTPUT
{
    float4 POS : SV_POSITION;
};

cbuffer Transform : register(b0)
{
    float4x4 WorldViewProjection;
};

cbuffer Color : register(b1)
{
    float4 color;
}

VS_OUTPUT SimpleColor_VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    output.POS = mul(input.POS, WorldViewProjection);
    return output;
}

float4 SimpleColor_PS(VS_OUTPUT input) : SV_Target
{
    return color;
}
