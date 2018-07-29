#ifndef LIGHT_HPP
#define LIGHT_HPP
#include "color.hpp"
#include <iostream>
#include <glm/vec3.hpp>
using namespace std;

class Light{

public:
	Light():
		name_{"default name fuer Light"},
		position_{10.0f,20.0f,10.0f},
		color_{1.0f,1.0f,1.0f},
	    brightness_{2000.0f} {}
	    //isSchatten_{false} 

	Light(string const& name,glm::vec3 position,Color const& color,float brightness):
		name_{name},
		position_{position}, 
		color_{color},
		brightness_{brightness}{}
		//isSchatten_{isSchatten} 

	~Light(){}
	/*Color intersect(scene const& scene, intersectionResult& result){
		//const float k=1e-4;
	}*/
	Color rechnen_intensitaet() const {
		Color intensitaet {color_*brightness_} ;
		return intensitaet;
	}
public:
	string name_;
	glm::vec3 position_;
	Color color_;
	float brightness_;
	//bool isSchatten_;
};
/*struct Light{
	string name{"default name fuer light"};
	glm::vec3 position{0,0,0};
	Color color{1,1,1};
	float brightness =1;

};*/
#endif