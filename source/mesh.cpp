#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "mesh.hpp"

// Attribute deduplication, currently by vertices
Mesh Mesh::deduplicate() const
{
	std::unordered_map <glm::vec3, int32_t> existing;

	Mesh fixed;

	auto add_uniquely = [&](int32_t i) -> int32_t {
		glm::vec3 v = positions[i];
		if (existing.find(v) == existing.end()) {
			int32_t csize = fixed.positions.size();

			fixed.positions.push_back(v);
			fixed.normals.push_back(normals[i]);
			fixed.uvs.push_back(uvs[i]);

			existing[v] = csize;
			return csize;
		}

		return existing[v];
	};

	for (const glm::ivec3 &t : triangles) {
		fixed.triangles.push_back(glm::ivec3 {
			add_uniquely(t.x),
			add_uniquely(t.y),
			add_uniquely(t.z)
		});
	}

	return fixed;
}

// Mesh functions
std::vector <float> interleave_attributes(const Mesh &m)
{
	// TODO: size check beforehand
	std::vector <float> attributes;
	for (size_t i = 0; i < m.positions.size(); i++) {
		attributes.push_back(m.positions[i].x);
		attributes.push_back(m.positions[i].y);
		attributes.push_back(m.positions[i].z);

		attributes.push_back(m.normals[i].x);
		attributes.push_back(m.normals[i].y);
		attributes.push_back(m.normals[i].z);
		
		attributes.push_back(m.uvs[i].x);
		attributes.push_back(m.uvs[i].y);
	}

	return attributes;
}