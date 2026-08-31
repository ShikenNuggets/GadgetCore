#version 460
#pragma shader_stage(fragment)

layout (location = 0) in vec4 aPos;

layout (location = 0) out vec4 FragColor;

void main()
{
	FragColor = aPos;
}
