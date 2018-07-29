#ifndef intersection_Result_HPP
#define intersection_Result_HPP
#include <glm/vec3.hpp>
// um Result (von Objekt mit Ray Intersection) zu speichern
struct intersectionResult{
	float distance;
	bool hit=false;
	glm::vec3 position={0,0,0}; 
	glm::vec3 normal={0,0,0}; 
};

#endif