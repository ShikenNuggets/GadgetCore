#include <iostream>

#include <catch2/catch_all.hpp>

#include <GCore/Data/RingBuffer.hpp>

using namespace Gadget;

TEST_CASE("RingBuffer::RingBuffer", "[ring_buffer_constructor]")
{
	const RingBuffer<int, 5> ringBuffer;
	REQUIRE(ringBuffer.IsEmpty());
	REQUIRE(!ringBuffer.IsFull());
}

TEST_CASE("RingBuffer::Add", "[ring_buffer_add]")
{
	RingBuffer<int, 2> ringBuffer;
	REQUIRE(ringBuffer.IsEmpty());
	REQUIRE(!ringBuffer.IsFull());

	ringBuffer.Add(0);
	REQUIRE(!ringBuffer.IsEmpty());
	REQUIRE(!ringBuffer.IsFull());
	REQUIRE(ringBuffer.GetOldest() == 0);
	REQUIRE(ringBuffer.GetNewest() == 0);

	ringBuffer.Add(1);
	REQUIRE(!ringBuffer.IsEmpty());
	REQUIRE(ringBuffer.IsFull());
	REQUIRE(ringBuffer.GetOldest() == 0);
	REQUIRE(ringBuffer.GetNewest() == 1);

	ringBuffer.Add(2);
	REQUIRE(!ringBuffer.IsEmpty());
	REQUIRE(ringBuffer.IsFull());
	REQUIRE(ringBuffer.GetOldest() == 1);
	REQUIRE(ringBuffer.GetNewest() == 2);
}

TEST_CASE("RingBuffer::Iteration", "[ring_buffer_iteration]")
{
	RingBuffer<int, 3> ringBuffer;

	ringBuffer.Add(1);
	ringBuffer.Add(2);
	ringBuffer.Add(3);
	ringBuffer.Add(4);

	int total = 0;
	for (const auto& i : ringBuffer)
	{
		total += i;
	}

	REQUIRE(total == 9);
}
