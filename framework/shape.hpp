#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <cmath>
#include <iostream>    
#include "color.hpp"
#include "ray.hpp"
using namespace std;    
  
class Shape{
public:
// Aufgabe 5.3
		Shape();
		Shape(string const& name, Color const& color);
		virtual ~Shape();
	    //~Shape();
		// Destruktoren legt man nur an wenn sie Sekundärressourcen freigeben muessen 

// Aufgabe 5.1
		virtual double area() const=0;  // 在 .hpp 写virtual; 在 .cpp 不需要写
		virtual double volume() const=0; // Wir koennen kein statisches/dynamsiches Objekt von Shape anlegen
										// sondern nur ein Pointer/Referenz

// Aufgabe 5.4
		virtual ostream& print(ostream& os) const;

// Aufgabe 6.3
		virtual bool intersect (Ray const& ray, float& distance)=0;

// Aufgabe 5.3
protected: // abgleiteted Klasse wird diese Attribute aufrufen( vererben diese Attribute als private )
		string name_;
		Color color_;
	
};

// Aufgabe 5.4
ostream& operator<<(ostream& os,Shape const& s);

#endif