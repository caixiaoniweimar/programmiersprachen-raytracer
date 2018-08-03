#ifndef BOX_HPP
#define BOX_HPP 

 
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>     
#include "shape.hpp"
#include <string>
#include "material.hpp"
using namespace std;
#include <catch.hpp>
#include <glm/vec3.hpp> 
#include <algorithm>
//Minimum und Maximum vec3
// Konstruktoren; get-Methoden; Methoden area und volume
class Box : public Shape{
public:  
// Aufgabe 5.2       
	Box();        
	Box(glm::vec3 const& min, glm::vec3 const& max);
	Box(string const& name, shared_ptr<Material> const& material, glm::vec3 const& min, glm::vec3 const& max );
	~Box();
	//double area() const override; // area(),volume() im hpp override, im cpp keine!
	//double volume() const override;
	glm::vec3 get_min() const;
	glm::vec3 get_max() const;
	shared_ptr<Material> get_Material() const;
// Aufgabe 5.5
	ostream& print(ostream& os) const override;

	bool intersect_neue (Ray const& ray, float& t, glm::vec3& normal) const;
	bool intersect (Ray const& rsay, float& t) const override;
	glm::vec3 get_normal(int plane) const;
	intersectionResult istIntersect(Ray const& ray,float& t) const override;
	glm::vec3 getNormal(intersectionResult const& schnittpunkt) const override;


	glm::vec3 minimum_;
	glm::vec3 maximum_;
};

#endif