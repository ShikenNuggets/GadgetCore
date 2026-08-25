#pragma once

#include <string_view>

#include "GpuDevice.hpp"

namespace Gadget
{
	class GpuPipeline
	{
	public:
		GpuPipeline(GpuDevice& owner, const RawShader& vertex, const RawShader& fragment);
		GpuPipeline(GpuDevice& owner, std::string_view vertexFilePath, std::string_view fragmentFilePath, uint32_t numVertexUniforms, uint32_t numFragmentUniforms);
		~GpuPipeline();

		SDL_GPUGraphicsPipeline* GetPipeline(){ return pipelinePtr; }

	private:
		GpuDevice& ownerDevice;
		SDL_GPUGraphicsPipeline* pipelinePtr;
	};
}
