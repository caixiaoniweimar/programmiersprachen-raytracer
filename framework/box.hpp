#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
#include <string>
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"
//Minimum und Maximum vec3
// Konstruktoren; get-Methoden; Methoden area und volume
class Box : public Shape{
public:  
// Aufgabe 5.2       
	Box();        
	Box(glm::vec3 const& min, glm::vec3 const& max);
	Box(string const& name, shared_ptr<Material> const& material, glm::vec3 const& min, glm::vec3 const& max );
	~Box();

	double area() const override; // area(),volume() im hpp override, im cpp keine!
	double volume() const override;

	glm::vec3 get_min() const;
	glm::vec3 get_max() const;

// Aufgabe 5.5
	ostream& print(ostream& os) const override;
	intersectionResult istIntersect(Ray const& ray,float& t) const override;


// Aufgabe 6.3
	bool intersect (Ray const& ray, float& t) const override;



public:
	glm::vec3 minimum_;
	glm::vec3 maximum_;
};

#endif