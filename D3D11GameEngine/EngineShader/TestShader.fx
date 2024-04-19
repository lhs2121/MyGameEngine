cbuffer Transform : register(b0)
{
    float4x4 WorldViewProjection;
};

struct VSInput
{
    float4 pos : POSITION;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
};


VSOutput TestShader_VS(VSInput _Input)
{
    VSOutput Output = (VSOutput)0;
    Output.pos = mul(_Input.pos, WorldViewProjection);
    
    return Output;
}

float4 TestShader_PS(VSOutput _Input) : SV_TARGET
{
    return float4(1,1,1,1);
}