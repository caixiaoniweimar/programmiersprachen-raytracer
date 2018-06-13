#ifndef SPHERE_HPP   
#define SPHERE_HPP
#include <glm/vec3.hpp>   
#include "shape.hpp"
// Mittelpunkt und einen Radius
// Konstruktor; get-Methoden; Methoden area und volume
class Sphere : public Shape{
public:
// Aufgabe 5.2     
	Sphere(); 
	Sphere(Sphere const& s); // copy Konstruktor
	Sphere(glm::vec3 const& mittelpunkt, double radius);
	~Sphere() override;

	double area() const override;
	double volume() const override;
	glm::vec3 get_mittelpunkt() const;
	double get_radius() const;

// Aufgabe 5.5
	ostream& print(ostream& os) const override;

// Aufgabe 5.6


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