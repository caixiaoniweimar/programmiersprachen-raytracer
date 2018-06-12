#include "box.hpp"
#include <glm/vec3.hpp>

// Aufgabe 5.2
Box::Box():
	minimum_{0.0f,0.0f,0.0f},
	maximum_{1.0f,1.0f,1.1f}{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
	minimum_{min},
	maximum_{max} {}

Box::~Box() {}
	
	double Box::area() const{
		double length= maximum_.x - minimum_.x;
		double height= maximum_.y - minimum_.y;
		double width= maximum_.z - minimum_.z;
		return 2*length*height+2*length*width+2*height*width;
	}

	double Box::volume() const{
		double length= maximum_.x - minimum_.x;
		double height= maximum_.y - minimum_.y;
		double width= maximum_.z - minimum_.z;
		return length*height*width;
	}

	glm::vec3 Box::get_min() const{
		return minimum_;
	}

	glm::vec3 Box::get_max() const{
		return maximum_;
	}