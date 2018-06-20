#include "shape.hpp"

// Aufgabe 5.3
Shape::Shape():
	name_{"default name"},    
	color_{0.0f,0.0f,0.0f} {
	//std::cout << "Hier benutze ich den Konstruktor von Shape!\n";
	}

Shape::Shape(string const& name, Color const& color):
	name_{name},
	color_{color} {
	//std::cout << "Hier benutze ich den Konstruktor von Shape!\n";
	}      
 
Shape::~Shape() {
	//std::cout << "Hier benutze ich den Destruktor von Shape!\n";
}

// Aufgabe 5.4
ostream& Shape::print(ostream& os) const{ 
			os << "Name: " << name_ <<" Color:(" << color_.r << "," << color_.g <<"," <<color_.b <<")";
            return os;
		}

ostream& operator<<(ostream& os,Shape const& s){
	ostream::sentry const ostream_sentry(os);
	return ostream_sentry ? s.print(os) : os;
}