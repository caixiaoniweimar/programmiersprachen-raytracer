#include "box.hpp"
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
	
	/*double Box::area() const{     
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
	}*/

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

	shared_ptr<Material> Box::get_Material() const {
		return material_;
	}

// Aufgabe 6.3 // ignorieren
bool Box::intersect (Ray const& ray, float& t) const{
	//glm::vec3 ray_direction = glm::normalize(ray.direction); //方向矢量
	glm::vec3 ray_direction = ray.direction;
	glm::vec3 ray_origin = ray.origin; 
	bool result = false;
	glm::vec3 schnittpunkt{0.0f,0.0f,0.0f};
	// 判断射线与盒x轴方向的面是否有交点, 射线x轴方向分量不为0, 如果射线方向矢量的x轴分量为0, 射线不可能经过盒朝x轴方向的两个面
// x-Achse Richtung zwei Seite 
//   A non-zero value (true) if x is an infinity; and zero (false) otherwise.
//   如果x是无穷大，则为非零值（true）; 否则为零（假）。
	if( ray_direction.x != 0 ){

		if(ray_direction.x > 10e-6 )//射线沿x轴正方向偏移 // 0.0001
			{ 
				t=(minimum_.x - ray_origin.x) / ray_direction.x;
				bool is_infinity = isinf(t);
				if(is_infinity==true){
					cerr<<"Schnittpunkt existiert nicht."<<endl;
				}
				else{
					//cout<<"t: "<<t<<endl;
				}
			}
		else{	//射线沿x轴负方向偏移
				t=(maximum_.x - ray_origin.x) / ray_direction.x;
				//cout<<"t: "<<t<<endl;
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
		if(ray_direction.y > 10e-6 ){
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
		if(ray_direction.z > 10e-6 ){
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

// vorher Methode funktioniert nicht so gut, schreibt erneut, praktisch benutzt
bool Box::intersect_neue (Ray const& ray, float& t, glm::vec3& normal) const{
	bool result=false;
	float ox=ray.origin.x;
	float oy=ray.origin.y;
	float oz=ray.origin.z;
	float dx=ray.direction.x;
	float dy=ray.direction.y;
	float dz=ray.direction.z;
	
	float min_x,min_y,min_z;
	float max_x,max_y,max_z;

	float a = 1.0/dx;
	if(a>=0){
		min_x =(minimum_.x-ox)*a;
		max_x =(maximum_.x-ox)*a;
	}else{
		min_x=(maximum_.x-ox)*a;
		max_x=(minimum_.x-ox)*a;
	}
	float b = 1.0/dy;
	if(b>=0){
		min_y =(minimum_.y-oy)*b;
		max_y =(maximum_.y-oy)*b;
	}else{
		min_y=(maximum_.y-oy)*b;
		max_y=(minimum_.y-oy)*b;
	}
	float c= 1.0/dz;
	if(c>=0){
		min_z=(minimum_.z-oz)*c;
		max_z=(maximum_.z-oz)*c;
	}else{
		min_z=(maximum_.z-oz)*c;
		max_z=(minimum_.z-oz)*c;
	}
	float biggest_t;// biggest_in_t zwischen min_x,min_y,min_z; in_T!!!
	float smallest_t; // smallest_out_t zwischen max_x,max_y,max_z; out_T!!!
	
	int plane_in,plane_out;
	if(min_x>min_y){
		biggest_t=min_x;
		plane_in=(a>=0.0)? 0:3;
	}else{
		biggest_t=min_y;
		plane_in=(b>=0.0)? 1:4;
	}
	if(min_z>biggest_t){
		biggest_t=min_z;
		plane_in=(c>=0.0)?2:5;
	}
	if(max_x<max_y){
		smallest_t=max_x;
		plane_out=(a>=0.0)?3:0;
	}else{
		smallest_t=max_y;
		plane_out=(b>=0.0)?4:1;
	}
	if(max_z<smallest_t){
		smallest_t=max_z;
		plane_out=(c>=0.0)?5:2;
	}
	result=biggest_t<smallest_t && smallest_t>10e-6;
	if(result==true ){ //hit
		if(biggest_t>10e-6){
			t=biggest_t;
			normal=get_normal(plane_in);
		}
		else{
			t=smallest_t;
			normal=get_normal(plane_out);
		}
	}
	return result;
}

// ignorieren
glm::vec3 Box::getNormal(intersectionResult const& schnittpunkt) const{
  glm::vec3 position = schnittpunkt.position; 
  if(position.x == Approx(minimum_.x))
  {
    return glm::vec3{-1.0,0.0,0.0};
  }
  if(position.y == Approx(minimum_.y))
  {
    return glm::vec3{0.0,-1.0,0.0};
  }
  if(position.z == Approx(minimum_.z))
  {
    return glm::vec3{0.0,0.0,-1.0};
  }
  if(position.x == Approx(maximum_.x))
  {
    return glm::vec3{1.0,0.0,0.0};
  }
  if(position.y == Approx(maximum_.y))
  {
    return glm::vec3{0.0,1.0,0.0};
  }
  if(position.z == Approx(maximum_.z))
  {
    return glm::vec3{0.0,0.0,1.0};
  }
}
// praktisch benutzt
glm::vec3 Box::get_normal(int plane) const{
	switch(plane){
		case 0: return glm::vec3{-1.0,0.0,0.0}; // -x
		case 1: return glm::vec3{0.0,-1.0,0.0}; // -y
		case 2: return glm::vec3{0.0,0.0,-1.0}; // -z
		case 3: return glm::vec3{1.0,0.0,0.0}; // +x-Plane
		case 4: return glm::vec3{0.0,1.0,0.0}; // +y-Plane
		case 5: return glm::vec3{0.0,0.0,1.0}; // +z-Plane
	}
}

intersectionResult Box::istIntersect(Ray const& ray,float& t) const{
    	intersectionResult result{};
		glm::vec3 normal{0,0,0};
		Ray new_ray = transformRay( world_transformation_ ,ray );
    	if(intersect_neue(new_ray,t,normal)==true)
    		{	
    			result.hit=true;
    			result.distance = t;
    			result.position=new_ray.getpoint(result.distance);
    			result.normal = normal; 
				result.closest_shape=this;
    		}
    	return result;
}

















