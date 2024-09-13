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


VS_OUTPUT DebugLine_VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    output.POS = mul(input.POS, WorldViewProjection);
    return output;
}

float4 DebugLine_PS(VS_OUTPUT input) : SV_Target
{
    return float4(0, 1, 0, 1);
}
