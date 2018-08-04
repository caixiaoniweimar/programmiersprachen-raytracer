#ifndef DREIECK_HPP   
#define DREIECK_HPP
#include <glm/vec3.hpp>  
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>     
#include "shape.hpp"
#include <string>
#include "material.hpp"
using namespace std;
class Dreieck : public Shape{
public:
    Dreieck();
    Dreieck(Dreieck const& dreieck);
    Dreieck(glm::vec3 punkt1, glm::vec3 punkt2, glm::vec3 punkt3);
    Dreieck(string const& name, shared_ptr<Material> const& material,glm::vec3 punkt1, glm::vec3 punkt2, glm::vec3 punkt3);
    ~Dreieck();

	bool intersect (Ray const& ray, float& t) const override;
	intersectionResult istIntersect(Ray const& ray,float& t) const override;
    glm::vec3 getNormal() const;
    //ignorieren
	glm::vec3 getNormal(intersectionResult const& schnittpunkt) const override;

    glm::vec3 punkt1_;
    glm::vec3 punkt2_;
    glm::vec3 punkt3_;

};
#endif