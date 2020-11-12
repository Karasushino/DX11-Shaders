// Tessellation Hull Shader
// Prepares control points for tessellation

cbuffer HullBuffer : register(b0)
{
    float4 EdgeTesellation;
    float2 InsideTesellation;
}
cbuffer HullCameraBuffer : register(b1)
{
    float3 cameraPosition;
    float padding;
}


struct InputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct ConstantOutputType
{
    float edges[4] : SV_TessFactor;
    float inside[2] : SV_InsideTessFactor;
};

struct OutputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

ConstantOutputType PatchConstantFunction(InputPatch<InputType, 4> inputPatch, uint patchId : SV_PrimitiveID)
{    
    ConstantOutputType output;
    float3 avgPos = inputPatch[0].position;
    avgPos += inputPatch[1].position;
    avgPos += inputPatch[2].position;
    avgPos += inputPatch[3].position;

    avgPos /= 4.0f;

   
    float3 distanceFromPlane = distance(cameraPosition, avgPos);
    



    
    //// Set the tessellation factors for the three edges of the triangle.
    //output.edges[0] = clamp(30 * EdgeTesellation.x / distanceFromPlane, 1, 64);
    //output.edges[1] = clamp(30 * EdgeTesellation.x / distanceFromPlane, 1, 64);
    //output.edges[2] = clamp(30 * EdgeTesellation.x / distanceFromPlane, 1, 64);
    //output.edges[3] = clamp(30 * EdgeTesellation.x / distanceFromPlane, 1, 64);

    //// Set the tessellation factor for tessallating inside the triangle.
    //output.inside[0] = clamp(30 * EdgeTesellation.x / distanceFromPlane, 1, 64);
    //output.inside[1] = clamp(30 * EdgeTesellation.x / distanceFromPlane, 1, 64);
    
    
     output.edges[0] = clamp(EdgeTesellation.x , 1, 64);
    output.edges[1] = clamp(EdgeTesellation.x, 1, 64);
 output.edges[2] = clamp(EdgeTesellation.x, 1, 64);
    output.edges[3] = clamp(EdgeTesellation.x, 1, 64);

   // Set the tessellation factor for tessallating inside the triangle.
    output.inside[0] = clamp(EdgeTesellation.x, 1, 64);
    output.inside[1] = clamp(EdgeTesellation.x, 1, 64);
    

    return output;
}


[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(4)]
[patchconstantfunc("PatchConstantFunction")]
OutputType main(InputPatch<InputType, 4> patch, uint pointId : SV_OutputControlPointID, uint patchId : SV_PrimitiveID)
{
    OutputType output;


    // Set the position for this control point as the output position.
    output.position = patch[pointId].position;

    // Set the input colour as the output colour.
   // Store the texture coordinates for the pixel shader.
    output.tex = patch[pointId].tex;

    output.normal = patch[pointId].normal;
    

    return output;
}