#ifndef SPHERE_HPP   
#define SPHERE_HPP
#include <glm/vec3.hpp>  
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>     
#include "shape.hpp"
#include <string>
#include "material.hpp"

using namespace std;
// Mittelpunkt und einen Radius
// Konstruktor; get-Methoden; Methoden area und volume

class Sphere : public Shape{
public: 
// Aufgabe 5.2     
	Sphere();
	Sphere(glm::vec3 const& mittelpunkt, double radius);
	//Sphere(glm::vec3 const& mittelpunkt, double radius=1.0f);
	// Dafault Werte um die Groesse des Sphere zu setzen, aehnlich wie Standardkonstruktor

	Sphere(string const& name, shared_ptr<Material> const& material, glm::vec3 const& mittelpunkt, double radius);
	~Sphere();

	//double area() const override;		// area(),volume() 在hpp写override, 在cpp不需要
	//double volume() const override;

	glm::vec3 get_mittelpunkt() const; // get_Methode() 为const
	double get_radius() const;

	shared_ptr<Material> get_Material() const;

// Aufgabe 5.5
	ostream& print(ostream& os) const override;

// Aufgabe 5.6
	bool intersect (Ray const& ray, float& t) const override;
	intersectionResult istIntersect(Ray const& ray,float& t) const override;
	glm::vec3 getNormal(intersectionResult const& schnittpunkt) const override;

	glm::vec3 mittelpunkt_;
	double radius_;

};	
#endif