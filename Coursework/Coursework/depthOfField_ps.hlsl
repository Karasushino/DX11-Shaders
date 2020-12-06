Texture2D sceneTexture : register(t0);
Texture2D blurredTexture : register(t1);
Texture2D depthMap : register(t2);

SamplerState Sampler : register(s0);

cbuffer DOPBuffer : register(b0)
{
      float distance;
      float range;
      float nearPlane;
      float farPlane;
};

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 main(InputType input) : SV_TARGET
{
    //Sample Unblurred Pixel(Get pixel of the normal scene)
    float4 unbluredPixel = sceneTexture.Sample(Sampler, input.tex);
    
   // unbluredPixel = float4(0, 0, 1, 1);
    //Sample Blurred Pixel (Get blurred pixel of the blurred scene)
    float4 blurredPixel = blurredTexture.Sample(Sampler, input.tex);
    
   // blurredPixel = float4(1, 0, 0, 1);
    //Get Depth map Pixel value (The amount of Blur)
    float depthValue = depthMap.Sample(Sampler, input.tex);
    //Invert it, since the closest in depth map is black and we want 1 to be the closest instead (more blur)
    depthValue = 1 - depthValue;

    //Calculate Scene depth with near and far planes and depth value
    float sceneDepth = (-nearPlane * farPlane) / (depthValue - farPlane);
    
    //Scale of Blurring, the amount of blurring, the Alpha of the Lerp
    float blurScale = saturate(abs(sceneDepth - distance) / range);
    
    //Use the alpha of the blurScale to get 
    return saturate(lerp(unbluredPixel, blurredPixel, blurScale));
    
    
}
