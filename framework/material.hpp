#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
//#include "light.hpp"
//#include "ray.hpp"
#include <cmath>
using namespace std;
struct Material{
	string name;
	Color ka;
	Color kd;
	Color ks;
	float exponente_m;

  Material():
    name{"default material_name"},
    ka{1,0,0}, // reflexion->ambiente Beleuchtung
    kd{1,0,0}, //red diffuse -> einfache Beleuchtungsmodell
    ks{1,1,1}, //white Spiegeln
    exponente_m{16.0f} {}

  Material(string const& name_, Color const& ka_, Color const& kd_, Color const& ks_, float exponente_m_ ):
    name{name_},
    ka{ka_},
    kd{kd_},
    ks{ks_},
    exponente_m{exponente_m_} {}
  

	friend ostream& operator<<(ostream& os, Material const& m)
  {
  	os << "Material Name: "<<m.name <<" k_a: "<<"("<< (m.ka).r<<","<< (m.ka).g<<","<<(m.ka).b<<") "<< 
  	" k_d"<<"("<< (m.kd).r<<","<< (m.kd).g<<","<<(m.kd).b<<") "<<
  	" k_s: "<<"("<< (m.ks).r<<","<< (m.ks).g<<","<<(m.ks).b<<") "<<
  	" exponente_m: "<< m.exponente_m<<endl;
    return os;
  }

};



#endif