#include "shape.hpp"

// Aufgabe 5.3
Shape::Shape():
	name_{"default name"},    
	material_{} {
	//std::cout << "Hier benutze ich den Konstruktor von Shape!\n";
	}
Shape::Shape(string const& name):
	name_{name},
	material_{} {}

//Shape::Shape(string const& name, Color const& color):
Shape::Shape(string const& name, shared_ptr<Material> const& material):	
	name_{name},
	material_{material} {
	//std::cout << "Hier benutze ich den Konstruktor von Shape!\n";
	}      
 
Shape::~Shape() {
	//std::cout << "Hier benutze ich den Destruktor von Shape!\n";
}

void Shape::set_name(string const& name){
	this->name_=name;
}
string Shape::get_name() const{
	return name_;
}

void Shape::set_material(shared_ptr<Material> const& material){
	material_=material;
}
shared_ptr<Material> Shape::get_material() const{
	return material_;
}

void Shape::set_transformation(glm::mat4 world_transfor){
	world_transformation_=world_transfor;
}
glm::mat4 Shape::get_transformation() const{
	return world_transformation_;
}
void Shape::set_transformation_inv(glm::mat4 world_transfor_inv){
	world_transformation_inv_ = world_transfor_inv;
}
glm::mat4 Shape::get_transformation_inv() const{
	return world_transformation_inv_;
}

// Aufgabe 5.4
ostream& Shape::print(ostream& os) const{  //重要！！！material_ -> name  区别于material.hpp中的<<重载 这里是 
	// shape对象的material属性 再到material的类中 读material的ka,name等属性 所以需要"->"
			os << "Name: " << name_ <<
			 "Material Name: "<<material_->name <<" k_a: "<<"("<< (material_->ka).r<<","<< (material_->ka).g<<","<<(material_->ka).b<<") "<<
  			 " k_d"<<"("<< (material_->kd).r<<","<< (material_->kd).g<<","<<(material_->kd).b<<") "<<
  			 " k_s: "<<"("<< (material_->ks).r<<","<< (material_->ks).g<<","<<(material_->ks).b<<") "<<
  			 " exponente_m: "<< material_->exponente_m<<endl; 
            return os;
		}

ostream& operator<<(ostream& os,Shape const& s){
	ostream::sentry const ostream_sentry(os);
	return ostream_sentry ? s.print(os) : os;
}

// Aufgabe 7.5
Ray Shape::transformRay(glm::mat4 const& mat, Ray const& ray) const{
	glm::vec4 a{ray.origin,1.0f};
	glm::vec4 b{ray.direction,0.0f};
	glm::vec3 origin1{mat*a};
	glm::vec3 direction1{mat*b};
	Ray new_Ray{origin1,direction1};
	return new_Ray;
}





