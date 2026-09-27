#version 460
#pragma shader_stage(fragment)

layout (location = 0) in vec3 out_normal;
layout (location = 1) in vec2 out_texCoords;
layout (location = 2) in vec3 out_fragPos;

layout (location = 0) out vec4 FragColor;

struct PointLight {
	vec3 position;
	vec4 color;
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	vec4 color;
	float constant;
	float linear;
	float quadratic;
};

struct DirectionalLight {
	vec3 direction;
	vec4 color;
};

layout (std140, set = 3, binding = 0) uniform Material {
	vec4 color;
} material;

const int gMaxLights = 8;

layout (std140, set = 3, binding = 1) uniform Lights {
	PointLight pointLights[gMaxLights];
	SpotLight spotLights[gMaxLights];
	DirectionalLight directionalLights[gMaxLights];
	int numPointLights;
	int numSpotLights;
	int numDirLights;
} lights;

layout (std140, set = 3, binding = 2) uniform CameraView {
	vec3 viewPos;
} cameraView;

vec3 GetPointLightShading(PointLight light, vec3 viewDir)
{
	float shininess = 32; // TODO - Material property
	float ambientValue = 0.1;

	vec3 lightDir = normalize(light.position - out_fragPos);
	float diffuseValue = max(dot(out_normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, out_normal);
	float specularValue = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

	float distance = length(light.position - out_fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.color.xyz * ambientValue * attenuation * material.color.xyz;
	vec3 diffuse = light.color.xyz * diffuseValue * attenuation * material.color.xyz;
	vec3 specular = light.color.xyz * specularValue * attenuation * material.color.xyz;
	return ambient + diffuse + specular;
}

vec3 GetSpotLightShading(SpotLight light, vec3 viewDir)
{
	float shininess = 32; // TODO - Material property
	float ambientValue = 0.1;

	vec3 lightDir = normalize(light.position - out_fragPos);
	float diffuseValue = max(dot(out_normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, out_normal);
	float specularValue = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

	float distance = length(light.position - out_fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 ambient = light.color.xyz * ambientValue * attenuation * intensity * material.color.xyz;
	vec3 diffuse = light.color.xyz * diffuseValue * attenuation * intensity * material.color.xyz;
	vec3 specular = light.color.xyz * specularValue * attenuation * intensity * material.color.xyz;
	return ambient + diffuse + specular;
}

vec3 GetDirLightShading(DirectionalLight light, vec3 viewDir)
{
	float shininess = 32; // TODO - Material property
	float ambientValue = 0.1;

	vec3 lightDir = normalize(-light.direction);
	float diffuseValue = max(dot(out_normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, out_normal);
	float specularValue = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

	vec3 ambient = light.color.xyz * ambientValue * material.color.xyz;
	vec3 diffuse = light.color.xyz * diffuseValue * material.color.xyz;
	vec3 specular = light.color.xyz * specularValue * material.color.xyz;
	return ambient + diffuse + specular;
}

void main()
{
	vec3 viewDir = normalize(cameraView.viewPos - out_fragPos);

	vec3 result = vec3(0.0, 0.0, 0.0);
	for(int i = 0; i < lights.numPointLights && i < gMaxLights; i++){
		result += GetPointLightShading(lights.pointLights[i], viewDir);
	}

	for(int i = 0; i < lights.numSpotLights && i < gMaxLights; i++){
		result += GetSpotLightShading(lights.spotLights[i], viewDir);
	}

	for(int i = 0; i < lights.numDirLights && i < gMaxLights; i++){
		result += GetDirLightShading(lights.directionalLights[i], viewDir);
	}

	float alpha = material.color.w;
	FragColor = vec4(result, alpha);
}
