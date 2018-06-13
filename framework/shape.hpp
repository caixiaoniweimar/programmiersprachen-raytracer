#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <cmath>
#include <iostream>
#include "color.hpp"
using namespace std;

class Shape{
public:
	// zwei Methoden
		Shape();
		Shape(string name, Color const& color);
		Shape(Shape const& shape);
		virtual ~Shape();

		virtual double area() const=0; 
		virtual double volume() const=0;

// Aufgabe 5.4
		virtual ostream& print(ostream& os) const;

// Aufgabe 5.3
protected:
		string name_;
		Color color_;
	
};

// Aufgabe 5.4
ostream& operator<<(ostream& os,Shape const& s);

#endif