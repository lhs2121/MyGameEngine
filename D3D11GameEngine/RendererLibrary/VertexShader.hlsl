
//시멘틱
//함수 옆에 있으면 함수반환값을 의미
//인자 옆에 있으면 인자를 의미
//뒤에 0,1이 붙으면 슬롯을의미
//이름은 같지만 슬롯이 나눠진 시멘틱은 행렬 또는 배열로 받을 수 있다
//POS0, POS1, POS2, POS3 은 float4[4]로 받거나 float4x4로 받을수있다

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
    input.pos.xy *= input.scale.xy; // 쿼드 로컬정점 늘리기
    input.pos.xy += input.offset.xy; // 쿼드 로컬정점 이동시키기
    
    result = mul(input.pos, viewProjectionMatrix);
    return result;
}

float4 ps_main(float4 pixel)
{
    spriteAtlas.Sample(pointSampler, maxBlockCountX);
    return float4(1, 0, 0, 1);
}

//Sample함수는 정규화된 텍스처에서 픽셀하나를 뽑아냄
//두번째인자는 반드시 정규화된 좌표를 넣어야함
//좌표계는 uv좌표계라서 0,0이 왼쪽위임

//예를들어 텍스처가 1000x500이다
//그럼 이 텍스처를 1x1로 줄인게 정규화된 텍스처다
//거기서 갖고와야함
//예를들어 1000x500텍스처의 중앙의 픽셀을 갖고오려면
//중앙의 uv좌표를 k라고할때 k는 500,250이다
//그럼 k의 x좌표를 텍스처의 밑변으로 나누고 y좌표는 높이로 나눈다
// k = 500/1000 , 250/500
//즉 k = 1/2 , 1/2
//정규화 완료
//하지만 우리는 블록을 갖고와야함
//그렇기때문에 아틀라스에 속한 각 블록에 번호를 매긴다
//예를들어 0번 블록은 가장 왼쪽 상단에 위치한 블록이다
//블록번호를 일단 쉐이더에 자원으로 가져온다
//그리고 아틀라스의 가로에 최대 몇개의 블록이 적재될수있는지 알아야함
//예를들어 블록길이를 10X10으로 그렸다고하자
//그럼 가로에 100개의 블록이 들어간다
//그리고 세로에는 50개의 블록이 들어간다
//그럼 블록번호가 99라면 오른쪽상단 블록이다
//블록번호가 100이라면 좌측 2행 블록일것이다
//여기서 공식을 구해보면
//내가 345번 블록을 원함
//그럼 345/100의 몫은 3이고 나머지는 45임
//그럼 이 3이 뜻하는건 3번째 행이라는 뜻임
//그다음 나머지가 45니까
//3행에서 45번째 블록을 가져오됨
//즉 y좌표는 block사이즈 * 3 = 30
//x좌표는 block사이즈 * 45 = 30
//공식은 row = blockNumber / maxBlockCountX, col = blockNumber % maxBlockCountX 이렇게 형성됨
//그다음 실제좌표는 (blockSize * col, blockSize * row);
//이걸 정규화시키면 (blockSize * col / 텍스처 가로길이, blockSize * row / 텍스처 세로길이)
//이렇게됨
//근데 이걸 쉐이더안해서하는게맞나?
//그냥 밖에서주면되는거아닌가
//BLOCKNUMBER를 쉐이더에 전달하는대신
//아예 
