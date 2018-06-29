#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include <iostream>

struct Material{
	string name="default material_name";
	Color ka{0,0,0};
	Color kd{0,0,0};
	Color ks{0,0,0};
	float exponente_m=0.0f;
};

#endif