Texture2D windSwayTexture : register(t0);
Texture2D noiseTexture : register(t1);
Texture2D grassSpawnTexture : register(t2);

SamplerState Sampler0 : register(s0);

cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer GrassBuffer : register(b1)
{
    float time;
    float3 padding;
};

struct InputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float4 worldPosition : TEXCOORD1;
};

struct OutputType
{
    float4 position : SV_POSITION;
    float4 depthPosition : TEXCOORD0;
};

//Converts to homegenous coords
OutputType makeNewVertex(float3 transformation, InputType input[3], float2 uv)
{
    OutputType output;
    
    // Move the vertex away from the point position
    output.position = input[0].worldPosition + float4(transformation.xyz, 0.f);
    output.position = mul(output.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    output.depthPosition = input[0].worldPosition + float4(transformation.xyz, 0.f);
    return output;
}

//** From Stackoverflow post (with a random number I could set a random rotation for each individual blade): https://stackoverflow.com/questions/22994596/how-to-get-my-current-culling-mode-directx11 */
float3 AddRotation(float3 pos, float rotationScalar)
{
    // This is the 3D position that we want to rotate:
    
// Specify the axis to rotate about:
    float x = 0.0;
    float y = 1.0;
    float z = 0.0;

    //Variable will be buffer
    float rotationAngle = 90.f;
    rotationAngle *= rotationScalar;
    //Conver to radiants and keep on 90 degree range
    float angle = rotationAngle * 3.141516f / 180.0; // 90 degrees, CCW

    
    float4 rotatedPos;
    rotatedPos.x = pos.x * (x * x * (1.0 - cos(angle)) + cos(angle))
    + pos.y * (x * y * (1.0 - cos(angle)) + z * sin(angle))
    + pos.z * (x * z * (1.0 - cos(angle)) - y * sin(angle));

    rotatedPos.y = pos.x * (y * x * (1.0 - cos(angle)) - z * sin(angle))
    + pos.y * (y * y * (1.0 - cos(angle)) + cos(angle))
    + pos.z * (y * z * (1.0 - cos(angle)) + x * sin(angle));

    rotatedPos.z = pos.x * (z * x * (1.0 - cos(angle)) + y * sin(angle))
    + pos.y * (z * y * (1.0 - cos(angle)) - x * sin(angle))
    + pos.z * (z * z * (1.0 - cos(angle)) + cos(angle));
    
    return rotatedPos;
}

void drawGrassBlade(OutputType output, InputType input[3], inout TriangleStream<OutputType> triStream)
{
    //Variables will be buffer
    float maxHeight = 9.f;
    float height = maxHeight;
    float width = 0.5f;
    float windStrength = 1.5f;
    float frequency = 0.05f;
    /////////////////////////////////////
    
    //Frac wil return the fractional number of the input value, meaning it will always go between 0 and 1
    float2 uv = frac(input[0].tex + time * frequency);
   
    //Substracting 0.5 will make it go forward in backwards, without it the grass its only pushed.
    float2 windTexture = windSwayTexture.SampleLevel(Sampler0, uv, 0) - 0.5f;
    
    float2 windFactor = float2(windTexture.x, windTexture.y) * windStrength;
    float randomRotation = noiseTexture.SampleLevel(Sampler0, input[0].tex, 0);
    float randomLocation = randomRotation - 0.5;
    
    height *= randomRotation;

    if (height < maxHeight/3)
    {
        height = maxHeight / 3;
    }
    
   
    //down right triangle
	// Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3(0.2 * width + randomLocation, 0, 0 + randomLocation), randomRotation), input, float2(1, 1));
    triStream.Append(output);
	// Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(1, 0.6f));
    triStream.Append(output);
	// Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3(-0.2 * width + randomLocation, 0.0, 0 + randomLocation), randomRotation), input, float2(0, 1));
    triStream.Append(output);
    triStream.RestartStrip();
    
    //down left triangle
    // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3(-0.2 * width + randomLocation, 0.0, 0 + randomLocation), randomRotation), input, float2(0, 1));
    triStream.Append(output);
    // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(0.8f, 0.6f));
    triStream.Append(output);
    // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((-0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(0.2f, 0.6f));
    triStream.Append(output);
    triStream.RestartStrip();
    
    //mid right triangle
     // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((-0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(0.2f, 0.6f));
    triStream.Append(output);
    // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(0.8f, 0.6f));
    triStream.Append(output);
    // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.1 + windFactor.x / 1.5f) * width + randomLocation, 0.8 * height, windFactor.y + randomLocation), randomRotation), input, float2(0.6f, 0.3f));
    triStream.Append(output);
    triStream.RestartStrip();

    //mid left triangle
     // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.1 + windFactor.x / 1.5f) * width + randomLocation, 0.8 * height, windFactor.y + randomLocation), randomRotation), input, float2(0.6f, 0.3f));
    triStream.Append(output);
    // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((-0.1 + windFactor.x / 1.5f) * width + randomLocation, 0.8 * height, windFactor.y + randomLocation), randomRotation), input, float2(0.3f, 0.3f));
    triStream.Append(output);
    // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((-0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(0.2f, 0.6f));
    triStream.Append(output);
    triStream.RestartStrip();
    
    //top right
    // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.1 + windFactor.x / 1.5f) * width + randomLocation, 0.8 * height, windFactor.y + randomLocation), randomRotation), input, float2(0.6f, 0.3f));
    triStream.Append(output);
    // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0 + windFactor.x * 1.5f) * width + randomLocation, 1.2 * height, windFactor.y * 2 + randomLocation), randomRotation), input, float2(0.5f, 0));
    triStream.Append(output);
    // Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((-0.1 + windFactor.x / 1.5f) * width + randomLocation, 0.8 * height, windFactor.y + randomLocation), randomRotation), input, float2(0.3f, 0.3f));
    triStream.Append(output);
    
    
}

///https://www.mathworks.com/matlabcentral/answers/108850-what-would-the-angles-be-for-a-3d-vector
float calculateStepnessFromNormal(InputType input[3])
{
    float angle = 0.f;
    
    float dotProd = dot(input[0].normal, float3(0, 0, 1));
    float lengthA = length(float3(0, 0, 1));
    float lenghtB = length(input[0].normal);
    
    
    
    angle = acos(dotProd / dot(lenghtB, lengthA));
    
 
 
    return angle;
}

[maxvertexcount(15)]
void main(triangle InputType input[3], inout TriangleStream<OutputType> triStream)
{

    OutputType output;
    
    float height = 2.f;
    
    //float maxAngleToSpawnGrass = 1.f;
    //float slopeAngle = calculateStepnessFromNormal(input);
    
    
    ////Draw the grass blade on the vertex. With a random value later we can edit if it spawns or not
    //if (maxAngleToSpawnGrass > slopeAngle)
    float grassNoiseSpawn = grassSpawnTexture.SampleLevel(Sampler0, input[0].tex, 0);
    float spawnTreshold = 0.7f;
    
    if (grassNoiseSpawn < spawnTreshold)
        drawGrassBlade(output, input, triStream);
    
    
}
