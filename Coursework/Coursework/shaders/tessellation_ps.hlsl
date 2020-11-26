Texture2D heightmapTexture : register(t0);
SamplerState Sampler0 : register(s0);

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float4 worldPosition : TEXCOORD1;
};


float4 main(InputType input) : SV_TARGET
{
    float4 temp = heightmapTexture.SampleLevel(Sampler0, input.tex.xy, 0);
    float height = temp.y;
    
    float waterLevel = height - input.worldPosition.y;
    
    float4 deepColor = float4(0.13f, 0.13f, 0.8f, 0.9f);
    float4 shallowColor = float4(0.82f, 0.82f, 0.82f, 0.7f);
    
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
    float4 waterColor = lerp(shallowColor, deepColor, waterLevel);
    return waterColor;
}