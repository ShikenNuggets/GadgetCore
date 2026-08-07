#pragma once

#include <cstddef>
#include <cstdint>

namespace GCore::MemoryUDLs
{
	constexpr size_t operator""_kb(unsigned long long val) noexcept
	{
		return val * 1024ULL;
	}

	constexpr size_t operator ""_mb(unsigned long long val) noexcept
	{
		return val * 1024ULL * 1024ULL;
	}

	constexpr size_t operator ""_gb(unsigned long long val) noexcept
	{
		return val * 1024ULL * 1024ULL * 1024ULL;
	}
}
