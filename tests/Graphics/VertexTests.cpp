#include <catch2/catch_all.hpp>

#include <GCore/Graphics/Vertex.hpp>

using namespace Gadget;

TEST_CASE("Vertex::Vertex", "[vertex_constructor]")
{
	const auto vertex = Vertex();
	REQUIRE(vertex.position.x == 0.0);
	REQUIRE(vertex.position.y == 0.0);
	REQUIRE(vertex.position.z == 0.0);
	REQUIRE(vertex.position.w == 1.0);

	REQUIRE(vertex.color.r == 0.0f);
	REQUIRE(vertex.color.g == 0.0f);
	REQUIRE(vertex.color.b == 0.0f);
	REQUIRE(vertex.color.a == 1.0f);

	const auto vertex2 = Vertex(Gadget::Vector4(1.0, 2.0, 3.0, 4.0), Gadget::Color(0.4f, 0.5f, 0.6f, 0.7f));
	REQUIRE(vertex2.position.x == 1.0);
	REQUIRE(vertex2.position.y == 2.0);
	REQUIRE(vertex2.position.z == 3.0);
	REQUIRE(vertex2.position.w == 4.0);

	REQUIRE(vertex2.color.r == 0.4f);
	REQUIRE(vertex2.color.g == 0.5f);
	REQUIRE(vertex2.color.b == 0.6f);
	REQUIRE(vertex2.color.a == 0.7f);
}
