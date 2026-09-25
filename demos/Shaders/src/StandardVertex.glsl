#version 460
#pragma shader_stage(vertex)

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texCoords;

layout (location = 0) out vec3 out_normal;
layout (location = 1) out vec2 out_texCoords;
layout (location = 2) out vec3 out_fragPos;

layout (std140, set = 1, binding = 0) uniform CameraBuffer {
	mat4 projectionMatrix;
	mat4 viewMatrix;
} camera;

layout (std140, set = 1, binding = 1) uniform ModelBuffer {
	mat4 modelMatrix;
	mat3 normalMatrix;
} model;

void main()
{
	out_normal = normalize(model.normalMatrix * in_normal);
	out_texCoords = in_texCoords;
	out_fragPos = vec3(model.modelMatrix * vec4(in_position, 1.0f));

	gl_Position = (camera.projectionMatrix * camera.viewMatrix) * vec4(in_position, 1.0f);
}
