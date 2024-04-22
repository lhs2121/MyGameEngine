cbuffer ConstantBuffer : register(b0)
{
    float4x4 WorldViewProjection; 
};

struct VS_INPUT
{
    float4 POS : POSITION;
    float4 COLOR : COLOR;
};

struct VS_OUTPUT
{
    float4 POS : SV_POSITION; 
    float4 COLOR : COLOR;
};

VS_OUTPUT TestShader_VS(VS_INPUT Input)
{
    VS_OUTPUT Output;
    Output.POS = mul(Input.POS, WorldViewProjection);
    Output.COLOR = Input.COLOR;
    return Output;
}

float4 TestShader_PS(VS_OUTPUT Input) : SV_Target
{
    return Input.COLOR;
}
