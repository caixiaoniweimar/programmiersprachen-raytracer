#include "sphere.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
using namespace std;
// wichtig!! wenn keine Complier,wird erzeugt Complier automatisch
// Aufgabe 5.2
	Sphere::Sphere():  
		Shape(),
		mittelpunkt_{0.0f,0.0f,0.0f},
		radius_{1.0} {}
    
    Sphere::Sphere(glm::vec3 const& mittelpunkt, double radius):
    	Shape(),
		mittelpunkt_{mittelpunkt},
		radius_{radius}
		{}

// Aufgabe 5.3
	Sphere::Sphere(string const& name, shared_ptr<Material> const& material, glm::vec3 const& mittelpunkt, double radius):
		Shape(name, material), // 重要!!!!
		// einzige Moeglichkeit um auf die Membervariable der Basisklasse zuzugreifen
		mittelpunkt_{mittelpunkt},
		radius_{radius} {
		/*cout<<"Hier benutze ich Konstruktor von Sphere namens: " << name_ << "!"<<endl;*/
		}

	Sphere::~Sphere(){//cout<<"Hier benutze ich Destruktor von Sphere namens: " << name_ << "!"<<endl;
	}  

	/*double Sphere::area() const {
		//std::cout << name_;
		return 4*M_PI*radius_*radius_;
	}

	double Sphere::volume() const {
		return (4.0/3.0) * M_PI * radius_ * radius_ * radius_;
	}*/

	glm::vec3 Sphere::get_mittelpunkt() const{
		return mittelpunkt_;
	}

	double Sphere::get_radius() const {
		return radius_;
	}

	shared_ptr<Material> Sphere::get_Material() const {
		return material_;
	}

// Aufgabe 5.5
	ostream& Sphere::print(ostream& os) const {
		Shape::print(os);
		os<<" Mittelpunkt: "<<"( "<<mittelpunkt_.x<<","<<mittelpunkt_.y<<","<<mittelpunkt_.z
		  <<" )"<<"Radius: "<<radius_;
		return os;
	}

// Aufgabe 5.6
	bool Sphere::intersect(Ray const& ray,float& t) const{ 
		glm::vec3 ray_direction=glm::normalize(ray.direction);
		auto result=glm::intersectRaySphere(ray.origin, ray_direction, mittelpunkt_, radius_*radius_, t);
		return result;
	}
	// Mit reference veraedert die Variable ausserhalb 
	// Mit per value veraedert die Variable nur innerhalb der Methode 

    glm::vec3 Sphere::getNormal(intersectionResult const& schnittpunkt) const{
    	return glm::normalize( glm::vec3{(schnittpunkt.position - mittelpunkt_)} );
    }
    // getNormal Methode gleich wie result.normal!!!

    // 之后考虑新Ray, transformRay
   intersectionResult Sphere::istIntersect(Ray const& ray,float& t) const{
    	intersectionResult result{};
// Theresa SDF Datei intersect funktioniert
    	if(intersect(ray,t)==true)
    		{	
    			result.hit=true;
    			result.distance = t;
    			result.position=ray.getpoint(result.distance);
    			result.normal = glm::normalize(result.position - mittelpunkt_);
				result.closest_shape=this;
				//cout<<"Sphere"<<endl;   
    		}
    	return result;
    }

   














	