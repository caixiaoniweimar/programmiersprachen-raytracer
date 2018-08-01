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
	Composite():
		Shape(),
		composite_{} {}

	void add( shared_ptr<Shape> objekt ){
		composite_.push_back(objekt);
	}

	// vergleichen die naehesten Objekt!!(closet_distance!!!)
	intersectionResult istIntersect(Ray const& ray,float& t) const override{
		intersectionResult result;
		intersectionResult tmp_Result;
		for( int i=0; i< composite_.size(); ++i ){
				tmp_Result = composite_[i]->istIntersect(ray,t);
			if( tmp_Result.distance < result.distance ){
				result=tmp_Result;
			} 
		}
		return result;
	}

// Shape ist abstract Class!!
	double area() const {
		return 0;
	}
	double volume() const {
		return 0;
	}
	bool intersect(Ray const& ray,float& t) const{ 
		return false;
	}

	~Composite(){}

public:
	vector<shared_ptr<Shape>> composite_;

};

#endif