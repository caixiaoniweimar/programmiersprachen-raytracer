#include "box.hpp"
#include <glm/vec3.hpp>

// Aufgabe 5.2
Box::Box():
	Shape(),
	minimum_{0.0f,0.0f,0.0f},
	maximum_{1.0f,1.0f,1.0f}{}
    
Box::Box(glm::vec3 const& min, glm::vec3 const& max):
	Shape(),
	minimum_{min},
	maximum_{max} {}      

// Aufgabe 5.3
Box::Box(string const& name, Color const& color, glm::vec3 const& min, glm::vec3 const& max ):
	Shape(name,color), // !!wichtig!!
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

// Aufgabe 5.5
	ostream& Box::print(ostream& os) const{
		Shape::print(os);
		os<<" Maximum: "<<"( "<< maximum_.x<<","<<maximum_.y<<","<<maximum_.z<<" )"
		<<" Minimum: "<<"( "<<minimum_.x<<","<<minimum_.y<<","<<minimum_.z<<" )";
		return os;
	}






