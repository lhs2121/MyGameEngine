cbuffer ConstantBuffer : register(b0)
{
    float4x4 WorldViewProjection;
};

struct VS_INPUT
{
    float4 POS : POSITION;
};

struct VS_OUTPUT
{
    float4 POS : SV_POSITION;
};

VS_OUTPUT Test2DShader_VS(VS_INPUT Input)
{
    VS_OUTPUT Output;
    Output.POS = mul(Input.POS, WorldViewProjection);
    return Output;
}

float4 Test2DShader_PS(VS_OUTPUT Input) : SV_Target
{
    return float4(1, 1, 1, 1);
}
