#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/vec3.hpp>
#define <string>
#include "ray.hpp"
class Camera{
	
public:
	Camera();
	Camera(string const& name, float fov_x);
	//Camera(string const& name, float fov_x, glm::vec3 eye, glm::vec3 dir, glm::vec3 up);
	~Camera();
	//float rechnen_fov_bereich(float fov);
	//Ray erzeugen_ray(float x,float y);



	string name_;
	float fov_x_;
	//glm::vec3 eye_;
	//glm::vec3 dir_;
	//glm::vec3 up_;

};

#endif