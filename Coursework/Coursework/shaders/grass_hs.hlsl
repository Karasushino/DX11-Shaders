// Tessellation Hull Shader
// Prepares control points for tessellation

struct InputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct OutputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct ConstantOutputType
{
    float edges[3] : SV_TessFactor;
    float inside : SV_InsideTessFactor;
};

cbuffer GrassDensityBuffer : register(b1)
{
    float density;
    float3 padding;
};


ConstantOutputType PatchConstantFunction(InputPatch<InputType, 3> inputPatch, uint patchId : SV_PrimitiveID)
{
    ConstantOutputType output;
    
 
    output.edges[0] = density;
    output.edges[1] = density;
    output.edges[2] = density;
     
    output.inside = density;
    
    return output;
}


[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(3)]
[patchconstantfunc("PatchConstantFunction")]
OutputType main(InputPatch<InputType, 3> patch, uint pointId : SV_OutputControlPointID, uint patchId : SV_PrimitiveID)
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