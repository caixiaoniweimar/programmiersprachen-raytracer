#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <cmath>
#include <iostream>    
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"
#include <glm/glm.hpp>

using namespace std;    

struct intersectionResult;
class Shape{
public:
// Aufgabe 5.3
		Shape();
		//Shape(string const& name, Color const& color);
		Shape(string const& name);
		Shape(string const& name, shared_ptr<Material> const& material);
		virtual ~Shape();
		// Destruktoren legt man nur an wenn sie Sekundärressourcen freigeben muessen 
// Aufgabe 5.1
		//virtual double area() const=0;  // 在 .hpp 写virtual; 在 .cpp 不需要写
		//virtual double volume() const=0; // Wir koennen kein statisches/dynamsiches Objekt von Shape anlegen
										// sondern nur ein Pointer/Referenz

// Aufgabe 5.4
		virtual ostream& print(ostream& os) const;

// Aufgabe 6.3
		virtual bool intersect (Ray const& ray, float& t) const=0;
		virtual intersectionResult istIntersect(Ray const& ray,float& t) const=0;
		virtual glm::vec3 getNormal(intersectionResult const& schnittpunkt) const=0;

		void set_name(string const& name);
		string get_name() const;

		void set_material(shared_ptr<Material> const& material);
		shared_ptr<Material> get_material() const;

		void set_transformation(glm::mat4 world_transfor);
		glm::mat4 get_transformation() const;
		void set_transformation_inv(glm::mat4 world_transfor_inv);
		glm::mat4 get_transformation_inv() const;
		
		Ray transformRay(glm::mat4 const& mat, Ray const& ray)const;

// Aufgabe 5.3
// abgleiteted Klasse wird diese Attribute aufrufen( vererben diese Attribute als private )
protected:
		string name_;
// Aufgabe 6.4
		shared_ptr<Material> material_;
// Aufgabe 7.5
		glm::mat4 world_transformation_{1,0,0,0,
										0,1,0,0,
										0,0,1,0,
										0,0,0,1};      // EinheitMatrix
		glm::mat4 world_transformation_inv_{1,0,0,0,
											0,1,0,0,
											0,0,1,0,
											0,0,0,1};

};
// Aufgabe 5.4
ostream& operator<<(ostream& os,Shape const& s);

struct intersectionResult{
	float distance;
	bool hit;
	glm::vec3 position; 
	glm::vec3 normal;
	//shared_ptr<Shape> closest_shape;
    Shape const* closest_shape;  // ?!!!!!
	// sphere.cpp result.closest_shape = this !! Fehler! (wenn kein *)

	intersectionResult():
		distance{2000.0},
		hit{false},
		position{0,0,0},
		normal{0,0,0}, 
		closest_shape{nullptr}
		{}
	intersectionResult( intersectionResult const& result):
	    distance{result.distance},
	    hit{result.hit},
	    position{result.position},
	    normal{result.normal}, 
		closest_shape{result.closest_shape}
		{}
	intersectionResult(Shape const* closest_shape_):
	    distance{2000.0},
	    hit{false},
	    position{0,0,0},
	    normal{0,0,0}, 
		closest_shape{closest_shape_}
		{}
};
#endif



