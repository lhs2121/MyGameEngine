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
    PSInput Output;
    Output.pos = _Input.pos;
    
    return Output;
}

float4 TestShader_PS(PSInput _Input) : SV_TARGET
{
	return float4(0.7f, 0.2f, 0.34f, 1.0f);
}