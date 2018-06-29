#ifndef SPHERE_HPP   
#define SPHERE_HPP
#include <glm/vec3.hpp>  
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>     
#include "shape.hpp"
#include <string>
#include "color.hpp"
#include "ray.hpp"
// Mittelpunkt und einen Radius
// Konstruktor; get-Methoden; Methoden area und volume

class Sphere : public Shape{
public:
// Aufgabe 5.2     
	Sphere();
	Sphere(glm::vec3 const& mittelpunkt, double radius);
	//Sphere(glm::vec3 const& mittelpunkt, double radius=1.0f);
	// Dafault Werte um die Groesse des Sphere zu setzen, aehnlich wie Standardkonstruktor

	Sphere(string const& name, Color const& color, glm::vec3 const& mittelpunkt, double radius);
	~Sphere();

	double area() const override;		// area(),volume() 在hpp写override, 在cpp不需要
	double volume() const override;

	glm::vec3 get_mittelpunkt() const; // get_Methode() 为const
	double get_radius() const;

// Aufgabe 5.5
	ostream& print(ostream& os) const override;

// Aufgabe 5.6
	bool intersect (Ray const& ray, float& distance) override;

private:
	glm::vec3 mittelpunkt_;
	double radius_;

};

/*struct Ray{
	glm::vec3 origin={0.0f,0.0f,0.0f};
	glm::vec3 direction={0.0f,0.0f,-1.0f};
};*/

// Aufgabe 5.6
	
#endif