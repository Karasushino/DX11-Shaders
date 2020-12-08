// Tessellation domain shader
// After tessellation the domain shader processes the all the vertices
Texture2D heightmapTexture : register(t0);
SamplerState displacementSampler : register(s0);


cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer HeightmapBuffer : register(b1)
{
    float amplitude;
    float3 padding;
}

struct InputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct OutputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 worldPosition : TEXCOORD1;
};

struct ConstantOutputType
{
    float edges[3] : SV_TessFactor;
    float inside : SV_InsideTessFactor;
};

[domain("tri")]
OutputType main(ConstantOutputType input, float3 uvwCoord : SV_DomainLocation, const OutputPatch<InputType, 3> patch)
{
    float3 vertexPosition;
    OutputType output;
    
   
    
 
    // Determine the position of the new vertex.
	// Invert the y and Z components of uvwCoord as these coords are generated in UV space and therefore y is positive downward.
	// Alternatively you can set the output topology of the hull shader to cw instead of ccw (or vice versa).
    vertexPosition = uvwCoord.x * patch[0].position + uvwCoord.y * patch[1].position + uvwCoord.z * patch[2].position;

    //Get texture
    float2 texturePosition = uvwCoord.x * patch[0].tex + uvwCoord.y * patch[1].tex + uvwCoord.z * patch[2].tex;

     
    float4 temp = heightmapTexture.SampleLevel(displacementSampler, texturePosition.xy, 0);
    float height = temp.y;
    vertexPosition.y = height * amplitude;
    
    

     // Calculate the position of the new vertex against the world, view, and projection matrices.
    output.position = mul(float4(vertexPosition, 1.0f), worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    
    output.worldPosition = mul(float4(vertexPosition, 1.0f), worldMatrix).xyz;
    
    return output;
}

