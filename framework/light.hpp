#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <string>
#include "color.hpp"
#include <glm/vec3.hpp>
class LIGHT{

public:
	LIGHT();
	LIGHT(string const& name, glm::vec3 position, Color const& color, float brightness);
	~LIGHT();

	string name_;
	glm::vec3 position_;
	Color color_;
	float brightness_;


};

#endif