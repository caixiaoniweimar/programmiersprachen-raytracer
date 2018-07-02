#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include <iostream>
using namespace std;
struct Material{
	string name="default material_name";
	Color ka{0,0,0};
	Color kd{0,0,0};
	Color ks{0,0,0};
	float exponente_m=0.0f;

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