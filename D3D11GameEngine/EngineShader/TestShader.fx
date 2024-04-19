cbuffer ConstantBuffer : register(b0)
{
    float4x4 WorldViewProjection; 
};

struct VS_INPUT
{
    float4 pos : POSITION;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION; 
};

VS_OUTPUT TestShader_VS(VS_INPUT Input)
{
    VS_OUTPUT Output;
    Output.pos = mul(Input.pos, WorldViewProjection);
    return Output;
}

float4 TestShader_PS(VS_OUTPUT Input) : SV_Target
{
    return float4(1, 1, 1, 1);
}
