struct VSInput
{
    float3 position : POSITION; // ���ؽ� ��ġ
};

struct VSOutput
{
    float3 position : SV_POSITION; // ��ũ�� ��ǥ
};

VSOutput main(VSInput input)
{
    VSOutput output;
    output.position = input.position;
    return output;
}