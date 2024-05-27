cbuffer ConstantBuffer : register(b0)
{
    float4x4 WorldViewProjection;
};

struct VS_INPUT
{
    float4 POS : POSITION;
    float2 TEXCOORD : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 POS : SV_POSITION;
    float2 TEXCOORD : TEXCOORD;
};

VS_OUTPUT TestSpriteShader_VS(VS_INPUT Input)
{
    VS_OUTPUT Output;
    Output.POS = mul(Input.POS, WorldViewProjection);
    Output.TEXCOORD = Input.TEXCOORD;
    return Output;
}

sampler2D DiffuseSampler;

float4 TestSpriteShader_PS(VS_OUTPUT Input) : SV_Target
{
    float4 TexColor = tex2D(DiffuseSampler, Input.TEXCOORD);
    return TexColor;
}
