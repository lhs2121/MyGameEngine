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
    float4x4 matWorld;
    float4x4 matView;
    float4x4 matProjection;
};

cbuffer Color : register(b1)
{
    float4 color;
}

VS_OUTPUT BasicColorShaderr_VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    output.POS = mul(input.POS, matWorld);
    output.POS = mul(output.POS, matView);
    output.POS = mul(output.POS, matProjection);
    
    return output;
}

float4 BasicColorShaderr_PS(VS_OUTPUT input) : SV_Target
{
    return color;
}
