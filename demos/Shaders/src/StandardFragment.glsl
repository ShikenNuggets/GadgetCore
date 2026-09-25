#version 460
#pragma shader_stage(fragment)

layout (location = 0) in vec3 out_normal;
layout (location = 1) in vec2 out_texCoords;
layout (location = 2) in vec3 out_fragPos;

layout (location = 0) out vec4 FragColor;

layout (std140, set = 3, binding = 0) uniform Material {
	vec4 color;
} material;

void main()
{
	FragColor = material.color;
}
