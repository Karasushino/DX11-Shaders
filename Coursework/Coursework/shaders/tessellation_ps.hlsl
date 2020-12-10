Texture2D heightmapTexture : register(t1);
SamplerState Sampler0 : register(s0);
SamplerState shadowSampler : register(s1);

#define numberOfPointlights 2
Texture2D directionalDepthMap : register(t2);
Texture2D pointlightDepthMap[numberOfPointlights * 6] : register(t3);


cbuffer WaterBuffer : register(b1)
{
    float heightmapAmplitude;
    float waterPlaneHeight;
    float offset;
    float depthScalar;
};

cbuffer WaterColorBuffer : register(b2)
{
    float4 deepColor;
    float4 shallowColor;
}

cbuffer DirectionLightBuffer : register(b3)
{
    float4 ambient;
    float4 dirDiffuse;
    float4 direction;
    //Specular settings
    float4 specularColour;
    float specularPower;
    float3 padding;
};

cbuffer PointlightBufferType : register(b4)
{
    float4 diffuse[numberOfPointlights];
    float4 position[numberOfPointlights];
    float4 attenuation[numberOfPointlights];
};

cbuffer LightMatrixBufferType : register(b5)
{
		//Directional light matrix
    matrix dirLightView;
    matrix dirLightProjection;
		//Pointlight matrix
    matrix pointlightProjection[numberOfPointlights];
    matrix pointlightView[numberOfPointlights * 6];
};

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float4 worldPosition : TEXCOORD1;
};

float4 calcSpecular(float3 lightDirection, float3 normal, float3 viewVector, float4 specularColour, float specularPower)
{
// blinn-phong specular calculation 
    //Turn alpha to 0
    specularColour = float4(specularColour.x, specularColour.y, specularColour.z, 0.f);
    float intensity = saturate(dot(lightDirection, normal));
    
    float3 reflection = normalize(intensity * normal + lightDirection);
    float3 halfway = normalize(lightDirection + viewVector);
    
    float4 specularIntensity = pow(max(dot(halfway, normal), 0.0), specularPower);
       
    //    // Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
    //float4 specularIntensity = pow(saturate(dot(reflection, viewVector)), 600);
    
    return saturate(specularColour * specularIntensity);
}

float4 calculateViewMatrix(matrix projection, matrix view, InputType input)
{
    float4 calculatedMatrix = input.worldPosition;
    // Calculate the position of the vertice as viewed by the light source.
    calculatedMatrix = mul(calculatedMatrix, view);
    calculatedMatrix = mul(calculatedMatrix, projection);
    //Return the matrix as view from the light source
    return calculatedMatrix;
}

// Calculate lighting intensity based on direction and normal. Combine with light colour.
float4 calculateDiffuseLighting(float3 lightDirection, float3 normal, float4 ldiffuse)
{
    float intensity = 0;
    float4 colour = float4(0.0f, 0.0f, 0.0f, 0.0f);
    
    //Trying not to add alpha to existing alpha
    ldiffuse = float4(ldiffuse.xyz, 0);
    
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

//Returns the corresponding pixel color, with shadows (not working)
float4 getPointlightContribution(float shadowMapBias, InputType input)
{
    int index = 0;
    float4 lightColour = 0.f;
     // Calculate the projected texture coordinasetes.
    //"i" correspond for index of pointlight
    for (int i = 0; i < numberOfPointlights; i++)
    {
        //Get light vector
        float3 lightVector = (float3) position[i] - input.worldPosition.xyz;
        
        //Distance for attenuation calculation = lenght of light vector
        float distance = length(lightVector);
        
        //Make sure to normalize the light vector.
        lightVector = normalize(lightVector);
        
        //Calculate the attenuation scalar value for the diffuse 
        float att = calculateAttenuation((float3) attenuation[i], distance);
        
        
       
        //"z" corresponds to the pointlight depth map
        //Check only forward
        for (int z = 0; z < 6; z++)
        {
            //Calculate the view position from the pointlight perspective
            float4 viewPosition = calculateViewMatrix(pointlightProjection[i], pointlightView[index], input);
            
            //Get projective Coords of pointlight view
            float2 pTexCoord = getProjectiveCoords(viewPosition);
            
             // Shadow test. Is or isn't in shadow
             //Test Lights
            if (hasDepthData(pTexCoord))
            {
            // Has depth map data
                if (!isInShadow(pointlightDepthMap[index], pTexCoord, viewPosition, shadowMapBias))
                {
                    //is NOT in shadow, therefore light
                
                   
                
                    lightColour += calculateDiffuseLighting(lightVector, input.normal, diffuse[i] * att);
                    //No attenuation yet, need to pass it to buffer I forgot : (
                   // lightColour = float4(1, 0, 0, 0);

                }
                
            }
            index++;
          
        }
       
    }
    return lightColour;
}

float4 getDirectionalLightContribution(float shadowMapBias, InputType input)
{
    float4 color = 0.f;
    float4 viewMatrix = calculateViewMatrix(dirLightProjection, dirLightView, input);
     // Calculate the projected texture coordinates.
    float2 pTexCoord = getProjectiveCoords(viewMatrix);
    //return float4(pTexCoord.xy, 0, 1);
        // Shadow test. Is or isn't in shadow
    if (hasDepthData(pTexCoord))
    {
            // Has depth map data
        if (!isInShadow(directionalDepthMap, pTexCoord, viewMatrix, shadowMapBias))
        {
                //is NOT in shadow, therefore light
            color += calculateDiffuseLighting(-direction.xyz, input.normal, dirDiffuse);
           

        }
    }
    
    return color;
}

float4 main(InputType input) : SV_TARGET
{
    float shadowMapBias = 0.01f;
    
    float4 temp = heightmapTexture.SampleLevel(Sampler0, input.tex.xy, 0);
    float height = temp.y * heightmapAmplitude;
    
    float waterheightCPU = waterPlaneHeight;
    //Treshold for depthness
    //float offset = 4.3f;
    
    float offsetLevel = waterheightCPU + offset;
    
    float waterLevel = input.worldPosition.y - height - offsetLevel;
    
    //float4 deepColor = float4(0.13f, 0.13f, 0.8f, 0.6f);
    //float4 shallowColor = float4(0.1f, 0.9f, 0.9f, 0.2f);
    float4 lightColor = float4(1, 1, 1, 1);
    
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
    float4 waterColor = saturate(lerp(shallowColor, deepColor, waterLevel / depthScalar));
    
    
    //Use directional W value of the buffer to toggle on if lighting will have an effect on the water or not.
    if (direction.w == 1)
    {
        lightColor = float4(ambient.xyz, 1);
    
        lightColor += getDirectionalLightContribution(shadowMapBias, input);
        lightColor += getPointlightContribution(shadowMapBias, input);
        //Get view matrix
        float4 viewMatrix = calculateViewMatrix(dirLightProjection, dirLightView, input);
        float3 lightDirection = normalize(-direction - input.worldPosition);
        lightColor += calcSpecular(lightDirection, input.normal, viewMatrix.xyz, specularColour, specularPower);

    }
        
    
    //Multiply light color by the Water Color to return lit water
    return (lightColor * waterColor);
}