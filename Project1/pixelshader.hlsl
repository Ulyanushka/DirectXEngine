struct PS_INPUT
{
    float4 outPosition : SV_POSITION;
    float3 outColor : COLOR;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return float4(input.outColor, 1.0f); //rgba
}
