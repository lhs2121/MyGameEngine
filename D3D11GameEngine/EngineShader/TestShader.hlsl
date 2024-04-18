cbuffer Transform : register(b0)
{
    float4x4 WorldViewProjection;
};

struct VSInput
{
    float4 pos : POSITION;
};

struct PSInput
{
    float4 pos : SV_POSITION;
};


PSInput TestShader_VS(VSInput _Input)
{
    PSInput Output = (PSInput)0;
    Output.pos = mul(_Input.pos, WorldViewProjection);
    
    return Output;
}

float4 TestShader_PS(PSInput _Input) : SV_TARGET
{
    return float4(0.25f, 0.5f, 0.69f, 1.0f);
}