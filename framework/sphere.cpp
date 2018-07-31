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

	double Sphere::area() const {
		//std::cout << name_;
		return 4*M_PI*radius_*radius_;
	}

	double Sphere::volume() const {
		return (4.0/3.0) * M_PI * radius_ * radius_ * radius_;
	}

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

    glm::vec3 Sphere::getNormal(glm::vec3 schnittpunkt) const{
    	return glm::vec3{ (schnittpunkt - mittelpunkt_)/((float)radius_)};
    }

    // getNormal Methode gleich wie result.normal!!!

    intersectionResult Sphere::istIntersect(Ray const& ray,float& t) const{
    	intersectionResult result{};
    	if(intersect(ray,t)==true)
    		{	
    			result.hit=true;
    			result.distance = t;
    			result.position=ray.getpoint(result.distance);
    			result.normal = glm::normalize(result.position - mittelpunkt_);
    			//cout<<"benutzt Sphere istIntersect"<<endl;
    		}
    	return result;
    }

    /*Color Sphere::rechnen_diffuse_reflexion(Light const& light, Material const& material, intersectionResult const& result, Color const& ambiente) const{
        glm::vec3 L = glm::normalize(light.position_ - result.position);
        glm::vec3 N = result.normal; //glm::vec3 N = sphere.getNormal(result.position);
        Color diffuseColor = light.rechnen_intensitaet() * (material.kd) * std::max(glm::dot(L,N),(float)0);
        Color reflexion = diffuseColor + ambiente*(material.ka); 
        return reflexion+diffuseColor;
    }*/

    /*Color Sphere::rechnen_diffuse_reflexion(Light const& light, Camera const& camera, Material const& material, intersectionResult const& result, Color const& ambiente) const{
        glm::vec3 L = glm::normalize(light.position_ - result.position);
        glm::vec3 N = result.normal; //glm::vec3 N = sphere.getNormal(result.position);
        float LNdot = glm::dot(L,N); // erlaubt klein 0?

        glm::vec3 R = glm::normalize(2 * LNdot * N-L);
        glm::vec3 V = glm::normalize( camera.eye_ - result.position );

        float RVdot = glm::dot(R,V);

        Color spiegeln = (material.ks) * (pow(std::max(RVdot,(float)0),material.exponente_m ));
        Color diffuseColor = light.rechnen_intensitaet() * (material.kd) * std::max(glm::dot(L,N),(float)0);
        Color reflexion = ambiente*(material.ka); 
        return reflexion+diffuseColor+spiegeln;
    }*/
   














	