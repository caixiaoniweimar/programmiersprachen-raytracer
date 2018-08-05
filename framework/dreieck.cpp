#include "dreieck.hpp"

Dreieck::Dreieck():
    Shape(),
    punkt1_{0,0,0},
    punkt2_{0,0,1},
    punkt3_{1,0,0} {}

Dreieck::Dreieck(Dreieck const& dreieck):
    Shape(),
    punkt1_{dreieck.punkt1_},
    punkt2_{dreieck.punkt2_},
    punkt3_{dreieck.punkt3_} {}

Dreieck::Dreieck(glm::vec3 punkt1, glm::vec3 punkt2, glm::vec3 punkt3):
    Shape(),
    punkt1_{punkt1},
    punkt2_{punkt2},
    punkt3_{punkt3} {}

Dreieck::Dreieck(string const& name, shared_ptr<Material> const& material,glm::vec3 punkt1, glm::vec3 punkt2, glm::vec3 punkt3):
    Shape(name,material),
    punkt1_{punkt1},
    punkt2_{punkt2},
    punkt3_{punkt3} {}

Dreieck::~Dreieck(){};

// wichtig::
bool Dreieck::intersect (Ray const& ray, float& t) const{
    bool result = false;
    // benutzt Matrix besser zu verstehen und berechnen, Determinante!!!!!
    float a = (punkt1_.y - punkt3_.y)*(ray.direction.z) - (ray.direction.y)*(punkt1_.z - punkt3_.z);
    float b = (punkt1_.y - ray.origin.y)*(ray.direction.z) - (ray.direction.y)*(punkt1_.z - ray.origin.z);
    float c = (punkt1_.y - punkt3_.y)*(punkt1_.z - ray.origin.z) - (punkt1_.y - ray.origin.y)*(punkt1_.z - punkt3_.z);
    float d = (ray.direction.y)*(punkt1_.z - punkt2_.z)-(punkt1_.y - punkt2_.y)*(ray.direction.z);
    float e = (punkt1_.y - punkt2_.y)*(punkt1_.z - punkt3_.z)-(punkt1_.y - punkt3_.y)*(punkt1_.z - punkt2_.z);

    float nenner_sum = (punkt1_.x - punkt2_.x)*a + (punkt1_.x - punkt3_.x)*d +(ray.direction.x)*e;
    float inverse_deter = 1.0/nenner_sum;
    float f1 = (punkt1_.x - ray.origin.x)*a - (punkt1_.x - punkt3_.x)*b - (ray.direction.x)*c;
    float det1 = f1*inverse_deter;
    if(det1<0.0f){
        return result;}
    float g = (punkt1_.y - punkt2_.y)*(punkt1_.z - ray.origin.z) -(punkt1_.y - ray.origin.y)*(punkt1_.z - punkt2_.z);
    float f2 = (punkt1_.x - punkt2_.x)*b + (punkt1_.x - ray.origin.x)*d + (ray.direction.x)*g;
    float det2 = f2*inverse_deter;
    if(det2<0.0){
        return result;}
    if(det1+det2>1.0f){
        return result;}
    float f3 = (punkt1_.x - punkt2_.x)*c - (punkt1_.x - punkt3_.x)*g + (punkt1_.x - ray.origin.x)*e;
    float distance = f3*inverse_deter;
    if(distance<10e-6) {
        return result;}
    t=distance;
    result=true;
    return result;
}
glm::vec3 Dreieck::getNormal() const{
    glm::vec3 normal;
    normal=glm::cross((punkt1_ - punkt2_),(punkt1_ - punkt3_));
    return glm::normalize(normal);
}
//andere Art Dreieck,benutzt glm
/*bool Dreieck::intersect_auto(Ray const& ray, float& t, glm::vec3& schnittpunkt) const{
    bool result=false;
    result = glm::intersectRayTriangle(ray.origin, ray.direction,
        punkt1_,punkt2_,punkt3_,schnittpunkt);
    return result;
}*/
intersectionResult Dreieck::istIntersect(Ray const& ray,float& t) const{
   intersectionResult result{};
    	if(intersect(ray,t)==true)
    		{	
    			result.hit=true;
    			result.distance = t;
    			result.position=ray.getpoint(result.distance);
    			result.normal = getNormal();
				result.closest_shape=this;   
    		}
    	return result;
}
glm::vec3 Dreieck::getNormal(intersectionResult const& schnittpunkt) const{
    return schnittpunkt.normal;
}

glm::vec3 Dreieck::get_punkt1() const{
    return punkt1_;
}
glm::vec3 Dreieck::get_punkt2() const{
    return punkt2_;
}
glm::vec3 Dreieck::get_punkt3() const{
    return punkt3_;
}