#include "box.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
using namespace std;
// Aufgabe 5.2
Box::Box():
	Shape(),
	minimum_{0.0f,0.0f,0.0f},
	maximum_{1.0f,1.0f,1.0f}{}
    
Box::Box(glm::vec3 const& min, glm::vec3 const& max):
	Shape(),
	minimum_{min},
	maximum_{max} {}      

// Aufgabe 5.3
Box::Box(string const& name, shared_ptr<Material> const& material, glm::vec3 const& min, glm::vec3 const& max ):
	Shape(name,material), // !!wichtig!!
	minimum_{min},
	maximum_{max} {}   

Box::~Box() {}   
	
	double Box::area() const{     
		double length= maximum_.x - minimum_.x;
		double height= maximum_.y - minimum_.y;
		double width= maximum_.z - minimum_.z;
		return 2*length*height+2*length*width+2*height*width;
	}

	double Box::volume() const{
		double length= maximum_.x - minimum_.x;
		double height= maximum_.y - minimum_.y;
		double width= maximum_.z - minimum_.z;
		return length*height*width;
	}

	glm::vec3 Box::get_min() const{
		return minimum_;
	}

	glm::vec3 Box::get_max() const{
		return maximum_;
	}

// Aufgabe 5.5
	ostream& Box::print(ostream& os) const{
		Shape::print(os);
		os<<" Maximum: "<<"( "<< maximum_.x<<","<<maximum_.y<<","<<maximum_.z<<" )"
		<<" Minimum: "<<"( "<<minimum_.x<<","<<minimum_.y<<","<<minimum_.z<<" )";
		return os;
	}

// Aufgabe 6.3
bool Box::intersect (Ray const& ray, float& t){
	//glm::vec3 ray_direction = glm::normalize(ray.direction); //方向矢量
	glm::vec3 ray_direction = ray.direction;
	glm::vec3 ray_origin = ray.origin; 
	bool result = false;
	glm::vec3 schnittpunkt{0.0f,0.0f,0.0f};
	// 判断射线与盒x轴方向的面是否有交点, 射线x轴方向分量不为0, 如果射线方向矢量的x轴分量为0, 射线不可能经过盒朝x轴方向的两个面
// x-Achse Richtung zwei Seite 
	if( ray_direction.x != 0 ){
		if(ray_direction.x > 0)//射线沿x轴正方向偏移
			{ 
				t=(minimum_.x - ray_origin.x) / ray_direction.x;
				cout<<"t: "<<t<<endl;
			}
		else{	//射线沿x轴负方向偏移
				t=(maximum_.x - ray_origin.x) / ray_direction.x;
				cout<<"t: "<<t<<endl;
			}
		if ( t>0 ){ // t>0, 射线与平面相交
			schnittpunkt = ray_origin + t*(ray_direction); // 交点坐标
			cout<<"schnittpunkt.x: "<<schnittpunkt.x<<endl;
			cout<<"schnittpunkt.y: "<<schnittpunkt.y<<endl;
			cout<<"schnittpunkt.z: "<<schnittpunkt.z<<endl;
			if( (minimum_.y < schnittpunkt.y && schnittpunkt.y < maximum_.y)  // min.y < schnittpunkt.y < max.y wenn gilt, 交点在当前面内
			 && (minimum_.z < schnittpunkt.z && schnittpunkt.z < maximum_.z) ) // min.z < schnittpunkt.z < max.z
			{ 

				result=true;
			}
		}
	}
// y-Achse Richtung zwei Seite
	if( ray_direction.y !=0 ){
		if(ray_direction.y >0 ){
			t=(minimum_.y - ray_origin.y) / ray_direction.y;
		}
		else{
			t=(maximum_.y - ray_origin.y) / ray_direction.y;
		}
		if ( t>0 ){ // t>0, 射线与平面相交
			schnittpunkt = ray_origin + t*(ray_direction); // 交点坐标
			if( (minimum_.x < schnittpunkt.x && schnittpunkt.x < maximum_.x)  // min.x < schnittpunkt.x < max.x wenn gilt, 交点在当前面内
			 && (minimum_.z < schnittpunkt.z && schnittpunkt.z < maximum_.z) ) // min.z < schnittpunkt.z < max.z
			{ 
				result=true;
			}
		}
	}
// z-Achse Richtung zwei Seite
	if( ray_direction.z !=0 ){
		if(ray_direction.z >0 ){
			t=(minimum_.z - ray_origin.z) / ray_direction.z;
		}
		else{
			t=(maximum_.z - ray_origin.z) / ray_direction.z;
		}
		if ( t>0 ){ // t>0, 射线与平面相交
			schnittpunkt = ray_origin + t*(ray_direction); // 交点坐标
			if( (minimum_.x < schnittpunkt.x && schnittpunkt.x < maximum_.x)  // min.x < schnittpunkt.x < max.x wenn gilt, 交点在当前面内
			 && (minimum_.y < schnittpunkt.y && schnittpunkt.y < maximum_.y) ) // min.y < schnittpunkt.y < max.y
			{ 
				result=true;
			}
		}
	}
return result;
}






