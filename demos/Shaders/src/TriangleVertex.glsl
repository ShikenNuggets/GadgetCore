#version 460
#pragma shader_stage(vertex)

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;

layout (location = 0) out vec4 v_color;

layout (std140, set = 1, binding = 0) uniform CameraBuffer {
	mat4 projectionMatrix;
	mat4 viewMatrix;
} camera;

void main()
{
	gl_Position = (camera.projectionMatrix * camera.viewMatrix) * vec4(a_position, 1.0f);
	v_color = a_color;
}
