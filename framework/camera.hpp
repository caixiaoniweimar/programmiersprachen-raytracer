#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "ray.hpp"
#include <math.h>
#define _USE_MATH_DEFINES
using namespace std;

class Camera{
public:
	Camera():
		name_{"default name duer Camera"},
		fov_x_{45}, // 45?
		eye_{0,0,0}, // origin / 0,10,10
		dir_{0,0,-1},
		up_{0,1,0} {}
	Camera(string const& name, float fov_x, glm::vec3 eye, glm::vec3 dir, glm::vec3 up ):
		name_{name},
		fov_x_{fov_x}, 
		eye_{eye},
		dir_{dir},
		up_{up} {}

	// nicht so gut Algorithmus fuer CameraModell, erste Mal Probe
	/*Ray erzeugen_ray(float x, float y) const{
		glm::vec3 right=glm::cross(dir_,up_); //垂直矢量
		glm::vec3 up=glm::cross(right,dir_); 
		float fovBereich=tan(fov_x_*(M_PI*0.5f/180))*2;
		glm::vec3 r=right*( (x-0.5f)*fovBereich );
		glm::vec3 u=up*( (y-0.5f)*fovBereich );
		glm::vec3 tmp=dir_+r+u;
		return Ray{eye_,glm::normalize(tmp)};
	}*/

	Ray erzeugen_ray(float x,float y, float height, float width) const{
		glm::vec3 direction{ x*(1.0/width)-0.5, y*(1.0/height)-0.5, 
			    -1.0*(0.5/tan(fov_x_*M_PI/360)) };
	    return Ray{eye_,direction};
	}
public:
	string name_;
	float fov_x_;
	glm::vec3 eye_;
	glm::vec3 dir_;  // front
	glm::vec3 up_; 
};
#endif