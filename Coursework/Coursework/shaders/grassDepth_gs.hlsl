//Geometry shader that generates a triangle for every vertex.
Texture2D texture0 : register(t0);
Texture2D noiseTexture : register(t1);
Texture2D grassSpawnTexture : register(t2);

SamplerState Sampler0 : register(s0);
SamplerState Sampler1 : register(s1);

cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer GrassBuffer : register(b1)
{
    float time;
    float maxHeight;
    float width;
    float windStrength;
    
    float frequency;
    float spawnTreshold;
    float2 padding;
};

struct InputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float4 worldPosition : TEXCOORD1;
};

struct OutputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
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
    
    output.tex = uv;

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
    //float maxHeight = 2.f;
    float height = maxHeight; //Max Heigth of the grass blade.
    //float width = 0.5f;
    //float windStrength = 1.5f;
    //float frequency = 0.05f;
    /////////////////////////////////////
    
    //Frac wil return the fractional number of the input value, meaning it will always go between 0 and 1
    float2 uv = frac(input[0].tex + time * frequency);
   
    /**Sample the 2 values from the DuDv texture for the grass sway
    Substracting 0.5 will make it go forward in backwards, without it the grass its only pushed.*/
    float2 windTexture = texture0.SampleLevel(Sampler1, uv, 0) - 0.5f;
    
    //The amount that will be added to the position of the grass blade to simulate sway.
    float2 windFactor = float2(windTexture.x, windTexture.y) * windStrength;
    
    //Sample the value from the noise map and use it as the value for the rotation function.
    float randomRotation = noiseTexture.SampleLevel(Sampler0, input[0].tex, 0);
    float randomLocation = randomRotation - 0.5; //Use the same sampled value for the rotation but offset it by half so its back and forward.
    
    //Also use the same value sampled for the rotation and use it as a pseudorandom scalar for the height of the grass blades.
    height *= randomRotation;

    //Clamp the values so the grass its not too small.
    if (height < maxHeight / 3.f)
        height = maxHeight / 3.f;
    
   
    //Down right triangle
	//Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3(0.2 * width + randomLocation, 0, 0 + randomLocation), randomRotation), input, float2(1, 1));
    triStream.Append(output);
	//Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(1, 0.6f));
    triStream.Append(output);
	//Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3(-0.2 * width + randomLocation, 0.0, 0 + randomLocation), randomRotation), input, float2(0, 1));
    triStream.Append(output);
    triStream.RestartStrip();
    
    //Down left triangle
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3(-0.2 * width + randomLocation, 0.0, 0 + randomLocation), randomRotation), input, float2(0, 1));
    triStream.Append(output);
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(0.8f, 0.6f));
    triStream.Append(output);
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((-0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(0.2f, 0.6f));
    triStream.Append(output);
    triStream.RestartStrip();
    
    //Mid right triangle
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((-0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(0.2f, 0.6f));
    triStream.Append(output);
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(0.8f, 0.6f));
    triStream.Append(output);
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.1 + windFactor.x / 1.5f) * width + randomLocation, 0.8 * height, windFactor.y + randomLocation), randomRotation), input, float2(0.6f, 0.3f));
    triStream.Append(output);
    triStream.RestartStrip();

    //Mid left triangle
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.1 + windFactor.x / 1.5f) * width + randomLocation, 0.8 * height, windFactor.y + randomLocation), randomRotation), input, float2(0.6f, 0.3f));
    triStream.Append(output);
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((-0.1 + windFactor.x / 1.5f) * width + randomLocation, 0.8 * height, windFactor.y + randomLocation), randomRotation), input, float2(0.3f, 0.3f));
    triStream.Append(output);
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((-0.15 + windFactor.x / 3.f) * width + randomLocation, 0.4 * height, windFactor.y / 6.f + randomLocation), randomRotation), input, float2(0.2f, 0.6f));
    triStream.Append(output);
    triStream.RestartStrip();
    
    //Top right
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0.1 + windFactor.x / 1.5f) * width + randomLocation, 0.8 * height, windFactor.y + randomLocation), randomRotation), input, float2(0.6f, 0.3f));
    triStream.Append(output);
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((0 + windFactor.x * 1.5f) * width + randomLocation, 1.2 * height, windFactor.y * 2 + randomLocation), randomRotation), input, float2(0.5f, 0));
    triStream.Append(output);
    //Move the vertex away from the point position
    output = makeNewVertex(AddRotation(float3((-0.1 + windFactor.x / 1.5f) * width + randomLocation, 0.8 * height, windFactor.y + randomLocation), randomRotation), input, float2(0.3f, 0.3f));
    triStream.Append(output);
    
    
}


[maxvertexcount(15)]
void main(triangle InputType input[3], inout TriangleStream<OutputType> triStream)
{

    OutputType output;
    
    //Sample from a Noise map a value that will determine if grass blade spawns or not.
    float grassNoiseSpawn = grassSpawnTexture.SampleLevel(Sampler0, input[0].tex, 0);
    
    //Check with the sampled value if the grass blade should be generated or not.
    if (grassNoiseSpawn < spawnTreshold)
        drawGrassBlade(output, input, triStream);
    
    
}
