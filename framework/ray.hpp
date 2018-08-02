#ifndef RAY_HPP
#define RAY_HPP
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>

struct Ray{
	glm::vec3 origin={0.0f,0.0f,0.0f};
	glm::vec3 direction ={0.0f,0.0f,-1.0f};
	//glm::vec3 punkt;-> getpoint(t)
	
	Ray(glm::vec3 const& origin_, glm::vec3 const& direction_):
	origin{origin_},
	direction{ glm::normalize(direction_) } {}

	glm::vec3 getpoint(float t) const{
		return origin + direction*t;
	}


};
/*Ray transformRay(glm::mat4 const& matrix, Ray const& ray){
	glm::vec4 a{ray.origin,1.0f};
	glm::vec4 b{ray.direction,0.0f};
	glm::vec3 origin(matrix*a);
	glm::vec3 direction(matrix*b);
	return {origin,direction};
}*/





#endif