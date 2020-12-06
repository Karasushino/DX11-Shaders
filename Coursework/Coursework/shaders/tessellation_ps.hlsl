Texture2D heightmapTexture : register(t1);
SamplerState Sampler0 : register(s0);


cbuffer WaterBuffer : register(b1)
{
    float heightmapAmplitude;
    float waterPlaneHeight;
    float offset;
    float depthScalar;
};


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
    float height = temp.y * heightmapAmplitude;
    
    float waterheightCPU = waterPlaneHeight;
    //Treshold for depthness
    //float offset = 4.3f;
    
    float offsetLevel = waterheightCPU + offset;
    
    float waterLevel = input.worldPosition.y - height - offsetLevel;
    
    float4 deepColor = float4(0.13f, 0.13f, 0.8f, 0.6f);
    float4 shallowColor = float4(0.1f, 0.9f, 0.9f, 0.2f);
    
    
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
        float4 waterColor = saturate(lerp(shallowColor, deepColor, waterLevel / depthScalar));
    
    return waterColor;
}