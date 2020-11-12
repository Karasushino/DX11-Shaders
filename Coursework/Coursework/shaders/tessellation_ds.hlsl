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

cbuffer WaveBuffer : register(b1)
{
   
    // x = time;
    //y = amplitude;
    //z =  frequency;
    //w = speed;
    
    float4 waveSettings;
    float3 WaveDirection;
    float WaveSmoothness;
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
};

struct WaveCalculations
{
    float3 vertexPosition;
    float3 normal;
};

WaveCalculations CalculateWaves(float4 vertexPositions);

[domain("quad")]
OutputType main(ConstantOutputType input, float2 uvwCoord : SV_DomainLocation, const OutputPatch<InputType, 4> patch)
{
    float4 vertexPosition;
    vertexPosition = float4(1.0f,1.0f,1.0f,1.0f);
    OutputType output;
    
   
    
 
    // Determine the position of the new vertex.
	// Invert the y and Z components of uvwCoord as these coords are generated in UV space and therefore y is positive downward.
	// Alternatively you can set the output topology of the hull shader to cw instead of ccw (or vice versa).
    float3 v1 = lerp(patch[0].position, patch[1].position, uvwCoord.y);
    float3 v2 = lerp(patch[3].position, patch[2].position, uvwCoord.y);
    vertexPosition = float4(lerp(v1, v2, uvwCoord.x),1.0f);
   

    //Get texture
    float2 t1 = lerp(patch[0].tex, patch[1].tex, uvwCoord.y);
    float2 t2 = lerp(patch[3].tex, patch[2].tex, uvwCoord.y);
    float2 texturePosition = lerp(t1, t2, uvwCoord.x);

   

    //Get normals
    float3 n1 = lerp(patch[0].normal, patch[1].normal, uvwCoord.y);
    float3 n2 = lerp(patch[3].normal, patch[2].normal, uvwCoord.y);
    float3 normalPosition = lerp(n1, n2, uvwCoord.x);
    
    
    
     
    //float4 temp = heightmapTexture.SampleLevel(displacementSampler, texturePosition.xy, 0);
    //float height = temp.y;
    //vertexPosition.y = height * amplitude;
    
    WaveCalculations Wave;

    
    Wave = CalculateWaves(vertexPosition);
   
    
    vertexPosition = float4(Wave.vertexPosition,1);
    normalPosition = Wave.normal;
    
    
    //All jumowombo preparation
    output.tex = texturePosition;
    // Calculate the normal vector against the world matrix only and normalise.
    output.normal = mul(normalPosition, (float3x3) worldMatrix);
    output.normal = normalize(output.normal);
     // Calculate the position of the new vertex against the world, view, and projection matrices.
    output.position = mul(float4(vertexPosition), worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    return output;
}



WaveCalculations CalculateWaves(float4 vertexPositions)
{
    WaveCalculations returnValue;
   
    
	//Wavelenght
    //float k = waveSettings.w / waveSettings.z;
    //Frequency
    float numberOfWaves = ((3.141516 * 2) / waveSettings.z);
    //Phase speed (The speed of the wave(calculated)) (Maybe add gravity as a tweakable constant in imgui)
    //Not needed, can just set my own phaseSpeed
    //float phaseSpeed = sqrt(waveSettings.w * numberOfWaves);
    
    //Get amplitude based on the "Steepness" value and the number of waves (How pointy they are and high).
    
    //Gets the amplitude value from IMGUI and divides by the number of waves to make sure waves overlap between each other and look funny.
    //This happens when there are too many waves next to each other.
    //Preventing the amplitude being too high to overlap with the next wave (between 0 and 1)
    
    // Nvidia suggests to do to prevent waves overlaping with each other and get the maximum height possible ()
    
    //This makes sure that the smoothenes value will never be big enough to make the waves overlap with each other and look bad
    float cappedWaveSmothness = WaveSmoothness * sqrt(numberOfWaves) * waveSettings.y;
    if (cappedWaveSmothness>1.0f)
        cappedWaveSmothness = 1.0f;
    
    //Calculate amplitude to apply on the wave (without getting any overlaping) (for X and Z values, for the Y we still use inputed Amplitude)
    float amplitude = cappedWaveSmothness / (waveSettings.y * numberOfWaves * sqrt(numberOfWaves));
    
    //Get direction and normalize it (Make sure its between 0 and 1)
    float2 waveDirection = normalize(WaveDirection.xy);
    
    //Precalculated trigonometric value that will create the wave (The thing to put inside the trigonometric functions)
    float TrigValue = numberOfWaves * dot(waveDirection, vertexPositions.xz) + waveSettings.w * waveSettings.x;
    
   // float w = sqrt(7 * 2 * 3.141516 / waveSettings.z);
    //Factor of wave peaks
    //float Q = WaveSmoothness / w * waveSettings.y;
    //Directional vector of the wave.
    //This will alter in which direction the wave moves. 
    //From 1 to 0 the bigger the higher.
    
    
    
    //vertexPositions.x += Q * D.x * cos(w * dot(D.xy, vertexPositions.xy) + waveSettings.w * waveSettings.x);
    //vertexPositions.y = waveSettings.y * sin(w * dot(D.xy, vertexPositions.xy) + waveSettings.w * waveSettings.x);
   // vertexPositions.z += Q * D.y * cos(w * dot(D.xy, vertexPositions.xy) + waveSettings.w * waveSettings.x);

    //Formula from NVIDIA
    //Where x,y,t are the inputs to the functions
    //Where P are the final vertex positions
    /*      (x + (Q*A)*D.x*cos(dot(w*D, (x,y))+time*phaseSpeed)
    /*P() = (y + (Q*A)*D.y*cos(dot(w*D, (x,y))+time*phaseSpeed)
            (A)                                              
    */     
    
    //Note: Multiplying the number of waves inside of the trigonometric functions changes the frequency of the waves, however doing it outside as NVIDIA suggests does not
    //It acts as a speed multiplier instead.
    //Calculate Vertex
    vertexPositions.x += amplitude * (waveDirection.x * cos(TrigValue));
    vertexPositions.y = waveSettings.y * sin(TrigValue);
    vertexPositions.z += amplitude * (waveDirection.y * cos(TrigValue));

    //Calculate Normals
    
    //Tangent Matrix in X,Y,Z form
    float3 tangent = float3(1 - pow(waveDirection.x, 2) * waveSettings.y * sin(TrigValue),
    waveDirection.x * waveSettings.y * cos(TrigValue),
    -waveDirection.x * waveDirection.y * waveSettings.y * sin(TrigValue));
    
    //Binormal Matrix in X,Y,Z form
    float binormal = float3(-waveDirection.x * waveDirection.y * waveSettings.y * sin(TrigValue),
    waveDirection.y * waveSettings.y * cos(TrigValue),
    1 - pow(waveDirection.y, 2) * waveSettings.y * sin(TrigValue));
    
    //Help here
    float3 normal = normalize(dot(tangent, binormal));
    returnValue.normal = normal;
    returnValue.vertexPosition = vertexPositions;
   

    //Wave Settings
    // x = time; //y = amplitude(Steepness); //z =  frequency (WaveL); //w = speed (gravity);
    
    return returnValue;
}


