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
    float3 normal : NORMAL;
};

struct OutputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
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

    //Get normals
    float3 normalPosition = uvwCoord.x * patch[0].normal + uvwCoord.y * patch[1].normal + uvwCoord.z * patch[2].normal;
    
     
    float4 temp = heightmapTexture.SampleLevel(displacementSampler, texturePosition.xy, 0);
    float height = temp.y;
    vertexPosition.y = height * amplitude;
    
    // Recalculate normals for a Heightmap
    /**Source: Introduction to 3D Game Programming with DirectX11 by Frank D.Luna. Page:614-615*/
    
    //Size of the plane used to get Texel.
    float planeSize = 120.f;
    
    //Calculate neighbouring coordinates
    float2 leftC = texturePosition - float2(1.f / planeSize, 0.0f);
    float2 rightC = texturePosition - float2(-1.f / planeSize, 0.0f);
    float2 bottomC = texturePosition - float2(0.0f, 1.f / planeSize);
    float2 topC = texturePosition - float2(0.0f, -1.f / planeSize);
    
    //Sample neighbouring heightmap Y texture values
    float leftY = heightmapTexture.SampleLevel(displacementSampler, leftC, 0).r;
    float rightY = heightmapTexture.SampleLevel(displacementSampler, rightC, 0).r;
    float bottomY = heightmapTexture.SampleLevel(displacementSampler, bottomC, 0).r;
    float topY = heightmapTexture.SampleLevel(displacementSampler, topC, 0).r;
    
    
    //Get Directional vector between right and left and get tangent.
    float3 tangent = normalize(float3(2.0f * (1.0f / 120.0f), (rightY - leftY), 0.0f));
    //Get Directional vector between top and bottom and get tangent.
    float3 bitan = normalize(float3(0.0f, (bottomY - topY), -2.0f * (1.0f / 120.0f)));
    
    //Get tangent and bitan and cross product them to get normal. 
    normalPosition = cross(tangent, bitan);
    
    
    
    //Set up variables for Geometry shader stage.
    output.tex = texturePosition;
    // Calculate the normal vector against the world matrix only and normalise.
    output.normal = mul(normalPosition, (float3x3) worldMatrix);
    output.normal = normalize(output.normal);
    // Calculate the position of the new vertex against the world, view, and projection matrices.
    output.position = mul(float4(vertexPosition, 1.0f), worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    
    output.worldPosition = mul(float4(vertexPosition, 1.0f), worldMatrix).xyz;
    
    return output;
}

