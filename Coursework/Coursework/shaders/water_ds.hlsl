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

    //Wave Settings (on brakets are the upgraded values)
    // x = peakeness; //y = amplitude; //z =  frequency (WaveLenght); //w = PhaseSpeed of the wave;
    float4 waveSettings[3];
    float4 WaveDirectionTimePadding[3];
  
    
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
    float4 worldPosition : TEXCOORD1;

};

struct WaveCalculations
{
    float3 vertexPosition;
    float3 normal;
};

WaveCalculations CalculateWaves(float4 vertexPositions, float4 waveSettings, float WaveDirection, float time);


[domain("quad")]
OutputType main(ConstantOutputType input, float2 uvwCoord : SV_DomainLocation, const OutputPatch<InputType, 4> patch)
{
    float WaveDirection[3];
    for (int i = 0; i < 3;i++)
    WaveDirection[i] = WaveDirectionTimePadding[i].x;
    
    float time = WaveDirectionTimePadding[0].y;
    
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
    
    
    //Calculate waves
    WaveCalculations Wave;
    //Get Base Wave
    float4 baseVertexPosition = vertexPosition;

    Wave = CalculateWaves(baseVertexPosition, waveSettings[0], WaveDirection[0], time);
   
    vertexPosition = float4(Wave.vertexPosition, 1);
    normalPosition = Wave.normal;
    normalPosition.y = 1- Wave.normal.y;
    
    for (int i = 1; i<3; i++)
    {
       Wave = CalculateWaves(baseVertexPosition, waveSettings[i], WaveDirection[i], time);
   
       vertexPosition += float4(Wave.vertexPosition, 1);
       
        
       normalPosition.x += Wave.normal.x;
        normalPosition.y += 1 - Wave.normal.y; //Invert normal. 
       normalPosition.z += Wave.normal.z;
    }
    
    normalPosition = normalize(normalPosition);
    //normalPosition = float3(0.0f, -1.0f, 0.0f);
    //All jumowombo preparation
    output.tex = texturePosition;
    // Calculate the normal vector against the world matrix only and normalise.
    output.normal = mul(normalPosition, (float3x3) worldMatrix);
    output.normal = normalize(output.normal);
     // Calculate the position of the new vertex against the world, view, and projection matrices.
    output.position = mul(float4(vertexPosition), worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    output.worldPosition = mul(vertexPosition, worldMatrix);
    
    return output;
}



WaveCalculations CalculateWaves(float4 vertexPositions, float4 waveSettings, float INWaveDirection, float time)
{
    WaveCalculations returnValue;
   
    //Calculate vector from angle (Im gui converts degrees to rad)
    float2 WaveDirection = float2(cos(INWaveDirection), sin(INWaveDirection));
   
    //Phase speed (The speed of the wave(calculated)) (Maybe add gravity as a tweakable constant in imgui)
    //Not needed, can just set my own phaseSpeed
    //float phaseSpeed = sqrt(waveSettings.w * numberOfWaves);
    
  
    //Angular Wavenumber ()
    //The angular wavenumber tells you the number of wavelengths per unit distance https://sciencing.com/calculate-wavenumber-5152608.html
    float numberOfWaves = ((3.141516 * 2) / waveSettings.z);
    
    // Nvidia suggests to do to prevent waves overlaping with each other and get the maximum height possible ()
    
    //Formula from NVIDIA https://developer.nvidia.com/gpugems/gpugems/part-i-natural-effects/chapter-1-effective-water-simulation-physical-models
    //Where x,y,t are the inputs to the functions
    //Where P are the final vertex positions, D = direction, w = sqrt(wavenumber)
    
    /*      (x + (Q*A)*D.x*cos(dot(w*D, (x,y))+time*phaseSpeed)
    /*P() = (y + (Q*A)*D.y*cos(dot(w*D, (x,y))+time*phaseSpeed)
            (Asin(dor(w*D,(x,y))+time*phaseSpeed))                                              
    */     
    
    /*Here Qi is a parameter that controls the steepness of the waves. For a single wave i, Qi of 0 gives the usual rolling sine wave
    and Qi = 1/(wi*Ai ) gives a sharp crest. Larger values of Qi should be avoided, because they will cause loops to form above the
    wave crests. In fact, we can leave the specification of Q as a "steepness" parameter for the production artist, allowing a
    range of 0 to 1, and using Qi = Q/(wi Ai x numWaves) to vary from totally smooth waves to the sharpest waves we can produce.*/
    
    //This makes sure that the smoothenes value will never be big enough to make the waves overlap with each other and look bad
    float clampedWavePeak = waveSettings.x * numberOfWaves * waveSettings.y;
    
    //if (clampedWavePeak > 1.0f)
        //clampedWavePeak = 1.0f;
    
    //Calculate amplitude to apply on the wave (without getting any overlaping) (for X and Z values, for the Y we still use inputed Amplitude)
    //float amplitude = clampedWavePeak / (waveSettings.y * numberOfWaves * numberOfWaves);
    
    float amplitude = clampedWavePeak * waveSettings.y;
    
    //Get direction and normalize it
    float2 waveDirection = normalize(WaveDirection.xy);
    
    //Precalculated trigonometric value that will create the wave (The thing to put inside the trigonometric functions)
    float TrigValue = numberOfWaves * dot(waveDirection, vertexPositions.xz) + waveSettings.w * time;

    
    //Note: Multiplying the number of waves inside of the trigonometric functions changes the frequency of the waves
    //It acts as a speed multiplier instead.
    //Calculate Vertex
    vertexPositions.x += amplitude * (waveDirection.x * cos(TrigValue));
    vertexPositions.y = waveSettings.y * sin(TrigValue);
    vertexPositions.z += amplitude * (waveDirection.y * cos(TrigValue));

    //Calculate Normals  
    float3 normal = float3(-waveDirection.x * waveSettings.y * cos(TrigValue),
    clampedWavePeak*(waveSettings.y) * sin(TrigValue),
    waveDirection.y * waveSettings.y * cos(TrigValue));
    
    
    returnValue.normal = normalize(normal);
    returnValue.vertexPosition = vertexPositions;
   

    //Wave Settings (on brakets are the upgraded values)
    // x = peakness; //y = amplitude; //z =  frequency (WaveLenght); //w = PhaseSpeed of the wave;
    
    return returnValue;
}


