#pragma once

#include <vector>

namespace Gadget
{
	template <typename T, int64_t Size>
	class RingBuffer
	{
	public:
		static_assert(Size > 0, "RingBuffer size must be > 0");

		RingBuffer()
		{
			data.reserve(Size);
		}

		void Add(T value)
		{
			if (!IsFull())
			{
				data.push_back(value);
				oldestIdx = 0;
				return;
			}

			data[oldestIdx] = value;
			oldestIdx++;
			if (oldestIdx >= data.size() || oldestIdx < 0)
			{
				oldestIdx = 0;
			}
		}

		[[nodiscard]] const T& GetOldest() const
		{
			if (IsEmpty())
			{
				throw -1; // TODO - Proper exception type for this
			}

			return data[oldestIdx];
		}

		[[nodiscard]] const T& GetNewest() const
		{
			if (IsEmpty())
			{
				throw - 1; // TODO - Proper exception type for this
			}

			auto newestIdx = oldestIdx - 1;
			if (newestIdx < 0)
			{
				newestIdx = data.size() - 1;
			}

			return data[newestIdx];
		}

		[[nodiscard]] bool IsFull() const{ return data.size() >= Size; }
		[[nodiscard]] bool IsEmpty() const{ return data.empty(); }

		[[nodiscard]] std::vector<T>::iterator begin(){ return data.begin(); }
		[[nodiscard]] std::vector<T>::const_iterator begin() const{ return data.begin(); }
		[[nodiscard]] std::vector<T>::iterator end(){ return data.end(); }
		[[nodiscard]] std::vector<T>::const_iterator end() const{ return data.end(); }

	private:
		std::vector<T> data;
		int64_t oldestIdx = 0;
	};
}
