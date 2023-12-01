struct VSInput
{
    float3 position : POSITION; // 버텍스 위치
};

struct VSOutput
{
    float3 position : SV_POSITION; // 스크린 좌표
};

VSOutput main(VSInput input)
{
    VSOutput output;
    output.position = input.position;
    return output;
}