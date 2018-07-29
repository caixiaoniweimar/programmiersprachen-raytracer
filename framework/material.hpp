#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

using namespace std;
struct Material{
	string name;
	Color ka;
	Color kd;
	Color ks;
	float exponente_m;

  Material():
    name{"default material_name"},
    ka{0,0,1},
    kd{0,0,1},
    ks{0,0,1},
    exponente_m{10.0f} {}

	friend ostream& operator<<(ostream& os, Material const& m)
  {
  	os << "Material Name: "<<m.name <<" k_a: "<<"("<< (m.ka).r<<","<< (m.ka).g<<","<<(m.ka).b<<") "<< 
  	" k_d"<<"("<< (m.kd).r<<","<< (m.kd).g<<","<<(m.kd).b<<") "<<
  	" k_s: "<<"("<< (m.ks).r<<","<< (m.ks).g<<","<<(m.ks).b<<") "<<
  	" exponente_m: "<< m.exponente_m<<endl;
    return os;
  }

  Color get_ka() const{
    return ka;
  }

};



#endif