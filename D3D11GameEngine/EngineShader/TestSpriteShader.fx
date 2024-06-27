cbuffer ConstantBuffer : register(b0)
{
    float4x4 WorldViewProjection;
};

struct VS_INPUT
{
    float4 POS : POSITION;
    float2 TEX : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 POS : SV_Position;
    float2 TEX : TEXCOORD;
};

VS_OUTPUT TestSpriteShader_VS(VS_INPUT input)
{
    
    VS_OUTPUT output;
    
    output.POS = mul(input.POS, WorldViewProjection);
    output.TEX = input.TEX;
    return output;
}

Texture2D g_Texture : register(t0);
SamplerState g_Sampler : register(s0);

float4 TestSpriteShader_PS(VS_OUTPUT input) : SV_Target
{
    float4 texColor = g_Texture.Sample(g_Sampler, input.TEX);
    return texColor;
}
