#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "ray.hpp"
#include <cmath>
#include <string>
#define _USE_MATH_DEFINES
using namespace std;

struct Camera{
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
	Ray erzeugen_ray(float x,float y, float width, float height){
		
		glm::vec3 direction{ x*(1.0/width)-0.5, y*(1.0/height)-0.5, 
			    -1.0*(0.5/tan(fov_x_*M_PI/360)) };
	    Ray ray{ {0,0,0},direction };
		
		camera_matrix = transformation_matrix();

		glm::vec4 a{ray.origin,1.0f}; //transformRay Methode
		glm::vec4 b{ray.direction,0.0f};
		glm::vec3 origin1{camera_matrix*a};
		glm::vec3 direction1{camera_matrix*b};
		return {origin1,direction1};
	}
        
	glm::mat4 transformation_matrix() // Laut Folien
    {
  	  glm::vec3 u = glm::normalize(glm::cross(glm::normalize(dir_),up_)); // u=n*up
  	  glm::vec3 v = glm::normalize(glm::cross(u,glm::normalize(dir_))); // v=u*n
  	  glm::mat4 transformatrix;
	  transformatrix[0] = glm::vec4(u,0.0); // U_x,U_y,U_z,0
	  transformatrix[1] = glm::vec4(v,0.0); // V_x,V_y,V_z,0
	  transformatrix[2] = glm::vec4(glm::normalize(dir_)* -1.0f,0.0) ; // -N_x,-N_y,-N_z,0
  	  transformatrix[3] = glm::vec4(eye_,1.0); 
      return transformatrix;
    }

	string name_;
	float fov_x_;
	glm::vec3 eye_;  // origin
	glm::vec3 dir_;  // direction, 0,0,-1
	glm::vec3 up_; 
    glm::mat4 camera_matrix;
    glm::mat4 world_transformation_inv_;
};
#endif