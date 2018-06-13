#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <shape.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <color.hpp>
#include <cmath>
#include <glm/vec3.hpp> 
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>
#include <memory>
#include <ray.hpp>
using namespace std;
// Aufgabe 5.2
TEST_CASE ("test_area_sphere_box","[area]"){ //Standardkonstruktor
    //auto sphere1 = Sphere{}; //4r^2\pi
    Sphere sphere1{};
    REQUIRE(sphere1.area()==Approx(12.56637).epsilon(0.01));
    Box box1{}; // min: 0.0.0 max:1.1.1
    REQUIRE(box1.area()==6);

    Sphere sphere2{ glm::vec3{1.0f,1.0f,1.0f}, 0.0f };
    REQUIRE(sphere2.area()==0);
    Box box2{ glm::vec3{1.0f,2.0f,3.0f}, glm::vec3{5.0f,5.0f,5.0f} };
    REQUIRE(box2.area()==52);
    
    Sphere sphere3{ glm::vec3{2.0f,2.0f,2.0f}, 2.0f };
	REQUIRE(sphere3.area()==Approx(50.2654).epsilon(0.01));
}

TEST_CASE ("test_volume_sphere","[volume]"){
	Sphere sphere1{}; // (4/3) * M_PI * radius_ * radius_ * radius_
	Box box1{};
	REQUIRE(sphere1.volume()==Approx(4.18879).epsilon(0.01) );
	REQUIRE(box1.volume()==1);

	Sphere sphere2{ glm::vec3{1.0f,1.0f,1.0f}, 0.0f };
	Box box2{ glm::vec3{1.0f,2.0f,3.0f}, glm::vec3{5.0f,5.0f,5.0f} };
	REQUIRE(sphere2.volume()==0 );
	REQUIRE(box2.volume()==24);

	Sphere sphere3{ glm::vec3{2.0f,2.0f,2.0f}, 2.0f };
	REQUIRE(sphere3.volume()==Approx(33.5103).epsilon(0.01));
}

TEST_CASE("test_get_mittelpunkt","[test_get_mittelpunkt]"){
	Sphere sphere1{};
	REQUIRE( sphere1.get_mittelpunkt().x==0.0f );
	Sphere sphere2{ glm::vec3{1.0f,1.0f,1.0f}, 0.0f };
	REQUIRE( sphere2.get_mittelpunkt().x==1.0f);
}

TEST_CASE("test_get_radius","[get_radius]"){
	Sphere sphere1{};
	Sphere sphere2{ glm::vec3{1.0f,1.0f,1.0f}, 0.0f };
	REQUIRE( sphere1.get_radius()==1.0f);
	REQUIRE( sphere2.get_radius()==0.0f );
}

TEST_CASE("test_get_min","test_get_min"){
	Box box1{}; // min: 0.0.0 max:1.1.1
	Box box2{ glm::vec3{1.0f,2.0f,3.0f}, glm::vec3{5.0f,5.0f,5.0f} };
	REQUIRE( box1.get_min().x==0.0f);
	REQUIRE( box2.get_min().y==2.0f);
}

TEST_CASE("test_get_max","test_get_max"){
	Box box1{}; // min: 0.0.0 max:1.1.1
	Box box2{ glm::vec3{1.0f,2.0f,3.0f}, glm::vec3{5.0f,5.0f,5.0f} };
	REQUIRE( box1.get_max().x==1.0f);
	REQUIRE( box2.get_max().z==5.0f);
}

// Aufgabe 5.6 
TEST_CASE("intersect_ray_sphere","[intersect]"){
	// Ray
	glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
	// ray direction has to be normalized!
	// you can use:
	// v=glm::normalize(some_vector)
	glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};

	// Sphere
	glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
	float sphere_radius{1.0f};

	float distance=0.0f;
	auto result=glm::intersectRaySphere(
		ray_origin,ray_direction,
		sphere_center,
		sphere_radius*sphere_radius,
		distance);
	REQUIRE( distance==Approx(4.0f) );
}

int main(int argc, char *argv[])
{
// Aufgabe 5.5
  cout<<"Aufgabe 5.5:"<<endl;
  Sphere sphere1{};
  cout<<sphere1<<endl;
  Box box2{ glm::vec3{1.0f,2.0f,3.0f}, glm::vec3{5.0f,5.0f,5.0f} };
  cout<<box2<<endl;
  cout<<endl;

// Aufgabe 5.7
  cout<<"Aufgabe 5.7:"<<endl;
  Color red{255,0,0};
  glm::vec3 position{0.0f,0.0f,0.0f};
  shared_ptr<Sphere> s1=std::make_shared<Sphere>( "sphere0", red, position, 1.2 );
  shared_ptr<Shape> s2=std::make_shared<Sphere> ( "sphere1", red, position, 1.2 );
  s1->print(cout);
  cout<<endl;
  s2->print(cout);
  cout<<endl;

  return Catch::Session().run(argc, argv);
}

