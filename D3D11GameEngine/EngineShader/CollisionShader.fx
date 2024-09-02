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
float LineThickness = 1.0; // �ܰ��� �β�

float4 CollisionShader_PS(VS_OUTPUT input) : SV_Target
{
     // �ȼ��� ��ġ�� ȭ�� �������� �����ɴϴ�.
    float2 screenPos = (input.POS.xy / input.POS.w) * 0.5 + 0.5;
    
    // �׸��� �ܰ����� �ش��ϴ� ������ �����մϴ�.
    float2 boxMin = float2(0.1, 0.1); // �׸��� ���ϴ� ��ǥ
    float2 boxMax = float2(0.9, 0.9); // �׸��� ���� ��ǥ

    // �ܰ��� �Ǻ�: �׸��� ��迡 ����� �ȼ��� �ܰ������� �Ǻ��մϴ�.
    float2 borderDist = min(abs(screenPos - boxMin), abs(screenPos - boxMax));
    float isBorder = max(max(borderDist.x, borderDist.y) - LineThickness / 2.0, 0.0);
    
    // �ܰ����� �ƴ� ���� �������� ó���մϴ�.
    float4 backgroundColor = float4(0.0, 0.0, 0.0, 1.0); // ����
    float4 color = lerp(backgroundColor, LineColor, 1.0 - isBorder);
    
    return color;
}
