// Tessellation Hull Shader
// Prepares control points for tessellation

cbuffer HullCameraBuffer : register(b1)
{
    float3 cameraPosition;
    float padding;
}

cbuffer TessellationBuffer : register(b0)
{
    float tessellationFactor;
    float dynamicTessellationFactor;
    int dynmaicTessellationToggle;
    float distanceScalar;
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
    

    //If dynamic Tessellation is ON
    if (dynmaicTessellationToggle == 1)
    {
        
        //Get the middle point of the patch points
        float3 avgPos = inputPatch[0].position;
        avgPos += inputPatch[1].position;
        avgPos += inputPatch[2].position;
        avgPos += inputPatch[3].position;
        avgPos /= 4.0f;
        
        //Get the distance from the Plane.
        float3 distanceFromPlane = distance(cameraPosition, avgPos);
    
        output.edges[0] = clamp(distanceScalar / distanceFromPlane * dynamicTessellationFactor, 1, 64);
        output.edges[1] = clamp(distanceScalar / distanceFromPlane * dynamicTessellationFactor, 1, 64);
        output.edges[2] = clamp(distanceScalar / distanceFromPlane * dynamicTessellationFactor, 1, 64);
        output.edges[3] = clamp(distanceScalar / distanceFromPlane * dynamicTessellationFactor, 1, 64);

        // Set the tessellation factor for tessallating inside the triangle.
        output.inside[0] = clamp(distanceScalar / distanceFromPlane * dynamicTessellationFactor, 1, 64);
        output.inside[1] = clamp(distanceScalar / distanceFromPlane * dynamicTessellationFactor, 1, 64);
    }
    else
    {
        output.edges[0] = clamp(tessellationFactor, 1, 64);
        output.edges[1] = clamp(tessellationFactor, 1, 64);
        output.edges[2] = clamp(tessellationFactor, 1, 64);
        output.edges[3] = clamp(tessellationFactor, 1, 64);

        // Set the tessellation factor for tessallating inside the triangle.
        output.inside[0] = clamp(tessellationFactor, 1, 64);
        output.inside[1] = clamp(tessellationFactor, 1, 64);
    }
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


    //Pass the position for this control point as the output position.
    output.position = patch[pointId].position;

    //Pass the texture coordinates.
    output.tex = patch[pointId].tex;

    //Pass the normals.
    output.normal = patch[pointId].normal;
    
    return output;
}