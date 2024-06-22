cbuffer ConstantBuffer : register(b0)
{
    float4x4 WorldViewProjection;
};
Texture2D g_Texture : register(t0);
SamplerState g_Sampler : register(s0);

struct VS_Input
{
    float4 POSITION : POSITION;
    float2 TEXCOORD : TEXCOORD;
};
struct PS_Output
{
    float4 COLOR : SV_POSITION;
};
PS_Output TestSpriteShader_VS(VS_Input input)
{
    PS_Output output;
    
    output.COLOR = float4(input.TEXCOORD.xy, 0.0f, 1.0f);
    
    return output;
}
float4 TestSpriteShader_PS(PS_Output input) : SV_Target
{
    float4 texColor = g_Texture.Sample(g_Sampler, input.COLOR.xy);
    return texColor;
}
