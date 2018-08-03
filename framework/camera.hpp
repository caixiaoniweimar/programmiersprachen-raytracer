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
	Ray erzeugen_ray(float x,float y, float width, float height){
		glm::vec3 direction{ x*(1.0/width)-0.5, y*(1.0/height)-0.5, 
			    -1.0*(0.5/tan(fov_x_*M_PI/360)) };
	    Ray ray{ {0,0,0},direction };
		
		transformMatrix_ = transformMatrix();

		glm::vec4 a{ray.origin,1.0f};
		glm::vec4 b{ray.direction,0.0f};
		glm::vec3 origin1{transformMatrix_*a};
		glm::vec3 direction1{transformMatrix_*b};
		return {origin1,direction1};
		//return ray;
	}

	// Camera Modell von Theresa, benutzt beispiel2.xsd;
	/*Ray erzeugen_ray(float x, float y, float width_, float height_) const {
        glm::vec3 rayOrigin{0,0,0};
        glm::vec3 rayDirection = { (x-width_/2), (y-height_/2),
			-(width_/2)/tan(fov_x_/2) };
		return Ray{rayOrigin,rayDirection};
    } */
        
	glm::mat4 transformMatrix()
    {
  	  glm::vec3 u = glm::normalize(glm::cross(glm::normalize(dir_),up_));
  	  glm::vec3 v = glm::normalize(glm::cross(u,glm::normalize(dir_)));
  	  glm::mat4 transformatrix;
  	  transformatrix[3] = glm::vec4(eye_,1.0);
  	  transformatrix[2] = glm::vec4(glm::normalize(dir_)* -1.0f,0.0) ;
  	  transformatrix[1] = glm::vec4(v,0.0);
  	  transformatrix[0] = glm::vec4(u,0.0);
      return transformatrix;
    }

	string name_;
	float fov_x_;
	glm::vec3 eye_;  // origin
	glm::vec3 dir_;  // direction
	glm::vec3 up_; 
    glm::mat4 transformMatrix_;
	//glm::mat4 transf_inv_;
	//glm::mat4 rotate_;
	//glm::mat4 translate_;
};
#endif