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

cbuffer ConstantBuffer : register(b0)
{
    float4x4 WorldViewProjection;
};


VS_OUTPUT TestSpriteShader_VS(VS_INPUT input)
{
    
    VS_OUTPUT output;
    
    output.POS = mul(input.POS, WorldViewProjection);
    output.TEX = input.TEX;
    return output;
}

cbuffer SpriteData : register(b1)
{
    float4 ResizeRatio;
}

Texture2D g_Texture : register(t0);
SamplerState g_Sampler : register(s0);

float4 TestSpriteShader_PS(VS_OUTPUT input) : SV_Target
{
    float2 TexLocation = float2(input.TEX.x * 0.5f, input.TEX.y * 0.5f);
    
    float4 texColor = g_Texture.Sample(g_Sampler, TexLocation);
    return texColor;
}
