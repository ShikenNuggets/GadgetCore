#include <catch2/catch_all.hpp>

#include <GCore/Graphics/Vertex.hpp>

using namespace Gadget;

TEST_CASE("Vertex::Vertex", "[vertex_constructor]")
{
	const auto vertex = Vertex();
	REQUIRE(vertex.position.x == 0.0);
	REQUIRE(vertex.position.y == 0.0);
	REQUIRE(vertex.position.z == 0.0);

	REQUIRE(vertex.normal.x == 0.0);
	REQUIRE(vertex.normal.y == 0.0);
	REQUIRE(vertex.normal.z == 1.0);

	REQUIRE(vertex.texCoords.x == 0.0);
	REQUIRE(vertex.texCoords.y == 0.0);

	const auto vertex2 = Vertex(Gadget::Vector3(1.0, 2.0, 3.0), Gadget::Vector3(0.4f, 0.5f, 0.6f), Gadget::Vector2(0.1f, 0.2f));
	REQUIRE(vertex2.position.x == 1.0);
	REQUIRE(vertex2.position.y == 2.0);
	REQUIRE(vertex2.position.z == 3.0);

	REQUIRE(vertex2.normal.x == 0.4f);
	REQUIRE(vertex2.normal.y == 0.5f);
	REQUIRE(vertex2.normal.z == 0.6f);

	REQUIRE(vertex2.texCoords.x == 0.1f);
	REQUIRE(vertex2.texCoords.y == 0.2f);
}
