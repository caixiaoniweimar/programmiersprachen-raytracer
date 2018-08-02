#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP
#include "shape.hpp" 
#include <vector>
#include <glm/vec3.hpp>
#include <memory>
#include "shape.hpp"

using namespace std;

class Composite: public Shape{

public:
	Composite();
	Composite(string const& name);
	~Composite();

	void add( shared_ptr<Shape> objekt );
	intersectionResult istIntersect(Ray const& ray,float& t) const override;
	bool intersect(Ray const& ray, float& t) const override;
	glm::vec3 getNormal(intersectionResult const& schnittpunkt) const override;

public:
	vector<shared_ptr<Shape>> composite_;

};

#endif