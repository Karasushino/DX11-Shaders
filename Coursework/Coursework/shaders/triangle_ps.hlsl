//#pragma exclude_renderers d3d11_9x
Texture2D texture0 : register(t0);
SamplerState Sampler0 : register(s0);
Texture2D directionalDepthMap : register(t1);
SamplerState shadowSampler : register(s1);



cbuffer DirectionLightBuffer : register(b0)
{
    float4 ambient;
    float4 dirDiffuse;
    float4 direction;
};

cbuffer LightMatrixBufferType : register(b1)
{
    //Directional light matrix
    matrix dirLightView;
    matrix dirLightProjection;

};

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 worldPosition : TEXCOORD1;
    
};

float4 calculateViewMatrix(matrix projection, matrix view, InputType input)
{
    float4 calculatedMatrix = float4(input.worldPosition,1);
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
    //This will be changed to a buffer later on.
    float shadowMapBias = 0.01f;
    
    float3 bottomColor = float3(0.0f, .3f, 0.f);
    float3 topColor = float3(0.0f, 1.0f, 0.f);

    //Ambient color
    float3 lightColor = ambient;
    
    //generate the color of the grass blade base on height
    float3 grassTexture = lerp(topColor, bottomColor, input.tex.y+0.2f);
    //Add the lighting
    lightColor += getDirectionalLightContribution(shadowMapBias, input);

    //return float4(input.normal.xyz, 1);
    return float4(lightColor.xyz * grassTexture.xyz, 1.0);
}