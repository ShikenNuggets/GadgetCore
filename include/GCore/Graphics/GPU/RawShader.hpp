#pragma once

#include <cstdint>
#include <span>
#include <vector>

namespace Gadget
{
	enum class ShaderType : uint8_t
	{
		Vertex,
		Fragment,
	};

	enum class ShaderFormat : uint8_t
	{
		SPIRV,
		DXIL,
		MSL
	};

	class RawShader
	{
	public:
		constexpr RawShader(std::vector<uint8_t> shaderBytes, ShaderType type, ShaderFormat format, uint32_t numUniforms) : shaderBytes(std::move(shaderBytes)), type(type), format(format), numUniforms(numUniforms){}
		constexpr RawShader(std::span<uint8_t> shaderBytes, ShaderType type, ShaderFormat format, uint32_t numUniforms) : shaderBytes(shaderBytes.begin(), shaderBytes.end()), type(type), format(format), numUniforms(numUniforms){}

		constexpr const std::vector<uint8_t>& GetShaderBytes() const{ return shaderBytes; }
		constexpr ShaderType GetShaderType() const{ return type; }
		constexpr ShaderFormat GetShaderFormat() const{ return format; }
		constexpr uint32_t GetNumUniforms() const{ return numUniforms; }

	private:
		std::vector<uint8_t> shaderBytes;
		ShaderType type;
		ShaderFormat format;
		uint32_t numUniforms;
	};
}
