struct VS_INPUT
{
    float4 POS : POSITION;
};

struct VS_OUTPUT
{
    float4 POS : SV_Position;
};

cbuffer Transform : register(b0)
{
    float4x4 WorldViewProjection;
};


VS_OUTPUT CollisionShader_VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    output.POS = mul(input.POS, WorldViewProjection);
    return output;
}

float4 LineColor = float4(1.0, 0.0, 0.0, 1.0);
float LineThickness = 1.0; // 외곽선 두께

float4 CollisionShader_PS(VS_OUTPUT input) : SV_Target
{
     // 픽셀의 위치를 화면 공간에서 가져옵니다.
    float2 screenPos = (input.POS.xy / input.POS.w) * 0.5 + 0.5;
    
    // 네모의 외곽선에 해당하는 조건을 정의합니다.
    float2 boxMin = float2(0.1, 0.1); // 네모의 좌하단 좌표
    float2 boxMax = float2(0.9, 0.9); // 네모의 우상단 좌표

    // 외곽선 판별: 네모의 경계에 가까운 픽셀을 외곽선으로 판별합니다.
    float2 borderDist = min(abs(screenPos - boxMin), abs(screenPos - boxMax));
    float isBorder = max(max(borderDist.x, borderDist.y) - LineThickness / 2.0, 0.0);
    
    // 외곽선이 아닌 경우는 배경색으로 처리합니다.
    float4 backgroundColor = float4(0.0, 0.0, 0.0, 1.0); // 배경색
    float4 color = lerp(backgroundColor, LineColor, 1.0 - isBorder);
    
    return color;
}
