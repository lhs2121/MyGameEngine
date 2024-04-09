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

float4 TestShader_PS(PSInput _Input) : SV_TARGET0
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}