#ifndef SCENE_HPP
#define SCENE_HPP
#include "box.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
struct Scene{
	string name="102";
	//Material material;
	//Shape shape;
};

void open_sdf_datei(string const& filename);

#endif