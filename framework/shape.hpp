#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <cmath>
#include <iostream>

class Shape{
public:
	// zwei Methoden
		//Shape();

		virtual double area() const=0; 
		virtual double volume() const=0;


		virtual ~Shape();
private:
	
};

//class Circle :: public Shape{
//	public:
//		double area() const override;
//}
#endif