#define POINT_LIGHT 0
#define DIRECTIONAL_LIGHT 1

struct Light
{
  int    type;
  float  dropOff;
  float  pow;
  float  radius;
  float  intensity;
  float3 pad;
  float4 positionOrDirection;
  float4 color;
};

float4 LightCalculation(in Light     light,
                        in float4    cameraPos,
                        in float4    pixelWorldPos,
                        in float4    pixelAlbedo,
                        in float4    pixelWorldNormal,
                        in float     pixelMetallic, // How shiny the pixel is
                        in float     roughness, // Higher value means more rough
                        inout float4 specularHighlight)
{
  float4 worldToCamDir = normalize(cameraPos - pixelWorldPos);
  float4 finalColor    = float4(0, 0, 0, 0);
  float4 halfWayDir    = float4(0, 0, 0, 0);

  if (light.type == POINT_LIGHT)
  {
    float4 positionToLight = light.positionOrDirection - pixelWorldPos;
    float  distanceToLight = length(positionToLight);
    if (distanceToLight <= light.radius)
    {
      float attenuation =
          light.intensity / (1.0f + light.dropOff * pow(distanceToLight, light.pow));
      halfWayDir = normalize(normalize(positionToLight) + worldToCamDir);
      //halfWayDir = normalize(positionToLight + worldToCamDir);
      specularHighlight += pow(max(dot(pixelWorldNormal, halfWayDir), 0.0f), roughness) *
                           pixelMetallic.r * attenuation * light.color;
      finalColor = max(dot(pixelWorldNormal, normalize(positionToLight)), 0.0f) * light.color *
                   pixelAlbedo * attenuation;
    }
  }
  else if (light.type == DIRECTIONAL_LIGHT)
  {
    halfWayDir = normalize(normalize(-light.positionOrDirection) + worldToCamDir);
    specularHighlight += pow(max(dot(pixelWorldNormal, halfWayDir), 0.0f), roughness) *
                         pixelMetallic.r * light.intensity * light.color;
    finalColor = max(dot(pixelWorldNormal, normalize(-light.positionOrDirection)), 0.0f) *
                 light.color * pixelAlbedo * light.intensity;
  }

  return finalColor;
}