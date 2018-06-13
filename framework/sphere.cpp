#include "sphere.hpp"
#include <glm/vec3.hpp>
      
// Aufgabe 5.2
	Sphere::Sphere():  
		mittelpunkt_{0.0f,0.0f,0.0f},
		radius_{1.0} {}

	Sphere::Sphere(Sphere const& s):// copy Konstruktor
		mittelpunkt_{s.mittelpunkt_},
		radius_{s.radius_} {}
         
	Sphere::Sphere(glm::vec3 const& mittelpunkt, double radius):
		mittelpunkt_{mittelpunkt},
		radius_{radius} {}

	Sphere::~Sphere(){}  

	double Sphere::area() const {
		return 4*M_PI*radius_*radius_;
	}

	double Sphere::volume() const {
		return (4/3) * M_PI * radius_ * radius_ * radius_;
	}

	glm::vec3 Sphere::get_mittelpunkt() const{
		return mittelpunkt_;
	}

	double Sphere::get_radius() const {
		return radius_;
	}

// Aufgabe 5.5
	ostream& Sphere::print(ostream& os) const {
		Shape::print(os);
		os<<"Mittelpunkt: "<<"( "<<mittelpunkt_.x<<","<<mittelpunkt_.y<<","<<mittelpunkt_.z
		  <<" )"<<"Radius: "<<radius_;
		return os;
	}
	