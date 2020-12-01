Texture2D texture0 : register(t0);
SamplerState Sampler0 : register(s0);
Texture2D depthMapTexture : register(t1);
SamplerState shadowSampler : register(s1);

cbuffer LightBuffer : register(b0)
{
    float4 ambient[3];
    float4 diffuse[3];
    float4 position[3];
    float4 direction[3];
    float4 attenuation[3];   
};

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 worldPosition : TEXCOORD1;
    float4 lightViewPos : TEXCOORD2;
};


// Calculate lighting intensity based on direction and normal. Combine with light colour.
float4 calculateDiffuseLighting(float3 lightDirection, float3 normal, float4 ldiffuse)
{
    float intensity = 0;
    float4 colour = float4(0.0f, 0.0f, 0.0f, 0.0f);
  
    intensity = saturate(dot(normal, lightDirection));
    colour = saturate(ldiffuse * intensity);
        

    return colour;
}

float calculateAttenuation(float3 attenuation, float distance)
{
    //Attenuation Formula Calculation.
    float returnAtt = 1 / (attenuation.x + (attenuation.y * distance) +
      (attenuation.z * pow(distance, 2)));
       
    return returnAtt;

}

// Is the gemoetry in our shadow map
bool hasDepthData(float2 uv)
{
    if (uv.x < 0.f || uv.x > 1.f || uv.y < 0.f || uv.y > 1.f)
    {
        return false;
    }
    return true;
}

bool isInShadow(Texture2D sMap, float2 uv, float4 lightViewPosition, float bias)
{
    // Sample the shadow map (get depth of geometry)
    float depthValue = sMap.Sample(shadowSampler, uv).r;
	// Calculate the depth from the light.
    float lightDepthValue = lightViewPosition.z / lightViewPosition.w;
    lightDepthValue -= bias;

	// Compare the depth of the shadow map value and the depth of the light to determine whether to shadow or to light this pixel.
    if (lightDepthValue < depthValue)
    {
        return false;
    }
    return true;
}

float2 getProjectiveCoords(float4 lightViewPosition)
{
    // Calculate the projected texture coordinates.
    float2 projTex = lightViewPosition.xy / lightViewPosition.w;
    projTex *= float2(0.5, -0.5);
    projTex += float2(0.5f, 0.5f);
    return projTex;
}


float4 main(InputType input) : SV_TARGET
{
	//This will be changed to a buffer later on.
    const int numberOfLights = 3;
    float shadowMapBias = 0.001f;

    
    float distance[numberOfLights - 1];
    float3 lightVector[numberOfLights - 1];
    
	// Sample the texture. Calculate light intensity and colour, return light*texture for final pixel colour.
    float4 textureColour = texture0.Sample(Sampler0, input.tex);
   
    textureColour = float4(textureColour.xyz, 0.7f);
    //Caluclate the Light vector of all lights
    for (int z = 0; z < numberOfLights - 1; z++)
    {
        lightVector[z] = normalize((float3) position[z + 1] - input.worldPosition);
        //Calculate Distance between light and Geometry.
        distance[z] = length(lightVector[z]);
    }
    

    //Calculate final Light color with Ambient + Diffuse + Attenuation.
    //float4 lightColour = ambient + (calculateDiffuseLighting(lightVector, input.normal, diffuse) + 
    //calculateAttenuation(constantFactor,linearFactor,quadraticFactor,distance));
	
    /**Calculate ambient only with one light since later on it will be changed as just a single parameter
    independent of lightColour object, ambient should only one after all*/
    float4 lightColour = ambient[0];
    
    ////Caulculate light
    //for (int i = 0; i < numberOfLights - 1; i++)
    //{
    //    //Calcuate light
    //    lightColour += calculateDiffuseLighting(lightVector[i], input.normal, diffuse[i + 1]);
    //    lightColour += calculateAttenuation((float3) attenuation[i + 1], distance[i]);
    //}
    
    
     
         // Calculate the projected texture coordinasetes.
    float2 pTexCoord = getProjectiveCoords(input.lightViewPos);
        // Shadow test. Is or isn't in shadow
    if (hasDepthData(pTexCoord))
    {
            // Has depth map data
        if (!isInShadow(depthMapTexture, pTexCoord, input.lightViewPos, shadowMapBias))
        {
                //is NOT in shadow, therefore light
            //Remember to invert the direction for direcional light:(
            lightColour += calculateDiffuseLighting(-(float3) direction[0], input.normal, diffuse[0]);
        }
 
    }
    //lightColour += calculateDiffuseLighting(-(float3) direction[0], input.normal, diffuse[0]);
    
    
    
    
    //Combine with the texture and return
    //return float4(input.normal.xyz, 1);
    return float4(lightColour*textureColour);
}