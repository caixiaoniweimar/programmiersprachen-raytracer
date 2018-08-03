#include "composite.hpp"
Composite::Composite():
		Shape::Shape(),
		composite_{} {}
Composite::Composite(string const& name):
		Shape::Shape(name),
		composite_{} {}
Composite::~Composite() {}

void Composite::add( shared_ptr<Shape> objekt ) {
        composite_.push_back(objekt);
}

intersectionResult Composite::istIntersect(Ray const& ray,float& t) const{
		intersectionResult result;
		intersectionResult tmp_Result;
		for( int i=0; i< composite_.size(); ++i ){
				tmp_Result = composite_[i]->istIntersect(ray,t);
			if( tmp_Result.distance < result.distance ){    
				result=tmp_Result;
			} 
		}
		return result;
}

bool  Composite::intersect(Ray const& ray, float& t) const{
	intersectionResult result=istIntersect(ray,t);
    return result.closest_shape->intersect(ray,t);
}
glm::vec3  Composite::getNormal(intersectionResult const& schnittpunkt) const{
    return schnittpunkt.closest_shape->getNormal(schnittpunkt);
}