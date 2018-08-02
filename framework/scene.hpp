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
#include <glm/vec3.hpp>
#include <set>
#include <map>
using namespace std;
#include <algorithm>
#include "light.hpp"
#include "camera.hpp"
#include "composite.hpp"

using material_ptr = std::shared_ptr<Material>;

struct Scene{
	vector<shared_ptr<Material>> vector_material;
	set<shared_ptr<Material>> set_material;
	map<string, shared_ptr<Material>> map_material;

// Aufgabe 7.2
	vector<shared_ptr<Shape>> container_objekt;
    // speichert Objekt im Composite
    shared_ptr<Composite> root;

	vector<Light> container_light;
	Camera camera{};

	Color ambiente{0.0f,0.0f,0.0f}; 
};
// Aufgabe 6.5
Scene open_sdf_datei(string const& filename);

// Aufgabe 6.5 find_vector
material_ptr vector_find(string const& such_name, vector<material_ptr> vector_material);

shared_ptr<Shape> shape_vector_find( string const& such_name, vector<shared_ptr<Shape>> container_objekt ); 

material_ptr map_find(string const& such_name, map< string, shared_ptr<Material> > map_material);

material_ptr set_find(string const& such_name, set< shared_ptr<Material> > set_material);









#endif