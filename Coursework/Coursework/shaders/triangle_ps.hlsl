// Simple colour pixel shader

Texture2D texture0 : register(t0);
SamplerState Sampler0 : register(s0);

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};


float4 main(InputType input) : SV_TARGET
{
    float3 bottomColor = float3(0.0f, .3f, 0.f);
    float3 topColor = float3(0.0f, 1.0f, 0.f);

    //Subtracting a number to the lerp will make it lighter, adding will make it darker
    float3 lerpColor = lerp(topColor, bottomColor, input.tex.y+0.2f);
    
    return float4(lerpColor.xyz,1.0);
}