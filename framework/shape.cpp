#include "shape.hpp"

Shape::Shape():
	name_{"default name"},
	color_{0.0f,0.0f,0.0f} {}

Shape::Shape(string name, Color const& color):
	name_{name},
	color_{color} {}
  
Shape::Shape(Shape const& shape):
	name_{shape.name_},
	color_{shape.color_} {}

Shape::~Shape() {}

// Aufgabe 5.4
ostream& Shape::print(ostream& os) const{ 
			os << "Name: " << name_ <<" Color:(" << color_.r << "," << color_.g <<"," <<color_.b <<")";
            return os;
		}

ostream& operator<<(ostream& os,Shape const& s){
	ostream::sentry const ostream_sentry(os);
	return ostream_sentry ? s.print(os) : os;
}