
//�ø�ƽ
//�Լ� ���� ������ �Լ���ȯ���� �ǹ�
//���� ���� ������ ���ڸ� �ǹ�
//�ڿ� 0,1�� ������ �������ǹ�
//�̸��� ������ ������ ������ �ø�ƽ�� ��� �Ǵ� �迭�� ���� �� �ִ�
//POS0, POS1, POS2, POS3 �� float4[4]�� �ްų� float4x4�� �������ִ�

float maxBlockCountX = 100;

struct quad
{
    float4 pos : POSITION;
    float2 offset : OFFSET;
    float2 scale : SCALE;
    float uv : TEXCOORD;
    float blockNumber : BLOCKNUMBER;
};
cbuffer viewProjection : register(b0)
{
    float4x4 viewProjectionMatrix;
}

Texture2D spriteAtlas : register(t0);
SamplerState pointSampler : register(s0);


float4 vs_main(quad input) : SV_POSITION
{
    float4 result;
    input.pos.xy *= input.scale.xy; // ���� �������� �ø���
    input.pos.xy += input.offset.xy; // ���� �������� �̵���Ű��
    
    result = mul(input.pos, viewProjectionMatrix);
    return result;
}

float4 ps_main(float4 pixel)
{
    spriteAtlas.Sample(pointSampler, maxBlockCountX);
    return float4(1, 0, 0, 1);
}

//Sample�Լ��� ����ȭ�� �ؽ�ó���� �ȼ��ϳ��� �̾Ƴ�
//�ι�°���ڴ� �ݵ�� ����ȭ�� ��ǥ�� �־����
//��ǥ��� uv��ǥ��� 0,0�� ��������

//������� �ؽ�ó�� 1000x500�̴�
//�׷� �� �ؽ�ó�� 1x1�� ���ΰ� ����ȭ�� �ؽ�ó��
//�ű⼭ ����;���
//������� 1000x500�ؽ�ó�� �߾��� �ȼ��� ���������
//�߾��� uv��ǥ�� k����Ҷ� k�� 500,250�̴�
//�׷� k�� x��ǥ�� �ؽ�ó�� �غ����� ������ y��ǥ�� ���̷� ������
// k = 500/1000 , 250/500
//�� k = 1/2 , 1/2
//����ȭ �Ϸ�
//������ �츮�� ����� ����;���
//�׷��⶧���� ��Ʋ�󽺿� ���� �� ��Ͽ� ��ȣ�� �ű��
//������� 0�� ����� ���� ���� ��ܿ� ��ġ�� ����̴�
//��Ϲ�ȣ�� �ϴ� ���̴��� �ڿ����� �����´�
//�׸��� ��Ʋ���� ���ο� �ִ� ��� ����� ����ɼ��ִ��� �˾ƾ���
//������� ��ϱ��̸� 10X10���� �׷ȴٰ�����
//�׷� ���ο� 100���� ����� ����
//�׸��� ���ο��� 50���� ����� ����
//�׷� ��Ϲ�ȣ�� 99��� �����ʻ�� ����̴�
//��Ϲ�ȣ�� 100�̶�� ���� 2�� ����ϰ��̴�
//���⼭ ������ ���غ���
//���� 345�� ����� ����
//�׷� 345/100�� ���� 3�̰� �������� 45��
//�׷� �� 3�� ���ϴ°� 3��° ���̶�� ����
//�״��� �������� 45�ϱ�
//3�࿡�� 45��° ����� ��������
//�� y��ǥ�� block������ * 3 = 30
//x��ǥ�� block������ * 45 = 30
//������ row = blockNumber / maxBlockCountX, col = blockNumber % maxBlockCountX �̷��� ������
//�״��� ������ǥ�� (blockSize * col, blockSize * row);
//�̰� ����ȭ��Ű�� (blockSize * col / �ؽ�ó ���α���, blockSize * row / �ؽ�ó ���α���)
//�̷��Ե�
//�ٵ� �̰� ���̴����ؼ��ϴ°Ը³�?
//�׳� �ۿ����ָ�Ǵ°žƴѰ�
//BLOCKNUMBER�� ���̴��� �����ϴ´��
//�ƿ� 
