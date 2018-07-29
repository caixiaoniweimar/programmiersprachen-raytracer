#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP
#include "box.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

class Composite: public Shape{

public:

	void add( shared_ptr<Shape> objekt ){
		composite_.push_back(objekt);
	}

	double area() const {
		return 0;
	}
	double volume() const {
		return 0;
	}
	bool intersect(Ray const& ray,float& t) const{ 
		return false;
	}


public:
	string name_;
	list<shared_ptr<Shape>> composite_;

};

#endif