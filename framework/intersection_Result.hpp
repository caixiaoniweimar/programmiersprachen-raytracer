#ifndef intersection_Result_HPP
#define intersection_Result_HPP
#include <glm/vec3.hpp>
// um Result (von Objekt mit Ray Intersection) zu speichern
struct intersectionResult{
	float distance;
	bool hit;
	glm::vec3 position; 
	glm::vec3 normal;
	//shared_ptr<Shape> closest_shape;

	intersectionResult():
		distance{0.0},
		hit{false},
		position{0,0,0},
		normal{0,0,0} {}
	intersectionResult( intersectionResult const& result):
	    distance{result.distance},
	    hit{result.hit},
	    position{result.position},
	    normal{result.normal} {}
};

#endif