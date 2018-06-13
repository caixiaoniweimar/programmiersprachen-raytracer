#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
//Minimum und Maximum vec3
// Konstruktoren; get-Methoden; Methoden area und volume
class Box : public Shape{
public:  
// Aufgabe 5.2     
	Box();
	Box(glm::vec3 const& min, glm::vec3 const& max);
	Box( Box const& box );
	~Box() override;

	double area() const override;
	double volume() const override;

	glm::vec3 get_min() const;
	glm::vec3 get_max() const;

// Aufgabe 5.5
	ostream& print(ostream& os) const override;

private:
	glm::vec3 minimum_;
	glm::vec3 maximum_;
};

#endif