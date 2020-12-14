Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

cbuffer ScreenSizeBuffer : register(b0)
{
    float screenWidth;
    float3 padding;
};

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 main(InputType input) : SV_TARGET
{
    float totalWeight = 0.0f;
    float weights[5];
    float4 colour;

	// Create the weights that each neighbor pixel will contribute to the blur.
    //weights[0] = 0.382928f;
    //weights[1] = 0.241732f;
    //weights[2] = 0.060598f;
    //weights[3] = 0.005977f;
    //weights[4] = 0.000229f;
    
    weights[0] = 0.1f;
    weights[1] = 0.1f;
    weights[2] = 0.1f;
    weights[3] = 0.1f;
    weights[4] = 0.1f;
    
    for (int i = 0; i < 5.f; i++)
    {
        totalWeight += weights[i];
    }
    if (totalWeight > 1.0f)
    {
        //Pink means wieghts not equal to 1
        return colour = float4(0.8f, 0.0f, 0.9, 1.0f);
    }
    
    
	// Initialize the colour to black.
    colour = float4(0.0f, 0.0f, 0.0f, 0.0f);

    float texelSize = 1.0f / screenWidth;
    // Add the horizontal pixels to the colour by the specific weight of each.
    
    
    // Add the vertical pixels to the colour by the specific weight of each.
    for (int i = 1; i < 5; i++)
    {
        colour += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * -i,0.0f )) * weights[i];
        colour += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * i, 0.0f)) * weights[i];

    }
    colour += shaderTexture.Sample(SampleType, input.tex) * weights[0];
    
    
    
    
    //colour += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * -4.0f, 0.0f)) * weights[4];
    //colour += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * -3.0f, 0.0f)) * weights[3];
    //colour += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * -2.0f, 0.0f)) * weights[2];
    //colour += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * -1.0f, 0.0f)) * weights[1];
    //colour += shaderTexture.Sample(SampleType, input.tex) * weights[0];
    //colour += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * 1.0f, 0.0f)) * weights[1];
    //colour += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * 2.0f, 0.0f)) * weights[2];
    //colour += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * 3.0f, 0.0f)) * weights[3];
    //colour += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * 4.0f, 0.0f)) * weights[4];

	// Set the alpha channel to one.
    colour.a = 1.0f;

    return colour;
}
