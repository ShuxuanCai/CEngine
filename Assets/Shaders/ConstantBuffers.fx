// Description: Constant Buffers for CEngine.

cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix wvp;
	float3 viewPosition;
	float bumpHeight;
}

cbuffer BoneTransformBuffer : register(b1)
{
	matrix boneTransforms[256];
}

cbuffer LightBuffer : register(b2)
{
	float3 lightDirection;
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
}

cbuffer MaterialBuffer : register(b3)
{
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
	float4 materialEmissive;
	float4 materialPower;
}

cbuffer SettingBuffer : register(b4)
{
	bool useDiffuseMap;
	bool useSpecularMap;
	bool useBumpMap;
	bool useNormalMap;
	bool useShadowMap;
	bool useSkinning;
	float depthBias;
}