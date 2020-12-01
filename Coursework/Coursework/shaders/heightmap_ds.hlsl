// Tessellation domain shader
// After tessellation the domain shader processes the all the vertices
Texture2D heightmapTexture : register(t0);
SamplerState displacementSampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    matrix lightViewMatrix;
    matrix lightProjectionMatrix;
};

cbuffer HeighmapBuffer : register(b1)
{
    float amplitude;
    float3 padding;
};

struct ConstantOutputType
{
    float edges[4] : SV_TessFactor;
    float inside[2] : SV_InsideTessFactor;
};

struct InputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct OutputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 worldPosition : TEXCOORD1;
    float4 lightViewPos : TEXCOORD2;
};

[domain("quad")]
OutputType main(ConstantOutputType input, float2 uvwCoord : SV_DomainLocation, const OutputPatch<InputType, 4> patch)
{
    float3 vertexPosition;
    OutputType output;
    
   
    
 
    // Determine the position of the new vertex.
	// Invert the y and Z components of uvwCoord as these coords are generated in UV space and therefore y is positive downward.
	// Alternatively you can set the output topology of the hull shader to cw instead of ccw (or vice versa).
    float3 v1 = lerp(patch[0].position, patch[1].position, uvwCoord.y);
    float3 v2 = lerp(patch[3].position, patch[2].position, uvwCoord.y);
    vertexPosition = lerp(v1, v2, uvwCoord.x); 
   

    //Get texture
    float2 t1 = lerp(patch[0].tex, patch[1].tex, uvwCoord.y);
    float2 t2 = lerp(patch[3].tex, patch[2].tex, uvwCoord.y);
    float2 texturePosition = lerp(t1, t2, uvwCoord.x);

   

    //Get normals
    float3 n1 = lerp(patch[0].normal, patch[1].normal, uvwCoord.y);
    float3 n2 = lerp(patch[3].normal, patch[2].normal, uvwCoord.y);
    float3 normalPosition = lerp(n1, n2, uvwCoord.x);
    
    // Recalculate normals for a Heightmap
    /**Source: Introduction to 3D Game Programming with DirectX11 by Frank D.Luna. Page:614-615*/
    //Calculate neighbouring coordinates
    
    float2 leftC = texturePosition - float2(-1.f / 120.f, 0.0f);
    float2 rightC = texturePosition - float2(1.f / 120.f, 0.0f);
    float2 bottomC = texturePosition - float2(0.0f, 1.f / 120.f);
    float2 topC = texturePosition - float2(0.0f, -1.f / 120.f);
    
    //Sample neighbouring heightmap Y texture values
    float leftY = heightmapTexture.SampleLevel(displacementSampler, leftC, 0).r;
    float rightY = heightmapTexture.SampleLevel(displacementSampler, rightC, 0).r;
    float bottomY = heightmapTexture.SampleLevel(displacementSampler, bottomC, 0).r;
    float topY = heightmapTexture.SampleLevel(displacementSampler, topC, 0).r;
    
    //Get tange nt and bitan and cross product them to get normal. 
    //Get Directional vector between right and left and get tangent.
    float3 tangent = normalize(float3(2.0f * (1.0f / 120.0f), (rightY - leftY), 0.0f));
    //Get Directional vector between top and bottom and get tangent.
    float3 bitan = normalize(float3(0.0f, (bottomY- topY), -2.0f * (1.0f / 120.0f)));
    float3 normal = cross(tangent, bitan);
    

    
    normalPosition = normal;
    
     
    float4 temp = heightmapTexture.SampleLevel(displacementSampler, texturePosition.xy, 0);
    float height = temp.y;
    vertexPosition.y = height * amplitude;
    
    
    //All jumowombo preparation
    output.tex = texturePosition;
    // Calculate the normal vector against the world matrix only and normalise.
    output.normal = mul(normalPosition, (float3x3) worldMatrix);
    output.normal = normalize(output.normal);
     // Calculate the position of the new vertex against the world, view, and projection matrices.
    output.position = mul(float4(vertexPosition, 1.0f), worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    output.lightViewPos = mul(float4(vertexPosition, 1.0f), worldMatrix);
    output.lightViewPos = mul(output.lightViewPos, lightViewMatrix);
    output.lightViewPos = mul(output.lightViewPos, lightProjectionMatrix);
    
    
    output.worldPosition = mul(float4(vertexPosition, 1.0f), worldMatrix).xyz;
    
    return output;
}   

