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
		constexpr RawShader(std::vector<uint8_t> shaderBytes, ShaderType type, ShaderFormat format) : shaderBytes(std::move(shaderBytes)), type(type), format(format){}
		constexpr RawShader(std::span<uint8_t> shaderBytes, ShaderType type, ShaderFormat format) : shaderBytes(shaderBytes.begin(), shaderBytes.end()), type(type), format(format){}

		constexpr const std::vector<uint8_t>& GetShaderBytes() const{ return shaderBytes; }
		constexpr ShaderType GetShaderType() const{ return type; }
		constexpr ShaderFormat GetShaderFormat() const{ return format; }

	private:
		std::vector<uint8_t> shaderBytes;
		ShaderType type;
		ShaderFormat format;
	};
}
