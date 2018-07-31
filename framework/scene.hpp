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
#include "intersection_Result.hpp"
#include "ray.hpp"


using material_ptr = std::shared_ptr<Material>;

struct Scene{
	vector<shared_ptr<Material>> vector_material;
	set<shared_ptr<Material>> set_material;
	map<string, shared_ptr<Material>> map_material;

// Aufgabe 7.2
	vector<shared_ptr<Shape>> container_objekt;
	vector<Light> container_light;
	Camera camera{};

	Color ambiente{0.0f,0.0f,0.0f}; 

	Color viel_object_intersect(Ray const& ray) const{
		float minDistance = 100;
		intersectionResult minResult = intersectionResult{};
		int size = container_objekt.size();

		int min_object_index= -1;
           
		// for all object 
		for( int i=0; i<size; ++i ){
			float t = 2000;
			intersectionResult result = container_objekt[i]->istIntersect(ray,t); // result.hit 0/1; result.t auch change; beidem funktionieren

			if( result.hit==true  &&(result.distance < minDistance) ){ // hit=1
				minDistance = result.distance;
				min_object_index=i;
			}
		}
		if(min_object_index != -1){  // index unmoeglich gleich -1 !!! das heisst, nie zurueck ambiente
			return schatten( container_objekt[min_object_index], ray, minDistance ); 
		}
		else{
			return ambiente; // ambiente
		}
	}

	Color schatten(shared_ptr<Shape> const& objekt, Ray const& ray, float t) const{
		intersectionResult schnittpunkt = objekt->istIntersect(ray,t);
		
		Color black{0,0,0};
		Color resultColor = ambiente*( (objekt->material_)->ka);

        for( int i=0; i < container_light.size(); ++i ){
           Ray licht_ray{ schnittpunkt.position, container_light[i].position_ };
              for( int j=0; j < container_objekt.size(); ++j ){
              	intersectionResult licht_result = container_objekt[j]->istIntersect(licht_ray,t);
            
        	    if(licht_result.hit==false){

                	glm::vec3 L = glm::normalize(container_light[i].position_ - schnittpunkt.position);
        			glm::vec3 N = schnittpunkt.normal; //glm::vec3 N = sphere.getNormal(result.position);
        			float LNdot = glm::dot(L,N); // erlaubt klein 0?

       				glm::vec3 R = glm::normalize(2 * LNdot * N-L);
        			glm::vec3 V = glm::normalize( camera.eye_ - schnittpunkt.position );

        			float RVdot = glm::dot(R,V);

        			Color spiegeln = ( (objekt->material_)->ks) * (pow(std::max(RVdot,(float)0), (objekt->material_)->exponente_m ));
        			Color diffuseColor = container_light[i].rechnen_intensitaet() * ( (objekt->material_)->kd) * std::max(glm::dot(L,N),(float)0);
        			resultColor += spiegeln + diffuseColor;
                }
 
              }
        }
		return resultColor;
	}

};
// Aufgabe 6.5
Scene open_sdf_datei(string const& filename);

// Aufgabe 6.5 find_vector
material_ptr vector_find(string const& such_name, vector<material_ptr> vector_material);

material_ptr map_find(string const& such_name, map< string, shared_ptr<Material> > map_material);

material_ptr set_find(string const& such_name, set< shared_ptr<Material> > set_material);









#endif